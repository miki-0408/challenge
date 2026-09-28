#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "tac.h"
#include "cfg.h"
#include "opt.h"

static int blocks_count(void);
/* 判断是否为编译器生成的临时变量（名称以 't' 开头） */
static int is_temp_var(SYM *s)
{
    return s && s->type == SYM_VAR && s->name && s->name[0] == 't';
}

static int is_var(SYM *s)
{
    return s && s->type == SYM_VAR;
}

static int is_const(SYM *s)
{
    return s && s->type == SYM_INT;
}

static int is_side_effect_op(int op)
{
    switch (op)
    {
    case TAC_GOTO:
    case TAC_IFZ:
    case TAC_RETURN:
    case TAC_LABEL:
    case TAC_BEGINFUNC:
    case TAC_ENDFUNC:
    case TAC_ACTUAL:
    case TAC_FORMAL:
    case TAC_CALL:
    case TAC_INPUT:
    case TAC_OUTPUT:
        return 1;
    default:
        return 0;
    }
}

/* ---------------- 常量折叠（Constant Folding） ---------------- */
void opt_constant_folding(void)
{
    for (TAC *i = tac_first; i; i = i->next)
    {
        int op = i->op;
        if (op == TAC_ADD || op == TAC_SUB || op == TAC_MUL || op == TAC_DIV ||
            op == TAC_EQ || op == TAC_NE || op == TAC_LT || op == TAC_LE || op == TAC_GT || op == TAC_GE)
        {
            if (is_const(i->b) && is_const(i->c))
            {
                int lb = i->b->value;
                int lc = i->c->value;
                int v = 0;
                switch (op)
                {
                case TAC_ADD:
                    v = lb + lc;
                    break;
                case TAC_SUB:
                    v = lb - lc;
                    break;
                case TAC_MUL:
                    v = lb * lc;
                    break;
                case TAC_DIV:
                    if (lc != 0)
                        v = lb / lc;
                    else
                        continue;
                    break;
                case TAC_EQ:
                    v = (lb == lc);
                    break;
                case TAC_NE:
                    v = (lb != lc);
                    break;
                case TAC_LT:
                    v = (lb < lc);
                    break;
                case TAC_LE:
                    v = (lb <= lc);
                    break;
                case TAC_GT:
                    v = (lb > lc);
                    break;
                case TAC_GE:
                    v = (lb >= lc);
                    break;
                }
                i->op = TAC_COPY;
                i->b = mk_const(v);
                i->c = NULL;
            }
        }
        else if (op == TAC_NEG)
        {
            if (is_const(i->b))
            {
                i->op = TAC_COPY;
                i->b = mk_const(-(i->b->value));
                i->c = NULL;
            }
        }
    }
}

/* ---------------- 强度削弱（乘以 2 的幂转换为加法，最多到 32） ---------------- */
static int is_power_of_two(int x)
{
    return x > 0 && (x & (x - 1)) == 0;
}
static int log2_int(int x)
{
    int k = 0;
    while (x > 1)
    {
        x >>= 1;
        k++;
    }
    return k;
}

void opt_strength_reduction_basic(void)
{
    for (TAC *i = tac_first; i; i = i->next)
    {
        if (i->op != TAC_MUL)
            continue;
        int c = 0;
        SYM *var = NULL;
        if (is_const(i->b) && is_var(i->c))
        {
            c = i->b->value;
            var = i->c;
        }
        else if (is_var(i->b) && is_const(i->c))
        {
            c = i->c->value;
            var = i->b;
        }
        else
            continue;

        if (!is_power_of_two(c) || c > 32)
            continue;

        if (c == 2)
        {
            i->op = TAC_ADD;
            i->b = var;
            i->c = var;
            continue;
        }

        int n = log2_int(c); /* c == 2^n, n>=2 */
        /* 首先更改当前指令为a=b+b */
        i->op = TAC_ADD;
        i->b = var;
        i->c = var;
        TAC *last = i;
        /* 之后插入 n-1 条 a=a+a */
        for (int step = 2; step <= n; ++step)
        {
            TAC *add = mk_tac(TAC_ADD, i->a, i->a, i->a);
            add->prev = last;
            add->next = last->next;
            if (last->next)
                last->next->prev = add;
            else
                tac_last = add;
            last->next = add;
            last = add;
        }
        i = last;
    }
}

/* ---------------- 针对 SYM* 的简单集合结构 ---------------- */
typedef struct SymSetNode
{
    SYM *s;
    struct SymSetNode *next;
} SymSetNode;

static int set_has(SymSetNode *h, SYM *s)
{
    for (; h; h = h->next)
        if (h->s == s)
            return 1;
    return 0;
}
static void set_add(SymSetNode **h, SYM *s)
{
    if (!s)
        return;
    if (s->type != SYM_VAR)
        return;
    if (set_has(*h, s))
        return;
    SymSetNode *n = (SymSetNode *)malloc(sizeof(SymSetNode));
    n->s = s;
    n->next = *h;
    *h = n;
}
static void set_remove(SymSetNode **h, SYM *s)
{
    SymSetNode **pp = h;
    while (*pp)
    {
        if ((*pp)->s == s)
        {
            SymSetNode *t = *pp;
            *pp = t->next;
            free(t);
            return;
        }
        pp = &(*pp)->next;
    }
}
static void set_union_into(SymSetNode **dst, SymSetNode *src)
{
    for (; src; src = src->next)
        set_add(dst, src->s);
}
static SymSetNode *set_copy(SymSetNode *h)
{
    SymSetNode *r = NULL;
    for (; h; h = h->next)
        set_add(&r, h->s);
    return r;
}
static int set_equal(SymSetNode *a, SymSetNode *b)
{
    /* 先比较大小，再逐项比较成员是否相等 */
    int ca = 0, cb = 0;
    for (SymSetNode *t = a; t; t = t->next)
        ca++;
    for (SymSetNode *t = b; t; t = t->next)
        cb++;
    if (ca != cb)
        return 0;
    for (SymSetNode *t = a; t; t = t->next)
        if (!set_has(b, t->s))
            return 0;
    return 1;
}
static void set_free(SymSetNode *h)
{
    while (h)
    {
        SymSetNode *n = h->next;
        free(h);
        h = n;
    }
}

