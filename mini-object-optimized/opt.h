#ifndef OPT_H
#define OPT_H
#include "cfg.h"

/* 运行优化流水线（在 TAC 层进行改写与优化） */
void opt_run_all(const char *input_m_filename);

/* 单独暴露的若干优化（可按需调用） */
void opt_constant_folding(void);
void opt_strength_reduction_basic(void);
void opt_copy_propagation_local(void);
void opt_cse_local(void);
void opt_cse_global(void);
void opt_copy_propagation_global(void);
void opt_dead_code_elim(void);
int opt_licm(void); /* 返回提升（外提）指令数量（含下沉的存储） */
void opt_remove_unused_var_decls(void);

#endif