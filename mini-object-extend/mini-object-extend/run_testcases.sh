#!/usr/bin/env bash
set -euo pipefail

# Default options
NO_BUILD=0
STOP_ON_FAIL=0
RECORD_EXPECTED=0
EXPECTED_FILE=""
TIMEOUT_SEC=10

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
TEST_DIR="$SCRIPT_DIR/testcase"

color_cyan='\033[0;36m'
color_yellow='\033[1;33m'
color_red='\033[0;31m'
color_green='\033[0;32m'
color_reset='\033[0m'

info(){ echo -e "${color_cyan}$*${color_reset}"; }
warn(){ echo -e "${color_yellow}$*${color_reset}"; }
err(){ echo -e "${color_red}$*${color_reset}"; }
ok(){ echo -e "${color_green}$*${color_reset}"; }

# Parse args
while [[ $# -gt 0 ]]; do
  case "$1" in
    --no-build) NO_BUILD=1; shift ;;
    --stop-on-fail) STOP_ON_FAIL=1; shift ;;
    --record-expected) RECORD_EXPECTED=1; shift ;;
    --expected-file) EXPECTED_FILE="$2"; shift 2 ;;
    --timeout-sec) TIMEOUT_SEC="$2"; shift 2 ;;
    -h|--help)
      cat <<EOF
Usage: $0 [--no-build] [--stop-on-fail] [--record-expected] [--expected-file path] [--timeout-sec N]