/* 计算一条 TAC 的 定义/使用 集合 */
static void tac_def_use(TAC *i, SymSetNode **defs, SymSetNode **uses)
{
    switch (i->op)
    {
    case TAC_ADD:
    case TAC_SUB:
    case TAC_MUL:
    case TAC_DIV:
    case TAC_EQ:
    case TAC_NE:
    case TAC_LT:
    case TAC_LE:
    case TAC_GT:
    case TAC_GE:
        set_add(defs, i->a);
        if (is_var(i->b))
            set_add(uses, i->b);
        if (is_var(i->c))
            set_add(uses, i->c);
        break;
    case TAC_NEG:
        set_add(defs, i->a);
        if (is_var(i->b))
            set_add(uses, i->b);
        break;
    case TAC_COPY:
        set_add(defs, i->a);
        if (is_var(i->b))
            set_add(uses, i->b);
        break;
    case TAC_INPUT:
        set_add(defs, i->a);
        break;
    case TAC_CALL:
        if (i->a)
            set_add(defs, i->a);
        /* 参数已通过 ACTUAL 指令发出 */
        break;
    case TAC_IFZ:
        if (is_var(i->b))
            set_add(uses, i->b);
        break;
    case TAC_OUTPUT:
        if (is_var(i->a))
            set_add(uses, i->a);
        break;
    default:
        break; /* 忽略 VAR/FORMAL/ACTUAL/LABEL/GOTO/BEGIN/END/RETURN */
    }
}

/* 基本块级别的 use/def 计算 */
static void block_use_def(Block *b, SymSetNode **use, SymSetNode **def)
{
    *use = NULL;
    *def = NULL;
    for (TAC *i = b->first;; i = i->next)
    {
        SymSetNode *d = NULL, *u = NULL;
        tac_def_use(i, &d, &u);
        /* 仅当使用在定义之前时才记入 use */
        for (SymSetNode *t = u; t; t = t->next)
            if (!set_has(*def, t->s))
                set_add(use, t->s);
        for (SymSetNode *t = d; t; t = t->next)
            set_add(def, t->s);
        if (i == b->last)
            break;
    }
}

/* ---------------- 活跃变量分析（反向，按基本块） ---------------- */
typedef struct
{
    SymSetNode *in, *out, *use, *def;
} LV;

static LV *live_vars_compute(int *nblocks)
{
    int maxId = -1;
    for (Block *b = cfg_blocks_head(); b; b = b->next)
        if (b->id > maxId)
            maxId = b->id;
    *nblocks = maxId + 1;
    LV *lv = (LV *)calloc(*nblocks, sizeof(LV));
    for (Block *b = cfg_blocks_head(); b; b = b->next)
    {
        block_use_def(b, &lv[b->id].use, &lv[b->id].def);
    }
    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (Block *b = cfg_blocks_head(); b; b = b->next)
        {
            SymSetNode *new_out = NULL;
            if (b->succ1 >= 0)
                set_union_into(&new_out, lv[b->succ1].in);
            if (b->succ2 >= 0)
                set_union_into(&new_out, lv[b->succ2].in);
            SymSetNode *new_in = set_copy(lv[b->id].use);
            /* 计算 out - def */
            for (SymSetNode *t = new_out; t; t = t->next)
                if (!set_has(lv[b->id].def, t->s))
                    set_add(&new_in, t->s);
            if (!set_equal(new_in, lv[b->id].in) || !set_equal(new_out, lv[b->id].out))
            {
                set_free(lv[b->id].in);
                set_free(lv[b->id].out);
                lv[b->id].in = new_in;
                lv[b->id].out = new_out;
                changed = 1;
            }
            else
            {
                set_free(new_in);
                set_free(new_out);
            }
        }
    }
    return lv;
}

/* ---------------- 死代码消除（DCE） ---------------- */
void opt_dead_code_elim(void)
{
    cfg_build_only();
    int n = 0;
    LV *lv = live_vars_compute(&n);
    for (Block *b = cfg_blocks_head(); b; b = b->next)
    {
        /* 初始化：live_after = OUT[b] */
        SymSetNode *live = set_copy(lv[b->id].out);
        /* 逆序遍历块中的指令 */
        TAC *i = b->last;
        while (i)
        {
            TAC *prev = i->prev; /* 在可能删除当前指令之前保存前驱 */
            SymSetNode *defs = NULL, *uses = NULL;
            tac_def_use(i, &defs, &uses);
            int can_remove = 0;
            if (!is_side_effect_op(i->op) && defs)
            {
                /* 若 defs 中的变量在 live_after 中都不活跃 */
                int any_live = 0;
                for (SymSetNode *t = defs; t; t = t->next)
                    if (set_has(live, t->s))
                    {
                        any_live = 1;
                        break;
                    }
                if (!any_live)
                    can_remove = 1;
            }
            if (can_remove)
            {
                /* 从全局 TAC 双向链表中摘除当前指令 */
                if (i->prev)
                    i->prev->next = i->next;
                else
                    tac_first = i->next;
                if (i->next)
                    i->next->prev = i->prev;
                else
                    tac_last = i->prev;
                /* 若影响块边界，进行修正 */
                if (b->first == i)
                    b->first = i->next;
                if (b->last == i)
                    b->last = i->prev;
                /* 是否释放节点？为避免其他结构悬挂，保持分配状态 */
            }
            else
            {
                /* live_before = (live_after - defs) ∪ uses */
                for (SymSetNode *t = defs; t; t = t->next)
                    set_remove(&live, t->s);
                set_union_into(&live, uses);
            }
            if (i == b->first)
                break;
            i = prev;
        }
        set_free(live);
    }
    /* 清理临时集合 */
    for (int i = 0; i < n; i++)
    {
        set_free(lv[i].in);
        set_free(lv[i].out);
        set_free(lv[i].use);
        set_free(lv[i].def);
    }
    free(lv);
}

/* ---------------- 优化驱动（执行优化流水线） ---------------- */
void opt_run_all(const char *input_m_filename)
{
    (void)input_m_filename;
    /* 流水顺序：常量折叠 -> 强度削弱 -> 全局 CSE -> 全局复制传播 -> LICM -> DCE */
    opt_constant_folding();
    opt_strength_reduction_basic();
    /* 限次运行 LICM，避免极端情况导致过长迭代。 */
    for (int _licm_iter = 0; _licm_iter < 8; ++_licm_iter)
    {
        int h = opt_licm();
        if (h == 0)
            break;
    }
    opt_cse_global();
    opt_copy_propagation_global();
    opt_dead_code_elim();
    opt_remove_unused_var_decls();
}

