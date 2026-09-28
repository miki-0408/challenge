#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"
#include "cfg.h"

/* 结构定义已在 cfg.h 暴露 */

typedef struct LabelMap LabelMap;
struct LabelMap
{
    char *name;
    /*
     * 标签映射（名称 -> 基本块 id）
     * 在构块第一趟中建立，供跳转目标解析使用。
     */
    int blockId;
    LabelMap *next;
};

static Block *blocks_head = NULL, *blocks_tail = NULL;
static int block_count = 0;
static LabelMap *labels = NULL;

static int is_leader(TAC *t)
{
    if (!t)
        return 0;
    /*
     * 判断一条 TAC 是否为基本块 leader：
     * - 标签（TAC_LABEL）；
     * - 函数起点（TAC_BEGINFUNC）。
     */
    if (t->op == TAC_LABEL)
        return 1;
    if (t->op == TAC_BEGINFUNC)
        return 1;
    return 0;
}

static void labelmap_put(char *name, int blockId)
{
    LabelMap *m = (LabelMap *)malloc(sizeof(LabelMap));
    m->name = name;
    /* 将标签名与块 id 关联（头插链表） */
    m->blockId = blockId;
    m->next = labels;
    labels = m;
}

static int labelmap_get(char *name)
{
    for (LabelMap *m = labels; m; m = m->next)
    {
        /* 通过标签名查找对应块 id，找不到返回 -1 */
        if (m->name && name && strcmp(m->name, name) == 0)
            return m->blockId;
    }
    return -1;
}

static Block *new_block(TAC *first)
{
    Block *b = (Block *)calloc(1, sizeof(Block));
    b->id = block_count++;
    /* 新建一个以 first 为首指令的基本块，并接到块链表尾部 */
    b->first = first;
    b->last = first;
    b->succ1 = -1;
    b->succ2 = -1;
    b->labelName = NULL;
    b->preds = NULL;
    b->next = NULL;
    if (!blocks_head)
        blocks_head = b;
    else
        blocks_tail->next = b;
    blocks_tail = b;
    return b;
}

static void build_blocks(void)
{
    blocks_head = blocks_tail = NULL;
    block_count = 0;
    /*
     * 第一趟：按 leader/终止条件切分基本块，并记录起始标签到块 id 的映射。
     * 终止条件包括：GOTO、IFZ、RETURN、ENDFUNC；
     * 下一条指令是 leader 也会开新块。
     */
    labels = NULL;

    if (!tac_first)
        return;
    TAC *cur = tac_first;
    Block *currBlock = new_block(cur);
    for (; cur; cur = cur->next)
    {
        if (cur == currBlock->first && cur->op == TAC_LABEL && cur->a && cur->a->name)
        {
            currBlock->labelName = cur->a->name;
            labelmap_put(cur->a->name, currBlock->id);
        }

        currBlock->last = cur;

        int terminates = 0;
        switch (cur->op)
        {
        case TAC_GOTO:
        case TAC_IFZ:
        case TAC_RETURN:
        case TAC_ENDFUNC:
            terminates = 1;
            break;
        default:
            break;
        }

        TAC *nxt = cur->next;
        int next_is_leader = is_leader(nxt);
        if (terminates || next_is_leader)
        {
            if (nxt)
            {
                currBlock = new_block(nxt);
            }
        }
    }
}

static Block *get_block_by_id(int id)
{
    for (Block *b = blocks_head; b; b = b->next)
        if (b->id == id)
            /* 按 id 在线性块链表中查找块 */
            return b;
    return NULL;
}

static Block *get_next_block(Block *b)
{
    return b ? b->next : NULL;
}
/* 获取顺序意义上的下一个块 */

static void wire_successors(void)
{
    for (Block *b = blocks_head; b; b = b->next)
    {
        /*
         * 第二趟：根据每个块最后一条指令连好后继边。
         * - GOTO：succ1 指向标签目标；
         * - IFZ：succ1 指向分支目标，succ2 指向顺序落下块；
         * - RETURN/ENDFUNC：无后继；
         * - 其他：succ1 指向顺序落下块。
         */
        TAC *last = b->last;
        if (!last)
            continue;
        switch (last->op)
        {
        case TAC_GOTO:
            if (last->a && last->a->name)
                b->succ1 = labelmap_get(last->a->name);
            break;
        case TAC_IFZ:
            if (last->a && last->a->name)
                b->succ1 = labelmap_get(last->a->name);
            if (get_next_block(b))
                b->succ2 = get_next_block(b)->id;
            break;
        case TAC_RETURN:
        case TAC_ENDFUNC:
            break;
        default:
            if (get_next_block(b))
                b->succ1 = get_next_block(b)->id;
            break;
        }
    }
}
static void add_pred(int toId, int fromId)
{
    Block *to = get_block_by_id(toId);
    if (!to)
        return;
    /* 给目标块增加一个前驱记录（去重） */
    Pred *p = (Pred *)malloc(sizeof(Pred));
    for (Pred *q = to->preds; q; q = q->next)
        if (q->id == fromId)
        {
            free(p);
            return;
        }
    p->id = fromId;
    p->next = to->preds;
    to->preds = p;
}

