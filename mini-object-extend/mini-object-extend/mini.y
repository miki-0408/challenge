%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

int yylex();
void yyerror(char* msg);
static SYM *switch_end_stack[32];
static int switch_stack_top = 0;
%}

%union
{
    char character;
    char *string;
    SYM *sym;
    TAC *tac;
    EXP	*exp;
    FIELD *field;   
    DLIST *dims;   
}

%token INT EQ NE LT LE GT GE UMINUS IF ELSE WHILE INPUT OUTPUT RETURN
%token <string> INTEGER IDENTIFIER TEXT
%token SWITCH CASE DEFAULT BREAK
%token FOR DO CONTINUE AND OR
%token CHAR
%token <character> CHARACTER


%token STRUCT TYPEDEF ARROW
%token <string> TYPEID

%left OR
%left AND
%left EQ NE LT LE GT GE
%left '+' '-'
%left '*' '/'
%right UMINUS
%nonassoc LOWER_THAN_POSTFIX
%left '.' ARROW '[' ']'     /* 后缀运算子统一为同一优先级，左结合 */

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%right '='


%type <tac> program function_declaration_list function_declaration function parameter_list variable_list statement assignment_statement return_statement if_statement while_statement call_statement block declaration_list declaration statement_list input_statement output_statement setup
%type <tac> switch_statement case_list case_item
%type <tac> for_statement do_while_statement
%type <tac> for_init for_iter
%type <tac> param_seq
%type <tac> var_unit 
%type <exp> argument_list expression_list expression call_expression
%type <exp> laddr
%type <exp> for_cond
%type <sym> function_head
%type <dims> dims

/* 结构体字段声明用到 */
%type <field> field_decl field_var_unit field_var_list field_decl_list

%%

program : function_declaration_list
{
    tac_last=$1;
    tac_complete();
}
;

function_declaration_list : function_declaration
| function_declaration_list function_declaration
{
    $$=join_tac($1, $2);
}
;

function_declaration : function
| declaration
;

/* ---------------- 类型说明 ---------------- */
type_spec
: INT  { current_type = T_INT;  current_sdef = NULL; current_elem_dtype=T_UNDEF; current_elem_sdef=NULL; current_ptr_level=0; current_array_len=0; }
| CHAR { current_type = T_CHAR; current_sdef = NULL; current_elem_dtype=T_UNDEF; current_elem_sdef=NULL; current_ptr_level=0; current_array_len=0; }
| STRUCT IDENTIFIER '{' field_decl_list '}'  /* struct S { ... } */
  { SDEF *d = struct_define($2, $4); current_type = T_STRUCT; current_sdef = d; current_elem_dtype=T_UNDEF; current_elem_sdef=NULL; current_ptr_level=0; current_array_len=0; }
| STRUCT '{' field_decl_list '}'            /* 匿名结构 */
  { SDEF *d = struct_define(NULL, $3); current_type = T_STRUCT; current_sdef = d; current_elem_dtype=T_UNDEF; current_elem_sdef=NULL; current_ptr_level=0; current_array_len=0; }
| STRUCT IDENTIFIER                          /* 前向/引用标签 */
  { SDEF *d = struct_forward($2); current_type = T_STRUCT; current_sdef = d; current_elem_dtype=T_UNDEF; current_elem_sdef=NULL; current_ptr_level=0; current_array_len=0; }
| TYPEID                                     /* typedef 名称：带回完整元信息 */
  {
    int dt, edt, pl, al; SDEF *sd, *esd;
    if (!typedef_get($1, &dt, &edt, &pl, &al, &sd, &esd)) yyerror("unknown typedef");
    current_type = dt; current_sdef = sd;
    current_elem_dtype = edt; current_elem_sdef = esd;
    current_ptr_level = pl; current_array_len = al;
  }
;

/* ---------------- 结构体字段声明 ---------------- */
field_decl_list
: field_decl                           { $$ = $1; }
| field_decl_list field_decl           { $$ = field_join($1, $2); }
;