/* ---------------- 全局公共子表达式消除（可用表达式分析） ---------------- */
/*  可用表达式前向数据流分析（按基本块）：
    范围：所有二元算术/比较表达式（不含取负），操作数为变量或常量；
    Gen[b]：块 b 内首次计算出的表达式；
    Kill[b]：块 b 内对某变量的定义会杀死以该变量为操作数的表达式；
    In[b]：所有前驱块的 Out 交集；
    Out[b]：Gen[b] ∪ (In[b] − Kill[b])；
    替换：若表达式在当前位置之前可用且存在代表符（与当前目标不同），则将其替换为 COPY；
    保守处理：调用/输入/输出可能影响定义，需保守地杀死相关表达式。 */
static int is_commutative(int op)
{
    return op == TAC_ADD || op == TAC_MUL || op == TAC_EQ || op == TAC_NE;
}
static const char *op_name(int op)
{
    switch (op)
    {
    case TAC_ADD:
        return "ADD";
    case TAC_SUB:
        return "SUB";
    case TAC_MUL:
        return "MUL";
    case TAC_DIV:
        return "DIV";
    case TAC_EQ:
        return "EQ";
    case TAC_NE:
        return "NE";
    case TAC_LT:
        return "LT";
    case TAC_LE:
        return "LE";
    case TAC_GT:
        return "GT";
    case TAC_GE:
        return "GE";
    default:
        return "OP";
    }
}
static int expr_is_candidate(TAC *i)
{
    int op = i->op;
    switch (op)
    {
    case TAC_ADD:
    case TAC_SUB:
    case TAC_MUL:
    case TAC_DIV:
    case TAC_EQ:
    case TAC_NE:
    case TAC_LT:
    case TAC_LE:
    case TAC_GT:
    case TAC_GE:
        return (is_var(i->b) || is_const(i->b)) && (is_var(i->c) || is_const(i->c));
    default:
        return 0;
    }
}

typedef struct ExprInfo
{
    char *key;
    SYM *result;
    SYM *b;
    SYM *c;
    int op;
} ExprInfo;

static char *global_expr_key(int op, SYM *b, SYM *c)
{

    uintptr_t x = (uintptr_t)b, y = (uintptr_t)c;
    if (is_commutative(op) && y < x)
    {
        uintptr_t t = x;
        x = y;
        y = t;
        SYM *ts = b;
        b = c;
        c = ts;
    }
    char buf[128];
    snprintf(buf, sizeof(buf), "%s:%p:%p", op_name(op), (void *)x, (void *)y);
    return strdup(buf);
}

