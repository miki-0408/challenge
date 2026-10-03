# 编译系统课程设计 — mini-object 编译器

用 **flex / bison（lex / yacc）** 从零实现的类 C 语言（mini-object）编译器，覆盖
**词法分析 → 语法分析 → 三地址码 → 控制流图 → 优化 → 汇编 → 目标代码生成** 的完整流程。

代码集中在 `mini-object-optimized/`，在基线版本之上加入了**控制流图（CFG）与七项数据流优化**。

---

## 目录

| 目录 / 文件 | 内容 |
|---|---|
| `mini-object-optimized/` | ★ 带 CFG 与优化的编译器（本 README 重点） |
| `mini-object-extend/` | 基线编译器，扩展了数组 / 结构体等语言特性 |
| `grammar/` | 参考文法资料（C / C++ / C- / Java / SysY 语言规范） |
| `homework/` | 课程作业 |
| `ppt/` | 课程课件 |
| `项目文档-2023080904008-马云.pdf` | 项目报告：设计说明、优化原理与性能测试 |

---

## 编译流水线

`mini-object-optimized/` 下的三个可执行文件串成一条链：

```
foo.m  ──[mini]────>  foo.s        汇编
                  ├─> foo.x        三地址码（TAC）列表
                  └─> foo.cfg.txt  控制流图

foo.s  ──[asm]─────>  foo.o        目标代码

foo.o  ──[machine]─>  执行（虚拟机）
```

`mini` 是主程序，`main.c` 中的调用顺序为：

```c
tac_init();
opt_run_all(input);            // 依次执行全部优化 pass
tac_list();                    // 导出优化后的三地址码
tac_obj();                     // 生成汇编 / 目标代码
cfg_build_and_dump_txt(input); // 导出控制流图
```

---

## 优化实现

优化全部集中在 `opt.c` / `opt.h`，建立在 `cfg.c` 构建的控制流图之上。

| 优化 | 入口函数 | 关键实现 |
|---|---|---|
| 常量折叠 | `opt_constant_folding()` | 编译期对常量表达式求值 |
| 强度削弱 | `opt_strength_reduction_basic()` | 乘除 2 的幂次改写为移位（`is_power_of_two` / `log2_int`） |
| 复制传播 | `opt_copy_propagation_global()` | 基于**到达定义**分析（`collect_defs` / `rd_try_replace`），全局版本 |
| 公共子表达式消除 | `opt_cse_global()` | 表达式键规范化 + 交换律处理（`is_commutative` / `global_expr_key`），全局版本 |
| 循环不变代码外提 | `opt_licm()` | **支配节点计算**（`compute_dominators`）+ **自然循环识别**（`build_natural_loop`） |
| 死代码消除 | `opt_dead_code_elim()` | **活跃变量分析**（`live_vars_compute`，含 def/use 集合计算） |
| LRU 寄存器分配 | `obj.c` | 按"最近使用计数"（`obj.h` 的 `last_use`）选择淘汰寄存器，含**溢出写回**路径 |

另有 `opt_remove_unused_var_decls()`（清除未使用的变量声明），以及局部版本的
复制传播与 CSE（`opt_copy_propagation_local` / `opt_cse_local`）作为对照实现。

---

## 构建与运行

依赖 `lex` / `yacc` / `gcc`：

```bash
cd mini-object-optimized
make          # 生成 mini / asm / machine
```

跑全部测试用例（`testcase/*.m`，结果写入 `results/`）：

```bash
./run_all_tests.sh
```

单独编译并执行一个文件：

```bash
./mini testcase/loop.m     # 产出 loop.s / loop.x / loop.cfg.txt
./asm  testcase/loop.s     # 产出 loop.o
./machine testcase/loop.o  # 执行
```

测试用例覆盖单层循环、嵌套循环、多 while 等控制流结构，用于验证优化不改变程序语义。

---

## 关于性能

`项目文档-2023080904008-马云.pdf` 中记录：优化后代码在性能测试中相较未优化基线
**提升约 20%**（该数字来自项目报告）。

需要说明的是，**本仓库内的 `results/` 保存的是各测试用例的功能正确性输出，不是性能基准**；
基准测试脚本未包含在仓库中。