field_decl
: type_spec field_var_list ';'         { $$ = $2; }
;

field_var_list
: field_var_unit                       { $$ = $1; }
| field_var_list ',' field_var_unit    { $$ = field_join($1, $3); }
;

field_var_unit
: IDENTIFIER                           { $$ = field_from_current($1, 0, 0); }
| '*' IDENTIFIER                       { $$ = field_from_current($2, 1, 0); }
| IDENTIFIER dims                       { $$ = field_from_current_dl($1, 0, $2); }
;

/* ---------------- 变量/函数声明 ---------------- */
declaration
: type_spec variable_list ';'    { $$ = $2; }
| TYPEDEF type_spec IDENTIFIER ';'           { typedef_add($3, current_type, T_UNDEF, 0, 0, current_sdef, NULL); $$ = NULL; }
| TYPEDEF type_spec '*' IDENTIFIER ';'       { typedef_add($4, T_PTR, current_type, 1, 0, NULL, current_sdef); $$ = NULL; }
| TYPEDEF type_spec IDENTIFIER '[' INTEGER ']' ';'
  { typedef_add($3, T_ARRAY, current_type, 0, atoi($5), NULL, current_sdef); $$ = NULL; }
| type_spec ';'                 { $$ = NULL; }   // 新增：允许“仅类型说明”的声明，如 struct S {..};

variable_list
: var_unit                      { $$ = $1; }
| variable_list ',' var_unit    { $$ = join_tac($1, $3); }
;

var_unit
: IDENTIFIER                    { $$ = declare_var($1); }
| '*' IDENTIFIER                { $$ = declare_var_ptr($2, 1); }
| IDENTIFIER dims               {
    int n = dl_count($2);
    int *lens = (int*)malloc(sizeof(int)*n);
    dl_to_array($2, lens);
    $$ = declare_var_array_multi_lens($1, lens, n);
}
;

dims
: '[' INTEGER ']' dims          { $$ = dl_new(atoi($2), $4); }
| '[' INTEGER ']'               { $$ = dl_new(atoi($2), NULL); }
;

/* ---------------- 函数 ---------------- */
function
: type_spec function_head '(' parameter_list ')' block
{
    current_function = $2;
    current_function->dtype = current_type;       /* 设置返回类型 */
    current_function->sdef  = (current_type == T_STRUCT) ? current_sdef : NULL;
    $$ = do_func($2, $4, $6);
    scope = 0; sym_tab_local = NULL; current_function = NULL;
}
| error
{
    error("Bad function syntax");
    $$ = NULL;
}
;

function_head : IDENTIFIER
{
    $$=declare_func($1);
    scope=1; /* Enter local scope. */
    sym_tab_local=NULL; /* Init local symbol table. */
}
;

parameter_list
: /* empty */ { $$ = NULL; }
| param_seq
;

param_seq
: type_spec IDENTIFIER                          { $$ = declare_para($2); }
| type_spec '*' IDENTIFIER                      { $$ = declare_para_ptr($3, 1); }
| type_spec IDENTIFIER '[' ']'                  { $$ = declare_para_array($2, 0); } /* 形参数组退化为指针 */
| param_seq ',' type_spec IDENTIFIER            { $$ = join_tac($1, declare_para($4)); }
| param_seq ',' type_spec '*' IDENTIFIER        { $$ = join_tac($1, declare_para_ptr($5, 1)); }
| param_seq ',' type_spec IDENTIFIER '[' ']'    { $$ = join_tac($1, declare_para_array($4, 0)); }
;

/* ---------------- 语句 ---------------- */
statement : assignment_statement ';'
| input_statement ';'
| output_statement ';'
| call_statement ';'
| return_statement ';'
| if_statement
| while_statement
| do_while_statement
| for_statement
| switch_statement
| block
| BREAK ';' { $$ = mk_tac(TAC_BREAK, NULL, NULL, NULL); }
| CONTINUE ';' { $$ = mk_tac(TAC_CONTINUE, NULL, NULL, NULL); }
| error { error("Bad statement syntax"); $$=NULL; }
;