void opt_cse_global(void)
{
    cfg_build_only();
    int cap = 256, ecnt = 0;
    ExprInfo *exprs = (ExprInfo *)malloc(cap * sizeof(ExprInfo));
    for (TAC *t = tac_first; t; t = t->next)
    {
        if (expr_is_candidate(t))
        {
            char *k = global_expr_key(t->op, t->b, t->c);
            int found = -1;
            for (int i = 0; i < ecnt; ++i)
                if (strcmp(exprs[i].key, k) == 0)
                {
                    found = i;
                    break;
                }
            if (found < 0)
            {
                if (ecnt >= cap)
                {
                    cap *= 2;
                    exprs = (ExprInfo *)realloc(exprs, cap * sizeof(ExprInfo));
                }
                exprs[ecnt].key = k;
                exprs[ecnt].result = t->a; /* 首次定义该表达式的结果符号 */
                exprs[ecnt].b = t->b;
                exprs[ecnt].c = t->c;
                exprs[ecnt].op = t->op;
                ecnt++;
            }
            else
            {
                /* 保留已有代表项，释放冗余的 key */
                free(k);
            }
        }
    }
    if (ecnt == 0)
    {
        free(exprs);
        return;
    }
    int nblocks = blocks_count();
    /* 每个基本块的位集合（bitset） */
    unsigned char **gen = (unsigned char **)malloc(nblocks * sizeof(unsigned char *));
    unsigned char **kill = (unsigned char **)malloc(nblocks * sizeof(unsigned char *));
    for (int b = 0; b < nblocks; ++b)
    {
        gen[b] = (unsigned char *)calloc(ecnt, 1);
        kill[b] = (unsigned char *)calloc(ecnt, 1);
    }
    /* 2. Build gen/kill */
    for (Block *b = cfg_blocks_head(); b; b = b->next)
    {
        /* 收集块内被定义的变量 */
        SymSetNode *defined = NULL;
        for (TAC *i = b->first;; i = i->next)
        {
            switch (i->op)
            {
            case TAC_ADD:
            case TAC_SUB:
            case TAC_MUL:
            case TAC_DIV:
            case TAC_EQ:
            case TAC_NE:
            case TAC_LT:
            case TAC_LE:
            case TAC_GT:
            case TAC_GE:
            case TAC_NEG:
            case TAC_COPY:
            case TAC_INPUT:
            case TAC_CALL:
                set_add(&defined, i->a);
                break;
            default:
                break;
            }
            if (expr_is_candidate(i))
            {
                /* 标记进入 Gen 集合 */
                char *k = global_expr_key(i->op, i->b, i->c);
                for (int id = 0; id < ecnt; ++id)
                    if (strcmp(exprs[id].key, k) == 0)
                    {
                        gen[b->id][id] = 1;
                        break;
                    }
                free(k);
            }
            if (i == b->last)
                break;
        }
        /* Kill：任一操作数包含被定义变量的表达式 */
        for (int id = 0; id < ecnt; ++id)
        {
            SYM *vb = exprs[id].b;
            SYM *vc = exprs[id].c;
            if ((is_var(vb) && set_has(defined, vb)) || (is_var(vc) && set_has(defined, vc)))
                kill[b->id][id] = 1;
        }
        set_free(defined);
    }
    /* 第 3 步：数据流不动点计算（可用表达式） */
    unsigned char **in = (unsigned char **)malloc(nblocks * sizeof(unsigned char *));
    unsigned char **out = (unsigned char **)malloc(nblocks * sizeof(unsigned char *));
    for (int b = 0; b < nblocks; ++b)
    {
        in[b] = (unsigned char *)calloc(ecnt, 1);
        out[b] = (unsigned char *)calloc(ecnt, 1);
    }
    int changed = 1;
    int entry = cfg_blocks_head() ? cfg_blocks_head()->id : -1;
    while (changed)
    {
        changed = 0;
        for (Block *b = cfg_blocks_head(); b; b = b->next)
        {
            int bid = b->id;
            /* 计算 in[bid] = 所有前驱 out 的交集 */
            unsigned char *new_in = (unsigned char *)malloc(ecnt);
            if (!b->preds)
            {
                memset(new_in, 0, ecnt); /* entry or unreachable */
            }
            else
            {
                memset(new_in, 1, ecnt); /* start with all */
                for (Pred *p = b->preds; p; p = p->next)
                    for (int id = 0; id < ecnt; ++id)
                        new_in[id] = (unsigned char)(new_in[id] & out[p->id][id]);
            }
            /* out = gen ∪ (in − kill) */
            unsigned char *new_out = (unsigned char *)malloc(ecnt);
            for (int id = 0; id < ecnt; ++id)
            {
                unsigned char avail = (new_in[id] && !kill[bid][id]);
                new_out[id] = (unsigned char)(gen[bid][id] || avail);
            }
            if (memcmp(new_in, in[bid], ecnt) != 0 || memcmp(new_out, out[bid], ecnt) != 0)
            {
                memcpy(in[bid], new_in, ecnt);
                memcpy(out[bid], new_out, ecnt);
                changed = 1;
            }
            free(new_in);
            free(new_out);
        }
    }
    /* 第 4 步：替换遍历 */
    for (Block *b = cfg_blocks_head(); b; b = b->next)
    {
        /* 当前块内的可用性位集 */
        unsigned char *cur = (unsigned char *)malloc(ecnt);
        memcpy(cur, in[b->id], ecnt);
        for (TAC *i = b->first;; i = i->next)
        {
            if (expr_is_candidate(i))
            {
                char *k = global_expr_key(i->op, i->b, i->c);
                int idMatch = -1;
                for (int id = 0; id < ecnt; ++id)
                    if (strcmp(exprs[id].key, k) == 0)
                    {
                        idMatch = id;
                        break;
                    }
                if (idMatch >= 0 && cur[idMatch] && exprs[idMatch].result != i->a)
                {
                    /* 用 COPY 替换原来的计算 */
                    i->op = TAC_COPY;
                    i->b = exprs[idMatch].result;
                    i->c = NULL;
                }
                else if (idMatch >= 0)
                {
                    /* 此计算使该表达式在之后可用 */
                    cur[idMatch] = 1;
                    /* ensure representative symbol recorded (keep first) */
                }
                free(k);
            }
            /* 在变量定义处执行杀死（Kill） */
            switch (i->op)
            {
            case TAC_ADD:
            case TAC_SUB:
            case TAC_MUL:
            case TAC_DIV:
            case TAC_EQ:
            case TAC_NE:
            case TAC_LT:
            case TAC_LE:
            case TAC_GT:
            case TAC_GE:
            case TAC_NEG:
            case TAC_COPY:
            case TAC_INPUT:
            case TAC_CALL:
                if (is_var(i->a))
                {
                    for (int id = 0; id < ecnt; ++id)
                    {
                        SYM *vb = exprs[id].b;
                        SYM *vc = exprs[id].c;
                        if ((vb == i->a) || (vc == i->a))
                            cur[id] = 0;
                    }
                }
                break;
            default:
                break;
            }
            if (i == b->last)
                break;
        }
        free(cur);
    }
    /* 清理分配的临时结构 */
    for (int b = 0; b < nblocks; ++b)
    {
        free(gen[b]);
        free(kill[b]);
        free(in[b]);
        free(out[b]);
    }
    free(gen);
    free(kill);
    free(in);
    free(out);
    for (int i = 0; i < ecnt; ++i)
        free(exprs[i].key);
    free(exprs);
}

/* ---------------- 删除未使用的变量声明 ---------------- */
/* 在所有转换后，可能有 TAC_VAR 声明的符号从未被剩余指令引用。*/
void opt_remove_unused_var_decls(void)
{
    /* 收集所有在非 VAR 指令中被引用的 SYM_VAR */
    SymSetNode *used = NULL;
    for (TAC *t = tac_first; t; t = t->next)
    {
        if (t->op == TAC_VAR)
            continue;
        if (t->a && t->a->type == SYM_VAR)
            set_add(&used, t->a);
        if (t->b && t->b->type == SYM_VAR)
            set_add(&used, t->b);
        if (t->c && t->c->type == SYM_VAR)
            set_add(&used, t->c);
    }
    /* 删除 used 集中不存在的变量声明 */
    for (TAC *t = tac_first; t;)
    {
        TAC *next = t->next;
        if (t->op == TAC_VAR && !set_has(used, t->a))
        {
            if (t->prev)
                t->prev->next = t->next;
            else
                tac_first = t->next;
            if (t->next)
                t->next->prev = t->prev;
            else
                tac_last = t->prev;
            /* no need to free symbol; declaration node discarded */
        }
        t = next;
    }
    set_free(used);
}

/* ---------------- 可达定义 + 全局复制传播 ---------------- */
/* 根据到达的 COPY 定义（位集 curr），在使用处进行替换 */
static void rd_try_replace(SYM **pp, unsigned char *curr, SYM **lhs, TAC **defs, int dcount)
{
    SYM *u = *pp;
    if (!is_var(u))
        return;
    SYM *src = NULL;
    int ok = -1; /* -1:未遇到候选；0:不一致；1:一致 */
    for (int id = 0; id < dcount; ++id)
    {
        if (!curr[id])
            continue;
        if (lhs[id] != u)
            continue;
        TAC *dt = defs[id];
        if (dt->op != TAC_COPY)
        {
            ok = 0;
            break;
        }
        SYM *s = dt->b;
        if (ok == -1)
        {
            src = s;
            ok = 1;
        }
        else if (src != s)
        {
            ok = 0;
            break;
        }
    }
    if (ok == 1 && src)
        *pp = src;
}

