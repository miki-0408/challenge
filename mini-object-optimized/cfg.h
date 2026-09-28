#ifndef CFG_H
#define CFG_H
#include "tac.h"

/* 公开 CFG 结构，便于优化器遍历基本块 */
typedef struct Pred Pred;
struct Pred
{
    int id;            /* 前驱块的编号 */
    struct Pred *next; /* 链表下一个前驱 */
};

typedef struct Block Block;
struct Block
{
    int id;          /* 基本块编号 */
    TAC *first;      /* 块起始三地址码 */
    TAC *last;       /* 块结束三地址码 */
    int succ1;       /* 第一后继块编号（-1 表示无） */
    int succ2;       /* 第二后继块编号（-1 表示无） */
    char *labelName; /* 若以标签开始，记录标签名 */
    Pred *preds;     /* 前驱块链表 */
    Block *next;     /* 下一基本块 */
};

/* 构建并导出 CFG 文本到 .cfg.txt 文件 */
void cfg_build_and_dump_txt(const char *input_m_filename);

/* 仅构建 CFG（不输出），供优化器使用 */
void cfg_build_only(void);

/* 获取基本块链表头指针（只读遍历用） */
Block *cfg_blocks_head(void);

#endif