switch_statement : SWITCH '(' expression ')' '{' setup case_list '}'
{
    TAC *res = do_switch($3, $7);
    parser_switch_end = NULL;
    $$ = res;
}
;


setup :
{
    SYM *end_label = mk_label(mk_lstr(next_label++));
    parser_switch_end = end_label;
    $$ = NULL;
}
;

case_list : /* empty */ { $$ = NULL; }
| case_list case_item { $$ = join_tac($1, $2); }
;

case_item : CASE INTEGER ':' statement_list
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *body = $4;
    TAC *case_tac = mk_tac(TAC_CASE, mk_const(atoi($2)), lbl, NULL);
    case_tac->etc = (void *)body;
    $$ = case_tac;
}
| CASE INTEGER ':'
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *case_tac = mk_tac(TAC_CASE, mk_const(atoi($2)), lbl, NULL);
    case_tac->etc = NULL;
    $$ = case_tac;
}
| CASE CHARACTER ':' statement_list
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *body = $4;
    TAC *case_tac = mk_tac(TAC_CASE, mk_char((int)$2), lbl, NULL);
    case_tac->etc = (void *)body;
    $$ = case_tac;
}
| CASE CHARACTER ':'
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *case_tac = mk_tac(TAC_CASE, mk_char((int)$2), lbl, NULL);
    case_tac->etc = NULL;
    $$ = case_tac;
}
| DEFAULT ':' statement_list
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *body = $3;
    TAC *case_tac = mk_tac(TAC_CASE, NULL, lbl, NULL);
    case_tac->etc = (void *)body;
    $$ = case_tac;
}
| DEFAULT ':'
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *case_tac = mk_tac(TAC_CASE, NULL, lbl, NULL);
    case_tac->etc = NULL;
    $$ = case_tac;
}
;

block : '{' declaration_list statement_list '}'
{
    $$=join_tac($2, $3);
}               
;

declaration_list :
{
    $$=NULL;
}
| declaration_list declaration
{
    $$=join_tac($1, $2);
}
;

statement_list : statement
| statement_list statement
{
    $$=join_tac($1, $2);
}               
;

/* ---------------- 赋值（含结构体字段） ---------------- */
assignment_statement
: IDENTIFIER '=' expression
{
    $$ = do_assign(get_var($1), $3);
}
| '*' expression '=' expression  
{
    $$ = do_assign_deref($2, $4);
}
| expression '[' expression ']' '=' expression   
{
    $$ = do_assign_index_exp($1, $3, $6);
}
| expression '.' IDENTIFIER '=' expression       
{
    $$ = do_assign_field_select($1, $3, 0, $5);
}
| expression ARROW IDENTIFIER '=' expression     
{
    $$ = do_assign_field_select($1, $3, 1, $5);
}
;