/* 收集所有定义类 TAC，并分配 id */
static int collect_defs(TAC ***out_defs, SYM ***out_lhs)
{
    int cap = 256, cnt = 0;
    TAC **defs = (TAC **)malloc(cap * sizeof(TAC *));
    SYM **lhs = (SYM **)malloc(cap * sizeof(SYM *));
    for (TAC *t = tac_first; t; t = t->next)
    {
        switch (t->op)
        {
        case TAC_ADD:
        case TAC_SUB:
        case TAC_MUL:
        case TAC_DIV:
        case TAC_EQ:
        case TAC_NE:
        case TAC_LT:
        case TAC_LE:
        case TAC_GT:
        case TAC_GE:
        case TAC_NEG:
        case TAC_COPY:
        case TAC_INPUT:
        case TAC_CALL:
            if (t->a)
            {
                if (cnt >= cap)
                {
                    cap *= 2;
                    defs = (TAC **)realloc(defs, cap * sizeof(TAC *));
                    lhs = (SYM **)realloc(lhs, cap * sizeof(SYM *));
                }
                defs[cnt] = t;
                lhs[cnt] = t->a;
                cnt++;
            }
            break;
        default:
            break;
        }
    }
    *out_defs = defs;
    *out_lhs = lhs;
    return cnt;
}

void opt_copy_propagation_global(void)
{
    cfg_build_only();
    TAC **defs = NULL;
    SYM **lhs = NULL;
    int dcount = collect_defs(&defs, &lhs);
    if (dcount == 0)
    {
        free(defs);
        free(lhs);
        return;
    }
    /* 为每个基本块构建定义 id 的 gen/kill 集合（位集） */
    int nblocks = blocks_count();
    unsigned char **gen = (unsigned char **)malloc(nblocks * sizeof(unsigned char *));
    unsigned char **kill = (unsigned char **)malloc(nblocks * sizeof(unsigned char *));
    for (int b = 0; b < nblocks; ++b)
    {
        gen[b] = (unsigned char *)calloc(dcount, 1);
        kill[b] = (unsigned char *)calloc(dcount, 1);
    }
    /* 为每个定义 id 找到其所属的块 */
    int *def_block = (int *)malloc(dcount * sizeof(int));
    for (int id = 0; id < dcount; ++id)
    {
        TAC *t = defs[id];
        /* 找到包含该指令 t 的块 */
        int bid = -1;
        for (Block *b = cfg_blocks_head(); b; b = b->next)
        {
            for (TAC *x = b->first;; x = x->next)
            {
                if (x == t)
                {
                    bid = b->id;
                    break;
                }
                if (x == b->last)
                    break;
            }
            if (bid >= 0)
                break;
        }
        def_block[id] = bid;
        if (bid >= 0)
            gen[bid][id] = 1;
    }
    /* 构建 kill：对于每个块，所有具有相同 LHS 且在其他块定义的 id 都被该块杀死 */
    for (int b = 0; b < nblocks; ++b)
    {
        for (int id = 0; id < dcount; ++id)
        {
            if (gen[b][id])
                continue; /* 本块自身的定义不被 kill[b] 标记 */
            SYM *v = lhs[id];
            for (int gid = 0; gid < dcount; ++gid)
            {
                if (gen[b][gid] && lhs[gid] == v)
                {
                    kill[b][id] = 1;
                    break;
                }
            }
        }
    }
    /* RD 前向不动点：基于定义 id 的 in[b]、out[b] 集合（位集） */
    unsigned char **in = (unsigned char **)malloc(nblocks * sizeof(unsigned char *));
    unsigned char **out = (unsigned char **)malloc(nblocks * sizeof(unsigned char *));
    for (int b = 0; b < nblocks; ++b)
    {
        in[b] = (unsigned char *)calloc(dcount, 1);
        out[b] = (unsigned char *)calloc(dcount, 1);
    }
    int changed = 1;
    int iter = 0;
    while (changed)
    {
        iter++;
        changed = 0;
        for (Block *b = cfg_blocks_head(); b; b = b->next)
        {
            int bid = b->id;
            unsigned char *new_in = (unsigned char *)calloc(dcount, 1);
            /* 前驱 out 的并集（OR） */
            if (b->preds)
            {
                for (Pred *p = b->preds; p; p = p->next)
                    for (int id = 0; id < dcount; ++id)
                        new_in[id] = (unsigned char)(new_in[id] | out[p->id][id]);
            }
            unsigned char *new_out = (unsigned char *)malloc(dcount);
            memcpy(new_out, gen[bid], dcount);
            /* out = gen ∪ (in − kill) */
            for (int id = 0; id < dcount; ++id)
            {
                unsigned char avail = (unsigned char)(new_in[id] && !kill[bid][id]);
                new_out[id] = (unsigned char)(new_out[id] | avail);
            }
            if (memcmp(new_in, in[bid], dcount) != 0 || memcmp(new_out, out[bid], dcount) != 0)
            {
                memcpy(in[bid], new_in, dcount);
                memcpy(out[bid], new_out, dcount);
                changed = 1;
            }
            free(new_in);
            free(new_out);
        }
    }
    /* 逐块扫描，维护当前可达集合，并在使用处执行复制传播 */
    for (Block *b = cfg_blocks_head(); b; b = b->next)
    {
        unsigned char *curr = (unsigned char *)malloc(dcount);
        memcpy(curr, in[b->id], dcount);
        for (TAC *t = b->first;; t = t->next)
        {
            /* 在该 TAC 中进行使用处替换 */
            switch (t->op)
            {
            case TAC_ADD:
            case TAC_SUB:
            case TAC_MUL:
            case TAC_DIV:
            case TAC_EQ:
            case TAC_NE:
            case TAC_LT:
            case TAC_LE:
            case TAC_GT:
            case TAC_GE:
                rd_try_replace(&t->b, curr, lhs, defs, dcount);
                rd_try_replace(&t->c, curr, lhs, defs, dcount);
                break;
            case TAC_NEG:
            case TAC_IFZ:
                rd_try_replace(&t->b, curr, lhs, defs, dcount);
                break;
            case TAC_OUTPUT:
                rd_try_replace(&t->a, curr, lhs, defs, dcount);
                break;
            default:
                break;
            }

            /* 更新当前集合：找到对应此指令的定义 id，并应用杀死/加入 */
            for (int id = 0; id < dcount; ++id)
            {
                if (defs[id] == t)
                {
                    /* remove killed defs for this block (defs with same lhs) */
                    for (int k = 0; k < dcount; ++k)
                        if (lhs[k] == lhs[id])
                            curr[k] = 0;
                    curr[id] = 1;
                    break;
                }
            }
            if (t == b->last)
                break;
        }
        free(curr);
    }
    /* 清理分配的集合结构 */
    for (int i = 0; i < nblocks; ++i)
    {
        free(gen[i]);
        free(kill[i]);
        free(in[i]);
        free(out[i]);
    }
    free(gen);
    free(kill);
    free(in);
    free(out);
    free(def_block);
    free(defs);
    free(lhs);
}