static void build_predecessors(void)
{
    for (Block *b = blocks_head; b; b = b->next)
    {
        Pred *p = b->preds;
        /*
         * 第三趟：先清空每个块的前驱链表，再依据 succ1/succ2 反向构建 preds。
         */
        while (p)
        {
            Pred *n = p->next;
            free(p);
            p = n;
        }
        b->preds = NULL;
    }

    for (Block *b = blocks_head; b; b = b->next)
    {
        if (b->succ1 >= 0)
            add_pred(b->succ1, b->id);
        if (b->succ2 >= 0)
            add_pred(b->succ2, b->id);
    }
}

static char *make_cfg_txt_filename(const char *input_m_filename)
{
    size_t n = strlen(input_m_filename);
    const char *suf = ".cfg.txt";
    if (n >= 2 && input_m_filename[n - 2] == '.' && (input_m_filename[n - 1] == 'm' || input_m_filename[n - 1] == 'M'))
    /* 生成输出文件名：将末尾 .m / .M 替换成 .cfg.txt，若无 .m 则直接追加 */
    {
        char *out = (char *)malloc(n - 2 + strlen(suf) + 1);
        memcpy(out, input_m_filename, n - 2);
        memcpy(out + (n - 2), suf, strlen(suf) + 1);
        return out;
    }
    char *out = (char *)malloc(n + strlen(suf) + 1);
    memcpy(out, input_m_filename, n);
    memcpy(out + n, suf, strlen(suf) + 1);
    return out;
}

static void dump_txt(const char *input_m_filename)
{
    char *txt = make_cfg_txt_filename(input_m_filename);
    FILE *f = fopen(txt, "w");
    if (!f)
    /*
     * 将 CFG 以可读的文本形式输出：
     * - Block 行：块 id 与可选标签；
     * - succ：后继列表，并标注边类型（goto/branch/fallthrough）；
     * - preds：前驱列表；
     * - tacs：该块内的三地址码序列（通过 out_tac 打印）。
     */
    {
        fprintf(stderr, "error: open %s failed\n", txt);
        free(txt);
        return;
    }
    fprintf(f, "CFG detail for %s\n\n", input_m_filename);

    for (Block *b = blocks_head; b; b = b->next)
    {
        fprintf(f, "Block B%d", b->id);
        if (b->labelName)
            fprintf(f, " (label: %s)", b->labelName);
        fprintf(f, "\n  succ: ");
        int first = 1;
        const char *k1 = NULL, *k2 = NULL;
        int lastop = b->last ? b->last->op : TAC_UNDEF;
        switch (lastop)
        {
        case TAC_GOTO:
            k1 = "goto";
            break;
        case TAC_IFZ:
            k1 = "branch";
            k2 = "fallthrough";
            break;
        case TAC_RETURN:
        case TAC_ENDFUNC:
            k1 = NULL;
            k2 = NULL;
            break;
        default:
            k1 = b->succ1 >= 0 ? "fallthrough" : NULL;
            break;
        }
        if (b->succ1 >= 0)
        {
            fprintf(f, first ? "B%d" : " ,B%d", b->succ1);
            if (k1)
                fprintf(f, "(%s)", k1);
            first = 0;
        }
        if (b->succ2 >= 0)
        {
            fprintf(f, first ? "B%d" : " ,B%d", b->succ2);
            if (k2)
                fprintf(f, "(%s)", k2);
            first = 0;
        }
        if (first)
            fprintf(f, "<none>");
        fprintf(f, "\n  preds: ");
        first = 1;
        for (Pred *p = b->preds; p; p = p->next)
        {
            fprintf(f, first ? "B%d" : " ,B%d", p->id);
            first = 0;
        }
        if (first)
            fprintf(f, "<none>");
        fprintf(f, "\n  tacs:\n");
        for (TAC *t = b->first; t; t = t->next)
        {
            fprintf(f, "    - ");
            out_tac(f, t);
            fprintf(f, "\n");
            if (t == b->last)
                break;
        }
        fprintf(f, "\n");
    }

    fclose(f);
    free(txt);
}

/* 构建并导出 CFG 的对外入口 */
void cfg_build_and_dump_txt(const char *input_m_filename)
{
    build_blocks();
    wire_successors();
    build_predecessors();
    dump_txt(input_m_filename);
}

/* 仅构建 CFG，供优化器调用 */
void cfg_build_only(void)
{
    build_blocks();
    wire_successors();
    build_predecessors();
}

/* 返回块链表头指针（供只读遍历） */
Block *cfg_blocks_head(void)
{
    return blocks_head;
}