/* ---------------- 表达式（含字段访问） ---------------- */
expression
: expression '+' expression { $$=do_bin(TAC_ADD, $1, $3); }
| expression '-' expression { $$=do_bin(TAC_SUB, $1, $3); }
| expression '*' expression { $$=do_bin(TAC_MUL, $1, $3); }
| expression '/' expression { $$=do_bin(TAC_DIV, $1, $3); }
| '-' expression  %prec UMINUS { $$=do_un(TAC_NEG, $2); }
| '*' expression  %prec UMINUS { $$=do_deref($2); }
| '&' laddr %prec UMINUS      { $$=$2; }
| expression '[' expression ']' { $$=do_index($1, $3); }
| expression '.' IDENTIFIER   { $$=do_field_select($1, $3, 0); }
| expression ARROW IDENTIFIER { $$=do_field_select($1, $3, 1); }
| expression EQ expression { $$=do_cmp(TAC_EQ, $1, $3); }
| expression NE expression { $$=do_cmp(TAC_NE, $1, $3); }
| expression LT expression { $$=do_cmp(TAC_LT, $1, $3); }
| expression LE expression { $$=do_cmp(TAC_LE, $1, $3); }
| expression GT expression { $$=do_cmp(TAC_GT, $1, $3); }
| expression GE expression { $$=do_cmp(TAC_GE, $1, $3); }
| expression AND expression { $$=do_logic_and($1, $3); }
| expression OR expression  { $$=do_logic_or($1, $3); }
| '(' expression ')' { $$=$2; }
| INTEGER  { $$=mk_exp(NULL, mk_const(atoi($1)), NULL); }
| CHARACTER { $$=mk_exp(NULL, mk_char((int)$1), NULL); }
| IDENTIFIER %prec LOWER_THAN_POSTFIX { $$=exp_from_symbol(get_var($1)); }
| call_expression { $$=$1; }
;

/* laddr 构造：按“地址链”逐步计算，便于解析 &a[i].x / &p->x 等形式 */
laddr
: IDENTIFIER
{
    /* &IDENTIFIER 等价于取该变量地址 */
    $$ = do_addr_var(get_var($1));
}
| laddr '[' expression ']'
{
    /* 在已有地址（指针值）基础上，计算元素地址 */
    $$ = addr_index($1, $3);
}
| laddr '.' IDENTIFIER
{
    /* 已有的是地址（指针），对后续 .name 当作指针访问处理（等价于 ->） */
    $$ = addr_field_select($1, $3, 1);
}
| laddr ARROW IDENTIFIER
{
    /* 仅允许在“地址链”上进行 -> 选择，避免与通用 expression 冲突 */
    $$ = addr_field_select($1, $3, 1);
}
;

argument_list : /* empty */ { $$=NULL; } | expression_list ;

expression_list : expression
|  expression_list ',' expression { $3->next=$1; $$=$3; }
;

input_statement : INPUT IDENTIFIER { $$=do_input(get_var($2)); }
;

output_statement : OUTPUT IDENTIFIER { $$=do_output(get_var($2)); }
| OUTPUT TEXT { $$=do_output(mk_text($2)); }
| OUTPUT CHARACTER { $$=do_output(mk_char((int)$2)); }
;

return_statement : RETURN expression
{
    if (current_function && current_function->dtype != $2->ret->dtype)
        error("return type mismatch");
    TAC *t=mk_tac(TAC_RETURN, $2->ret, NULL, NULL);
    t->prev=$2->tac;
    $$=t;
}
;

if_statement : IF '(' expression ')' block %prec LOWER_THAN_ELSE { $$=do_if($3, $5); }
| IF '(' expression ')' block ELSE block   { $$=do_test($3, $5, $7); }
;

while_statement : WHILE '(' expression ')' block { $$=do_while($3, $5); }
;

do_while_statement : DO block WHILE '(' expression ')' ';' { $$=do_do_while($5, $2); }
;

for_statement : FOR '(' for_init ';' for_cond ';' for_iter ')' block { $$=do_for($3, $5, $7, $9); }
;

for_init : assignment_statement { $$=$1; } | call_statement { $$=$1; } | { $$=NULL; } ;
for_cond : expression { $$=$1; } | { $$=mk_exp(NULL, mk_const(1), NULL); };
for_iter : assignment_statement { $$=$1; } | call_statement { $$=$1; } | { $$=NULL; } ;

call_statement : IDENTIFIER '(' argument_list ')' { $$=do_call($1, $3); }
;
call_expression : IDENTIFIER '(' argument_list ')' { $$=do_call_ret($1, $3); }
;

%%

void yyerror(char* msg) 
{
    fprintf(stderr, "%s: line %d\n", msg, yylineno);
    exit(0);
}