/* ==================== LICM（循环不变代码移动 / 外提） ==================== */
/* 支配关系与环构建的辅助函数 */
static int blocks_count(void)
{
    int mx = -1;
    for (Block *b = cfg_blocks_head(); b; b = b->next)
        if (b->id > mx)
            mx = b->id;
    return mx + 1;
}

static unsigned char **alloc_dom(int n)
{
    unsigned char **dom = (unsigned char **)malloc(n * sizeof(unsigned char *));
    for (int i = 0; i < n; i++)
    {
        dom[i] = (unsigned char *)malloc(n);
        memset(dom[i], 0, n);
    }
    return dom;
}
static void free_dom(unsigned char **dom, int n)
{
    for (int i = 0; i < n; i++)
        free(dom[i]);
    free(dom);
}

static Block *get_block_by_id_public(int id)
{
    for (Block *b = cfg_blocks_head(); b; b = b->next)
        if (b->id == id)
            return b;
    return NULL;
}

static void compute_dominators(unsigned char ***pdom, int *pn)
{
    cfg_build_only();
    int n = blocks_count();
    *pn = n;
    unsigned char **dom = alloc_dom(n);
    if (n == 0)
    {
        *pdom = dom;
        return;
    }
    int entry = cfg_blocks_head()->id;
    for (Block *b = cfg_blocks_head(); b; b = b->next)
    {
        int id = b->id;
        if (id == entry)
            dom[id][id] = 1;
        else
            memset(dom[id], 1, n);
    }
    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (Block *b = cfg_blocks_head(); b; b = b->next)
        {
            int id = b->id;
            if (id == entry)
                continue;
            unsigned char *newset = (unsigned char *)malloc(n);
            memset(newset, 1, n);
            if (!b->preds)
                memset(newset, 0, n);
            for (Pred *p = b->preds; p; p = p->next)
                for (int k = 0; k < n; k++)
                    newset[k] = (unsigned char)(newset[k] & dom[p->id][k]);
            newset[id] = 1;
            int diff = memcmp(newset, dom[id], n);
            if (diff != 0)
            {
                memcpy(dom[id], newset, n);
                changed = 1;
            }
            free(newset);
        }
    }
    *pdom = dom;
}

typedef struct LoopSet
{
    unsigned char *in;
    int n;
    int header;
    int tail;
} LoopSet;

static LoopSet build_natural_loop(int header, int tail, int n)
{
    unsigned char *in = (unsigned char *)calloc(n, 1);
    in[header] = 1;
    in[tail] = 1;
    int cap = 64, top = 0;
    int *stack = (int *)malloc(cap * sizeof(int));
    stack[top++] = tail;
    while (top)
    {
        int x = stack[--top];
        Block *bx = get_block_by_id_public(x);
        for (Pred *p = bx->preds; p; p = p->next)
        {
            int pid = p->id;
            if (!in[pid])
            {
                in[pid] = 1;
                if (pid != header)
                {
                    if (top >= cap)
                    {
                        cap *= 2;
                        stack = (int *)realloc(stack, cap * sizeof(int));
                    }
                    stack[top++] = pid;
                }
            }
        }
    }
    free(stack);
    LoopSet ls = {in, n, header, tail};
    return ls;
}

static int sym_is_temp(SYM *s)
{
    return s && s->type == SYM_VAR && s->name && s->name[0] == 't';
}
static void replace_use_with(SYM **p, SYM *from, SYM *to)
{
    if (*p == from)
        *p = to;
}
static void replace_uses_in_tac(TAC *i, SYM *from, SYM *to)
{
    switch (i->op)
    {
    case TAC_ADD:
    case TAC_SUB:
    case TAC_MUL:
    case TAC_DIV:
    case TAC_EQ:
    case TAC_NE:
    case TAC_LT:
    case TAC_LE:
    case TAC_GT:
    case TAC_GE:
        replace_use_with(&i->b, from, to);
        replace_use_with(&i->c, from, to);
        break;
    case TAC_NEG:
        replace_use_with(&i->b, from, to);
        break;
    case TAC_COPY:
        replace_use_with(&i->b, from, to);
        break;
    case TAC_IFZ:
        replace_use_with(&i->b, from, to);
        break;
    case TAC_OUTPUT:
        replace_use_with(&i->a, from, to);
        break;
    default:
        break;
    }
}

static int tac_is_pure_assign(TAC *i)
{
    switch (i->op)
    {
    case TAC_ADD:
    case TAC_SUB:
    case TAC_MUL:
    case TAC_DIV:
    case TAC_EQ:
    case TAC_NE:
    case TAC_LT:
    case TAC_LE:
    case TAC_GT:
    case TAC_GE:
    case TAC_NEG:
    case TAC_COPY:
        return 1;
    default:
        return 0;
    }
}