Runs all tests in testcase/*.m using ./mini -> ./asm -> ./machine
EOF
      exit 0
      ;;
    *) err "Unknown option: $1"; exit 2 ;;
  esac
done

if [[ -z "$EXPECTED_FILE" ]]; then
  EXPECTED_FILE="$TEST_DIR/expected.json"
fi


build_tools(){
  if [[ "$NO_BUILD" == "1" ]]; then info "Build: Skipped (--no-build)"; return; fi
  info "Build: make"
  make -C "$SCRIPT_DIR"
  if [[ ! -x "$SCRIPT_DIR/mini" || ! -x "$SCRIPT_DIR/asm" || ! -x "$SCRIPT_DIR/machine" ]]; then
    err "Build: binaries missing (mini/asm/machine)."; exit 2
  fi
}

# Default expectations (fallback when expected.json absent or jq not available)
default_stdin(){
  case "$1" in
    arr) echo "5";;
    arr-while) echo "1";;
    char|char-int) echo -e "Z\nA";;
    for) echo "5";;
    for-bc) echo "12";;
    func-char) echo -e "A\nB";;
    func-int) echo -e "7\n3";;
    if) echo -e "2\n5";;
    int) echo "5";;
    ptr-char) echo -e "Z\nA";;
    ptr-char-int) echo -e "K\n123";;
    ptr-int) echo "5";;
    struct) echo -e "1\n2\n3";;
    switch) echo "3";;
    while) echo "5";;
    while-bc) echo "15";;
    *) return 1;;
  esac
}

default_expected_all(){
  case "$1" in
    arr) printf "%s\n" "17" ;;
    arr-struct) printf "%s\n" "12ab" ;;
    arr-while) printf "%s\n" "10987654321" ;;
    char) printf "%s\n" "AbcZ" "B" ;;
    char-int) printf "%s\n" "AbcZ" "65989990" ;;
    for) printf "%s\n" "01234" ;;
    for-bc) printf "%s\n" "012345678910break" "0123456789continue11" ;;
    func-char) printf "%s\n" "B C" ;;
    func-int) printf "%s\n" "7 8" ;;
    if) printf "%s\n" "not equal" "7" ;;
    int) printf "%s\n" "515-5-150" ;;
    ptr-char) printf "%s\n" "AbcZ" "AB" ;;
    ptr-char-int) printf "%s\n" "K123" ;;
    ptr-int) printf "%s\n" "515-5-150" "111222" ;;
    struct) printf "%s\n" "103202301" ;;
    struct-arr) printf "%s\n" "12ab" ;;
    struct-ptr) printf "%s\n" "999" ;;
    switch) printf "%s\n" "6" ;;
    while) printf "%s\n" "01234" ;;
    while-bc) printf "%s\n" "012345678910break" "11121314" ;;
    *) return 1;;
  esac
}

get_program_output_lines(){
  # reads stdin, prints only program output (before stats dashed line), trims trailing empty
  awk 'BEGIN{sep=0} { if ($0 ~ /^-+$/) { sep=1 } if (sep==0) print $0 }' |
  awk '1' |
  sed -e :a -e '/^\s*$/{$d;N;ba' -e '}'
}


get_stdin(){
  local name="$1"
  if default_stdin "$name" >/dev/null 2>&1; then default_stdin "$name"; return 0; fi
  return 1
}

get_expected_all(){
  local name="$1"
  if default_expected_all "$name" >/dev/null 2>&1; then default_expected_all "$name"; return 0; fi
  return 1
}

record_expected(){
  local name="$1"; shift
  local stdin_text="$1"; shift
  local got_lines="$1"; shift
  warn "Record mode disabled: JSON source removed. Skipped recording for $name."
}

run_one(){
  local name="$1"
  local m="$TEST_DIR/$name.m"
  local s="$TEST_DIR/$name.s"
  local o="$TEST_DIR/$name.o"

  if [[ ! -f "$m" ]]; then
    warn "Skip: missing $m"; return 0
  fi

  # Compile .m -> .s
  local mini_err
  mini_err=$("$SCRIPT_DIR/mini" "$m" 2>&1 >/dev/null || true)
  if [[ -n "$mini_err" ]]; then
    err "COMPILE_FAIL $name"
    echo "$mini_err" | sed -e 's/^/       /'
    return 1
  fi
  if [[ ! -f "$s" ]]; then err "Fail: $s not generated"; return 1; fi

  # Assemble .s -> .o
  local asm_err
  asm_err=$("$SCRIPT_DIR/asm" "$s" 2>&1 >/dev/null || true)
  if [[ -n "$asm_err" ]]; then
    err "ASM_FAIL $name"
    echo "$asm_err" | sed -e 's/^/       /'
    return 1
  fi
  if [[ ! -f "$o" ]]; then err "Fail: $o not generated"; return 1; fi

  local stdin_text=""
  if stdin_text=$(get_stdin "$name"); then :; else stdin_text=""; fi

  # Run machine with timeout and capture exit code correctly (avoid masking with '|| true')
  local out rc
  if [[ -n "$stdin_text" ]]; then
    set +e
    out=$(echo -e "$stdin_text" | timeout "${TIMEOUT_SEC}"s "$SCRIPT_DIR/machine" "$o")
    rc=$?
    set -e
  else
    set +e
    out=$(timeout "${TIMEOUT_SEC}"s "$SCRIPT_DIR/machine" "$o")
    rc=$?
    set -e
  fi

  # Detect timeout by exit status 124
  if [[ $rc -eq 124 ]]; then
    warn "TIMEOUT $name (${TIMEOUT_SEC}s)"
    return 2
  fi

  # Keep only program output lines
  local prog_lines
  prog_lines=$(printf '%s\n' "$out" | get_program_output_lines)

  if [[ "$RECORD_EXPECTED" == "1" ]]; then
    echo -e "REC  $name"
    record_expected "$name" "$stdin_text" "$prog_lines"
    return 0
  fi

  # Expected lines
  local exp_lines
  if exp_lines=$(get_expected_all "$name"); then :; else
    warn "Skip: No expected mapping for '$name' (defaults only)."; return 0
  fi

  # Normalize and compare sequence strictly
  # Trim trailing spaces per line
  mapfile -t got_arr < <(printf '%s\n' "$prog_lines" | sed -E 's/[[:space:]]+$//' | sed '/^\s*$/d')
  mapfile -t exp_arr < <(printf '%s\n' "$exp_lines" | sed -E 's/[[:space:]]+$//')

  if [[ ${#got_arr[@]} -ne ${#exp_arr[@]} ]]; then
    err "FAIL $name"
    echo '       expected:'; for l in "${exp_arr[@]}"; do echo "         $l"; done
    echo '       got     :'; for l in "${got_arr[@]}"; do echo "         $l"; done
    return 1
  fi
  for i in "$(seq 0 $((${#exp_arr[@]}-1)))"; do :; done >/dev/null 2>&1 # quiet shellcheck
  idx=0
  while [[ $idx -lt ${#exp_arr[@]} ]]; do
    if [[ "${got_arr[$idx]}" != "${exp_arr[$idx]}" ]]; then
      err "FAIL $name"
      echo '       expected:'; for l in "${exp_arr[@]}"; do echo "         $l"; done
      echo '       got     :'; for l in "${got_arr[@]}"; do echo "         $l"; done
      return 1
    fi
    idx=$((idx+1))
  done
  ok "PASS $name"
  return 0
}

main(){
  build_tools
  if [[ ! -d "$TEST_DIR" ]]; then err "Test directory '$TEST_DIR' not found."; exit 2; fi
  local pass=0 total=0
  shopt -s nullglob
  for m in "$TEST_DIR"/*.m; do
    local name
    name="$(basename "$m" .m)"
    total=$((total+1))
    if run_one "$name"; then
      pass=$((pass+1))
    else
      if [[ "$STOP_ON_FAIL" == "1" ]]; then break; fi
    fi
  done
  echo ""
  info "Summary: $pass/$total passed"
}

main "$@"