int opt_licm(void)
{
    cfg_build_only();
    int n = 0;
    unsigned char **dom = NULL;
    compute_dominators(&dom, &n);
    if (n <= 0)
    {
        if (dom)
            free_dom(dom, n);
        return 0;
    }
    int hoisted_count = 0;
    /* 扫描所有满足“h 支配 b”的回边 b->h */
    for (Block *b = cfg_blocks_head(); b; b = b->next)
    {
        int succs[2] = {b->succ1, b->succ2};
        for (int si = 0; si < 2; ++si)
        {
            int h = succs[si];
            if (h < 0)
                continue;
            if (!dom[b->id][h])
                continue;
            /* 构建自然环 */
            LoopSet loop = build_natural_loop(h, b->id, n);
            Block *header = get_block_by_id_public(h);
            if (!header || !header->first)
            {
                free(loop.in);
                continue;
            }
            /* 准备环头信息；仅在确有外提时构建前序块（preheader） */
            TAC *header_first = header->first;
            SYM *headerLabelSym = (header_first->op == TAC_LABEL) ? header_first->a : NULL;
            TAC *preLabelTac = NULL;
            SYM *preLabelSym = NULL;
            TAC *ins = NULL;
            int preheader_built = 0;

            /* 收集环内被定义的变量（指针集合） */
            SymSetNode *defsInLoop = NULL;
            for (Block *bb = cfg_blocks_head(); bb; bb = bb->next)
            {
                if (!loop.in[bb->id])
                    continue;
                for (TAC *i = bb->first;; i = i->next)
                {
                    switch (i->op)
                    {
                    case TAC_ADD:
                    case TAC_SUB:
                    case TAC_MUL:
                    case TAC_DIV:
                    case TAC_EQ:
                    case TAC_NE:
                    case TAC_LT:
                    case TAC_LE:
                    case TAC_GT:
                    case TAC_GE:
                    case TAC_NEG:
                    case TAC_COPY:
                    case TAC_INPUT:
                    case TAC_CALL:
                        set_add(&defsInLoop, i->a);
                        break;
                    default:
                        break;
                    }
                    if (i == bb->last)
                        break;
                }
            }

            /* 一旦创建 preheader，插入点将位于其后 */
            /* 尝试对候选指令做外提 */
            for (Block *bb = cfg_blocks_head(); bb; bb = bb->next)
            {
                if (!loop.in[bb->id])
                    continue;
                for (TAC *i2 = bb->first; i2;)
                {
                    TAC *nexti = (i2 == bb->last) ? NULL : i2->next;
                    if (tac_is_pure_assign(i2) && sym_is_temp(i2->a))
                    {
                        /* 确保 LHS 在环内只有一次真实定义（忽略 TAC_VAR） */
                        int cnt = 0;
                        for (Block *cc = cfg_blocks_head(); cc; cc = cc->next)
                        {
                            if (!loop.in[cc->id])
                                continue;
                            for (TAC *t = cc->first;; t = t->next)
                            {
                                switch (t->op)
                                {
                                case TAC_ADD:
                                case TAC_SUB:
                                case TAC_MUL:
                                case TAC_DIV:
                                case TAC_EQ:
                                case TAC_NE:
                                case TAC_LT:
                                case TAC_LE:
                                case TAC_GT:
                                case TAC_GE:
                                case TAC_NEG:
                                case TAC_COPY:
                                case TAC_INPUT:
                                case TAC_CALL:
                                    if (t->a == i2->a)
                                        cnt++;
                                    break;
                                default:
                                    break;
                                }
                                if (t == cc->last)
                                    break;
                            }
                        }
                        if (cnt == 1)
                        {
                            /* 确保 LHS 未在其块中“定义之前被使用” */
                            int used_before = 0;
                            for (TAC *scan = bb->first; scan && scan != i2; scan = scan->next)
                            {
                                switch (scan->op)
                                {
                                case TAC_ADD:
                                case TAC_SUB:
                                case TAC_MUL:
                                case TAC_DIV:
                                case TAC_EQ:
                                case TAC_NE:
                                case TAC_LT:
                                case TAC_LE:
                                case TAC_GT:
                                case TAC_GE:
                                    if (scan->b == i2->a || scan->c == i2->a)
                                        used_before = 1;
                                    break;
                                case TAC_NEG:
                                case TAC_COPY:
                                case TAC_IFZ:
                                    if (scan->b == i2->a)
                                        used_before = 1;
                                    break;
                                case TAC_OUTPUT:
                                    if (scan->a == i2->a)
                                        used_before = 1;
                                    break;
                                default:
                                    break;
                                }
                                if (scan == bb->last || used_before)
                                    break;
                            }
                            if (!used_before)
                            {
                                /* 检查不变性：所有操作数未在环内定义 */
                                int inv = 1;
                                switch (i2->op)
                                {
                                case TAC_ADD:
                                case TAC_SUB:
                                case TAC_MUL:
                                case TAC_DIV:
                                case TAC_EQ:
                                case TAC_NE:
                                case TAC_LT:
                                case TAC_LE:
                                case TAC_GT:
                                case TAC_GE:
                                    if ((is_var(i2->b) && set_has(defsInLoop, i2->b)) || (is_var(i2->c) && set_has(defsInLoop, i2->c)))
                                        inv = 0;
                                    break;
                                case TAC_NEG:
                                case TAC_COPY:
                                    if (is_var(i2->b) && set_has(defsInLoop, i2->b))
                                        inv = 0;
                                    break;
                                default:
                                    inv = 0;
                                }
                                if (inv)
                                {
                                    /* 在 preheader 中以新临时变量发出该计算；替换使用点；移除原指令 */
                                    /* 若 preheader 尚未存在，则先创建（一次） */
                                    if (!preheader_built)
                                    {
                                        preLabelSym = mk_label(mk_lstr(next_label++));
                                        preLabelTac = mk_tac(TAC_LABEL, preLabelSym, NULL, NULL);
                                        preLabelTac->prev = header_first->prev;
                                        preLabelTac->next = header_first;
                                        if (header_first->prev)
                                            header_first->prev->next = preLabelTac;
                                        else
                                            tac_first = preLabelTac;
                                        header_first->prev = preLabelTac;
                                        /* 仅将环外到环头的边重定向到 preheader（保留回边） */
                                        for (Block *pp = cfg_blocks_head(); pp; pp = pp->next)
                                        {
                                            if (loop.in[pp->id])
                                                continue; /* keep back-edge */
                                            TAC *lt = pp->last;
                                            if (!lt)
                                                continue;
                                            if (lt->op == TAC_GOTO && lt->a && headerLabelSym && lt->a == headerLabelSym)
                                                lt->a = preLabelSym;
                                            if (lt->op == TAC_IFZ && lt->a && headerLabelSym && lt->a == headerLabelSym)
                                                lt->a = preLabelSym;
                                        }
                                        ins = preLabelTac;
                                        preheader_built = 1;
                                    }
                                    SYM *tmp = mk_tmp();
                                    TAC *decl = mk_tac(TAC_VAR, tmp, NULL, NULL);
                                    TAC *comp = mk_tac(i2->op, tmp, i2->b, i2->c);
                                    /* splice after ins */
                                    decl->prev = ins;
                                    decl->next = ins->next;
                                    if (ins->next)
                                        ins->next->prev = decl;
                                    ins->next = decl;
                                    ins = decl;
                                    comp->prev = ins;
                                    comp->next = ins->next;
                                    if (ins->next)
                                        ins->next->prev = comp;
                                    ins->next = comp;
                                    ins = comp;
                                    /* 替换环内的使用点 */
                                    for (Block *rr = cfg_blocks_head(); rr; rr = rr->next)
                                    {
                                        if (!loop.in[rr->id])
                                            continue;
                                        for (TAC *u = rr->first;; u = u->next)
                                        {
                                            if (u != i2)
                                                replace_uses_in_tac(u, i2->a, tmp);
                                            if (u == rr->last)
                                                break;
                                        }
                                    }
                                    /* 将原指令 i2 从链表摘除 */
                                    TAC *rem = i2;
                                    if (rem->prev)
                                        rem->prev->next = rem->next;
                                    else
                                        tac_first = rem->next;
                                    if (rem->next)
                                        rem->next->prev = rem->prev;
                                    else
                                        tac_last = rem->prev;
                                    if (bb->first == rem)
                                        bb->first = rem->next;
                                    if (bb->last == rem)
                                        bb->last = rem->prev;
                                    hoisted_count++;
                                    i2 = nexti;
                                    continue;
                                }
                            }
                        }
                    }
                    /* 存储下沉 / 完整赋值外提：形如 d = invariantTemp */
                    if (i2 && i2->op == TAC_COPY && is_var(i2->a) && !sym_is_temp(i2->a))
                    {
                        /* 统计 LHS 在环内的真实定义次数 */
                        int cntLhs = 0;
                        for (Block *cc = cfg_blocks_head(); cc; cc = cc->next)
                        {
                            if (!loop.in[cc->id])
                                continue;
                            for (TAC *t = cc->first;; t = t->next)
                            {
                                switch (t->op)
                                {
                                case TAC_ADD:
                                case TAC_SUB:
                                case TAC_MUL:
                                case TAC_DIV:
                                case TAC_EQ:
                                case TAC_NE:
                                case TAC_LT:
                                case TAC_LE:
                                case TAC_GT:
                                case TAC_GE:
                                case TAC_NEG:
                                case TAC_COPY:
                                case TAC_INPUT:
                                case TAC_CALL:
                                    if (t->a == i2->a)
                                        cntLhs++;
                                    break;
                                default:
                                    break;
                                }
                                if (t == cc->last)
                                    break;
                            }
                        }
                        if (cntLhs == 1)
                        {
                            /* 确保 LHS 未在其块中“定义之前被使用” */
                            int used_before_lhs = 0;
                            for (TAC *scan = bb->first; scan && scan != i2; scan = scan->next)
                            {
                                switch (scan->op)
                                {
                                case TAC_ADD:
                                case TAC_SUB:
                                case TAC_MUL:
                                case TAC_DIV:
                                case TAC_EQ:
                                case TAC_NE:
                                case TAC_LT:
                                case TAC_LE:
                                case TAC_GT:
                                case TAC_GE:
                                    if (scan->b == i2->a || scan->c == i2->a)
                                        used_before_lhs = 1;
                                    break;
                                case TAC_NEG:
                                case TAC_COPY:
                                case TAC_IFZ:
                                    if (scan->b == i2->a)
                                        used_before_lhs = 1;
                                    break;
                                case TAC_OUTPUT:
                                    if (scan->a == i2->a)
                                        used_before_lhs = 1;
                                    break;
                                default:
                                    break;
                                }
                                if (scan == bb->last || used_before_lhs)
                                    break;
                            }
                            if (!used_before_lhs)
                            {
                                /* 检查 RHS 的不变性 */
                                int rhs_inv = 0;
                                if (is_const(i2->b))
                                    rhs_inv = 1;
                                else if (is_var(i2->b) && !set_has(defsInLoop, i2->b))
                                    rhs_inv = 1;
                                if (rhs_inv)
                                {
                                    /* 确保存在 preheader */
                                    if (!preheader_built)
                                    {
                                        preLabelSym = mk_label(mk_lstr(next_label++));
                                        preLabelTac = mk_tac(TAC_LABEL, preLabelSym, NULL, NULL);
                                        preLabelTac->prev = header_first->prev;
                                        preLabelTac->next = header_first;
                                        if (header_first->prev)
                                            header_first->prev->next = preLabelTac;
                                        else
                                            tac_first = preLabelTac;
                                        header_first->prev = preLabelTac;
                                        /* redirect only edges from outside the loop to preheader */
                                        for (Block *pp = cfg_blocks_head(); pp; pp = pp->next)
                                        {
                                            if (loop.in[pp->id])
                                                continue; /* keep back-edge */
                                            TAC *lt = pp->last;
                                            if (!lt)
                                                continue;
                                            if (lt->op == TAC_GOTO && lt->a && headerLabelSym && lt->a == headerLabelSym)
                                                lt->a = preLabelSym;
                                            if (lt->op == TAC_IFZ && lt->a && headerLabelSym && lt->a == headerLabelSym)
                                                lt->a = preLabelSym;
                                        }
                                        ins = preLabelTac;
                                        preheader_built = 1;
                                    }
                                    /* 将 COPY 外提到 preheader（无需新临时变量） */
                                    TAC *copy = mk_tac(TAC_COPY, i2->a, i2->b, NULL);
                                    copy->prev = ins;
                                    copy->next = ins->next;
                                    if (ins->next)
                                        ins->next->prev = copy;
                                    ins->next = copy;
                                    ins = copy;
                                    /* 移除环内的原始 COPY 指令 */
                                    TAC *rem2 = i2;
                                    if (rem2->prev)
                                        rem2->prev->next = rem2->next;
                                    else
                                        tac_first = rem2->next;
                                    if (rem2->next)
                                        rem2->next->prev = rem2->prev;
                                    else
                                        tac_last = rem2->prev;
                                    if (bb->first == rem2)
                                        bb->first = rem2->next;
                                    if (bb->last == rem2)
                                        bb->last = rem2->prev;
                                    hoisted_count++;
                                    i2 = nexti;
                                    continue;
                                }
                            }
                        }
                    }
                    if (i2 == bb->last)
                        break;
                    i2 = nexti ? nexti : NULL;
                }
            }
            set_free(defsInLoop);
            free(loop.in);
        }
    }
    free_dom(dom, n);
    return hoisted_count;
}
