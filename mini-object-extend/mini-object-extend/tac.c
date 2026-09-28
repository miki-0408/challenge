#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

int scope, next_tmp, next_label;
SYM *sym_tab_global, *sym_tab_local;
TAC *tac_first, *tac_last;

SYM *parser_switch_end = NULL;
int current_type = T_INT;
SYM *current_function = NULL;
SDEF *current_sdef = NULL;

int current_elem_dtype = T_UNDEF;
int current_ptr_level = 0;
int current_array_len = 0;
SDEF *current_elem_sdef = NULL;

/* 多维数组类型结点 */
typedef struct type_node
{
	int kind;				/* T_ARRAY / T_INT / T_CHAR / T_STRUCT */
	int len;				/* 若为 T_ARRAY，则为该维度长度 */
	struct type_node *elem; /* 元素类型（下一层） */
	SDEF *sdef;				/* 若为结构体叶子则指向定义 */
} TNode;

static int size_of_tnode(TNode *tn)
{
	if (!tn)
		return 0;
	switch (tn->kind)
	{
	case T_CHAR:
		return 1;
	case T_INT:
		return 4;
	case T_STRUCT:
		return tn->sdef ? tn->sdef->size : 0;
	case T_ARRAY:
	{
		int esz = size_of_tnode(tn->elem);
		if (esz <= 0)
			esz = 4;
		return (tn->len > 0 ? tn->len : 0) * esz;
	}
	default:
		return 4;
	}
}

static TNode *tnode_make_array(int len, TNode *elem)
{
	TNode *t = (TNode *)malloc(sizeof(TNode));
	t->kind = T_ARRAY;
	t->len = len;
	t->elem = elem;
	t->sdef = NULL;
	return t;
}

static TNode *tnode_make_leaf(int kind, SDEF *sdef)
{
	TNode *t = (TNode *)malloc(sizeof(TNode));
	t->kind = kind;
	t->len = 0;
	t->elem = NULL;
	t->sdef = sdef;
	return t;
}

// 结构体定义与 typedef 表
static SDEF *sdef_tab = NULL;

typedef struct typedef_entry
{
	char *name;
	int dtype;
	int elem_dtype;
	int ptr_level;
	int array_len;
	SDEF *sdef;
	SDEF *elem_sdef;
	struct typedef_entry *next;
} TDEF;

static TDEF *typedef_tab = NULL;

static FIELD *mk_field(char *name, int dtype, int elem_dtype, int ptr_level, int array_len, SDEF *sdef, SDEF *elem_sdef)
{
	FIELD *f = (FIELD *)malloc(sizeof(FIELD));
	f->name = strdup(name);
	f->dtype = dtype;
	f->elem_dtype = elem_dtype;
	f->ptr_level = ptr_level;
	f->array_len = array_len;
	f->sdef = sdef;
	f->elem_sdef = elem_sdef;
	f->tnode = NULL;
	f->offset = 0;
	f->next = NULL;
	return f;
}

FIELD *field_join(FIELD *list, FIELD *item)
{
	if (!list)
		return item;
	FIELD *p = list;
	while (p->next)
		p = p->next;
	p->next = item;
	return list;
}

SDEF *struct_lookup(const char *tag)
{
	for (SDEF *p = sdef_tab; p; p = p->next)
		if (p->name && strcmp(p->name, tag) == 0)
			return p;
	return NULL;
}

SDEF *struct_define(char *tag, FIELD *fields)
{
	SDEF *def = tag ? struct_lookup(tag) : NULL;
	if (!def)
	{
		def = (SDEF *)malloc(sizeof(SDEF));
		def->name = tag ? strdup(tag) : strdup(mk_lstr(next_label++));
		def->fields = NULL;
		def->size = 0;
		def->next = sdef_tab;
		sdef_tab = def;
	}

	/* 直接在原字段链表上计算并写入 offset，避免复制时丢失偏移 */
	int off = 0;
	for (FIELD *f = fields; f; f = f->next)
	{
		int bytes = 0;
		if (f->dtype == T_ARRAY)
		{
			/* 多维数组：若字段带有 tnode，优先使用类型结点计算整个块大小 */
			if (f->tnode)
			{
				bytes = size_of_tnode((TNode *)f->tnode);
			}
			else
			{
				int esz = (f->elem_dtype == T_STRUCT) ? (f->elem_sdef ? f->elem_sdef->size : 0)
													  : size_of_dtype(f->elem_dtype);
				bytes = esz * ((f->array_len > 0) ? f->array_len : 0);
			}
		}
		else if (f->dtype == T_STRUCT)
		{
			bytes = f->sdef ? f->sdef->size : 0;
		}
		else
		{
			bytes = size_of_dtype(f->dtype);
		}
		if (bytes <= 0)
			bytes = 4;
		f->offset = off; /* 写回原结点 */
		off += bytes;
	}
	def->fields = fields; /* 直接挂原链表 */
	def->size = off;
	return def;
}

SDEF *struct_forward(const char *tag)
{
	SDEF *d = struct_lookup(tag);
	if (d)
		return d;
	d = (SDEF *)malloc(sizeof(SDEF));
	d->name = strdup(tag);
	d->fields = NULL;
	d->size = 0;
	d->next = sdef_tab;
	sdef_tab = d;
	return d;
}

static FIELD *find_field(SDEF *def, const char *name)
{
	for (FIELD *f = def ? def->fields : NULL; f; f = f->next)
		if (strcmp(f->name, name) == 0)
			return f;
	return NULL;
}

void typedef_add(const char *name, int dtype, int elem_dtype, int ptr_level, int array_len, SDEF *sdef, SDEF *elem_sdef)
{
	TDEF *e = (TDEF *)malloc(sizeof(TDEF));
	e->name = strdup(name);
	e->dtype = dtype;
	e->elem_dtype = elem_dtype;
	e->ptr_level = ptr_level;
	e->array_len = array_len;
	e->sdef = sdef;
	e->elem_sdef = elem_sdef;
	e->next = typedef_tab;
	typedef_tab = e;
}

int is_typedef_name(const char *name)
{
	for (TDEF *p = typedef_tab; p; p = p->next)
		if (strcmp(p->name, name) == 0)
			return 1;
	return 0;
}

int typedef_get(const char *name, int *dtype, int *elem_dtype, int *ptr_level, int *array_len, SDEF **sdef, SDEF **elem_sdef)
{
	for (TDEF *p = typedef_tab; p; p = p->next)
		if (strcmp(p->name, name) == 0)
		{
			if (dtype)
				*dtype = p->dtype;
			if (elem_dtype)
				*elem_dtype = p->elem_dtype;
			if (ptr_level)
				*ptr_level = p->ptr_level;
			if (array_len)
				*array_len = p->array_len;
			if (sdef)
				*sdef = p->sdef;
			if (elem_sdef)
				*elem_sdef = p->elem_sdef;
			return 1;
		}
	return 0;
}

/* 字段声明：识别 typedef 指针/数组 */
FIELD *field_from_current(char *name, int ptr_level, int array_len)
{
	/* 显式 * 或 [n] 优先。支持多级指针：ptr_level 可大于 1，
	   若当前类型本身是 typedef 成的指针，则与显式 * 的层数相加。 */
	if (ptr_level > 0)
	{
		int lvl = ptr_level;
		int base_dtype;
		SDEF *base_sdef = NULL;
		if (current_type == T_PTR)
		{
			/* typedef 指针 + 显式 * 叠加层数 */
			lvl += (current_ptr_level > 0 ? current_ptr_level : 1);
			base_dtype = (current_elem_dtype != T_UNDEF) ? current_elem_dtype : T_INT;
			base_sdef = (current_elem_dtype == T_STRUCT) ? current_elem_sdef : NULL;
		}
		else if (current_type == T_STRUCT)
		{
			base_dtype = T_STRUCT;
			base_sdef = current_sdef;
		}
		else
		{
			base_dtype = current_type;
		}
		return mk_field(name, T_PTR, base_dtype, lvl, 0, NULL, base_sdef);
	}
	if (array_len > 0)
	{
		if (current_type == T_STRUCT)
			return mk_field(name, T_ARRAY, T_STRUCT, 0, array_len, NULL, current_sdef);
		return mk_field(name, T_ARRAY, current_type, 0, array_len, NULL, NULL);
	}

	/* 没有显式 * 或 [n]，但当前类型本身可能是 typedef 成的指针/数组 */
	if (current_type == T_PTR)
	{
		int lvl = (current_ptr_level > 0 ? current_ptr_level : 1);
		int base_dtype = (current_elem_dtype != T_UNDEF) ? current_elem_dtype : T_INT;
		SDEF *base_sdef = (current_elem_dtype == T_STRUCT) ? current_elem_sdef : NULL;
		return mk_field(name, T_PTR, base_dtype, lvl, 0, NULL, base_sdef);
	}
	if (current_type == T_ARRAY)
	{
		if (current_elem_dtype == T_STRUCT)
			return mk_field(name, T_ARRAY, T_STRUCT, 0, current_array_len, NULL, current_elem_sdef);
		return mk_field(name, T_ARRAY, current_elem_dtype, 0, current_array_len, NULL, NULL);
	}

	/* 标量/结构体本体 */
	if (current_type == T_STRUCT)
		return mk_field(name, T_STRUCT, T_UNDEF, 0, 0, current_sdef, NULL);
	return mk_field(name, current_type, T_UNDEF, 0, 0, NULL, NULL);
}

/* 多维数组字段声明：name dims -> 构建 tnode 并返回 FIELD */
FIELD *field_from_current_dl(char *name, int ptr_level, DLIST *dims)
{
	if (!dims)
		return field_from_current(name, ptr_level, 0);

	int n = dl_count(dims);
	if (n <= 0)
		return field_from_current(name, ptr_level, 0);

	int *lens = (int *)malloc(sizeof(int) * n);
	dl_to_array(dims, lens); /* outer-to-inner: lens[0]..lens[n-1] */

	/* ptr_level > 0: 退化为数组，元素为指针（elem_dtype=T_PTR）——暂不在 tnode 中表示指针 */
	if (ptr_level > 0)
	{
		FIELD *f = mk_field(name, T_ARRAY, T_PTR, ptr_level, lens[0], NULL, NULL);
		f->tnode = NULL;
		free(lens);
		return f;
	}

	/* 构建 tnode：从叶子（基础类型）向外包裹维度 */
	TNode *leaf = (current_type == T_STRUCT) ? tnode_make_leaf(T_STRUCT, current_sdef)
											 : tnode_make_leaf(current_type, NULL);
	TNode *tn = leaf;
	for (int i = 0; i < n; ++i)
	{
		tn = tnode_make_array(lens[i], tn);
	}

	FIELD *f;
	if (n == 1)
		f = mk_field(name, T_ARRAY, current_type, 0, lens[0], NULL, (current_type == T_STRUCT ? current_sdef : NULL));
	else
		f = mk_field(name, T_ARRAY, T_ARRAY, 0, lens[0], NULL, (current_type == T_STRUCT ? current_sdef : NULL));

	f->tnode = tn;
	free(lens);
	return f;
}

static SYM *mk_tmp_typed(int dtype, int elem_dtype, SDEF *sdef, SDEF *elem_sdef)
{
	int old = current_type;
	SDEF *old_sd = current_sdef;
	current_type = T_INT;
	current_sdef = NULL;
	SYM *t = mk_tmp();
	current_type = old;
	current_sdef = old_sd;
	t->dtype = dtype;
	t->elem_dtype = elem_dtype;
	t->ptr_level = (dtype == T_PTR) ? 1 : 0;
	t->sdef = sdef;
	t->elem_sdef = elem_sdef;
	return t;
}

void tac_init()
{
	scope = 0;
	sym_tab_global = NULL;
	sym_tab_local = NULL;
	next_tmp = 0;
	next_label = 1;
	current_type = T_INT;
	current_sdef = NULL;
	sdef_tab = NULL;
	typedef_tab = NULL;
	current_elem_dtype = T_UNDEF;
	current_ptr_level = 0;
	current_array_len = 0;
	current_elem_sdef = NULL;
}

int size_of_dtype(int dtype)
{
	switch (dtype)
	{
	case T_CHAR:
		return 1;
	case T_INT:
	case T_PTR:
		return 4;
	case T_STRUCT:
		return 0;
	default:
		return 4;
	}
}

int size_of_symbol_elem(SYM *s)
{
	/* 多维数组支持：若元素是数组，使用 tnode 递归计算元素块大小 */
	if (s && s->dtype == T_ARRAY && s->tnode)
	{
		TNode *tn = (TNode *)s->tnode;
		if (tn && tn->elem)
		{
			int esz = size_of_tnode(tn->elem);
			if (esz > 0)
				return esz;
		}
	}
	/* 多级指针：其“元素”是指针本身（步长为指针大小） */
	if (s && s->dtype == T_PTR && s->ptr_level > 1)
	{
		return size_of_dtype(T_PTR);
	}
	switch (s->elem_dtype)
	{
	case T_CHAR:
		return 1;
	case T_INT:
	case T_PTR:
		return 4;
	case T_STRUCT:
		return s->elem_sdef ? s->elem_sdef->size : 0;
	default:
		return 4;
	}
}

int size_of_symbol(SYM *s)
{
	if (!s)
		return 0;
	switch (s->dtype)
	{
	case T_CHAR:
		return 1;
	case T_INT:
	case T_PTR:
		return 4;
	case T_STRUCT:
		return s->sdef ? s->sdef->size : 0;
	case T_ARRAY:
	{
		if (s->tnode)
		{
			int bytes = size_of_tnode((TNode *)s->tnode);
			return bytes > 0 ? bytes : 4;
		}
		int esz = size_of_symbol_elem(s);
		int n = s->array_len > 0 ? s->array_len : 0;
		int bytes = esz * n;
		return bytes > 0 ? bytes : 4;
	}
	default:
		return 4;
	}
}

void tac_complete()
{
	TAC *cur = NULL;	  /* Current TAC */
	TAC *prev = tac_last; /* Previous TAC */

	while (prev != NULL)
	{
		prev->next = cur;
		cur = prev;
		prev = prev->prev;
	}

	tac_first = cur;
}

SYM *lookup_sym(SYM *symtab, char *name)
{
	SYM *t = symtab;

	while (t != NULL)
	{
		if (strcmp(t->name, name) == 0)
			break;
		else
			t = t->next;
	}

	return t; /* NULL if not found */
}

void insert_sym(SYM **symtab, SYM *sym)
{
	sym->next = *symtab; /* Insert at head */
	*symtab = sym;
}

SYM *mk_sym(void)
{
	SYM *t;
	t = (SYM *)malloc(sizeof(SYM));
	memset(t, 0, sizeof(SYM));
	return t;
}

SYM *mk_var(char *name)
{
	SYM *sym = NULL;

	if (scope)
		sym = lookup_sym(sym_tab_local, name);
	else
		sym = lookup_sym(sym_tab_global, name);

	if (sym != NULL)
	{
		error("variable already declared");
		return NULL;
	}

	sym = mk_sym();
	sym->type = SYM_VAR;
	sym->name = name;
	sym->offset = -1;
	sym->dtype = current_type;
	sym->elem_dtype = T_UNDEF;
	sym->ptr_level = 0;
	sym->array_len = 0;
	sym->sdef = (current_type == T_STRUCT) ? current_sdef : NULL;
	sym->elem_sdef = NULL;
	sym->tnode = NULL;
	/* 若当前类型来自 typedef 的指针/数组，把元信息写入 */
	if (current_type == T_PTR)
	{
		sym->elem_dtype = (current_elem_dtype != T_UNDEF) ? current_elem_dtype : T_INT;
		sym->elem_sdef = (current_elem_dtype == T_STRUCT) ? current_elem_sdef : NULL;
		sym->ptr_level = (current_ptr_level > 0) ? current_ptr_level : 1;
		sym->sdef = NULL; /* 本体不是结构体 */
	}
	else if (current_type == T_ARRAY)
	{
		sym->elem_dtype = (current_elem_dtype != T_UNDEF) ? current_elem_dtype : T_INT;
		sym->elem_sdef = (current_elem_dtype == T_STRUCT) ? current_elem_sdef : NULL;
		sym->array_len = current_array_len;
		sym->sdef = NULL;
	}
	if (scope)
		insert_sym(&sym_tab_local, sym);
	else
		insert_sym(&sym_tab_global, sym);

	return sym;
}

// 指针变量声明：
TAC *declare_var_ptr(char *name, int level)
{
	SYM *v = mk_var(name);
	v->dtype = T_PTR;
	v->ptr_level = level;
	v->elem_dtype = current_type; /* 指向当前基础类型 */
	v->elem_sdef = (current_type == T_STRUCT) ? current_sdef : NULL;
	v->sdef = NULL;
	return mk_tac(TAC_VAR, v, NULL, NULL);
}

/* 一维数组变量声明 */
TAC *declare_var_array(char *name, int len)
{
	SYM *v = mk_var(name);
	v->dtype = T_ARRAY;
	v->elem_dtype = current_type;
	v->array_len = len;
	v->elem_sdef = (current_type == T_STRUCT) ? current_sdef : NULL;
	v->sdef = NULL;
	v->tnode = NULL; 
	return mk_tac(TAC_VAR, v, NULL, NULL);
}

/* 形式参数：指针 */
TAC *declare_para_ptr(char *name, int level)
{
	SYM *v = mk_var(name);
	v->dtype = T_PTR;
	v->ptr_level = level;
	v->elem_dtype = current_type;
	v->elem_sdef = (current_type == T_STRUCT) ? current_sdef : NULL;
	v->sdef = NULL;
	return mk_tac(TAC_FORMAL, v, NULL, NULL);
}

/* 形式参数：数组（按指针退化处理） */
TAC *declare_para_array(char *name, int len)
{
	SYM *v = mk_var(name);
	v->dtype = T_PTR; /* 参数数组等价为指针 */
	v->ptr_level = 1;
	v->elem_dtype = current_type;
	v->array_len = len;
	v->elem_sdef = (current_type == T_STRUCT) ? current_sdef : NULL;
	v->sdef = NULL;
	return mk_tac(TAC_FORMAL, v, NULL, NULL);
}

/* 多维数组变量声明：lens 为各维长度（外到内），n 为维数 */
TAC *declare_var_array_multi_lens(char *name, int *lens, int n)
{
	if (!lens || n <= 0)
		return declare_var_array(name, 0);

	SYM *v = mk_var(name);
	v->dtype = T_ARRAY;
	v->sdef = NULL;
	v->elem_sdef = (current_type == T_STRUCT) ? current_sdef : NULL;

	/* 构建类型结点：从叶子（基础类型）向外包裹维度 */
	TNode *leaf = (current_type == T_STRUCT) ? tnode_make_leaf(T_STRUCT, current_sdef)
											 : tnode_make_leaf(current_type, NULL);
	TNode *tn = leaf;
	for (int i = 0; i < n; ++i)
	{
		tn = tnode_make_array(lens[i], tn);
	}
	v->tnode = tn; /* 顶层为数组 */

	/* 顶层长度挂在 array_len；元素类型对多维设为 T_ARRAY */
	v->array_len = lens[0];
	if (n == 1)
	{
		v->elem_dtype = current_type;
	}
	else
	{
		v->elem_dtype = T_ARRAY;
	}
	return mk_tac(TAC_VAR, v, NULL, NULL);
}

TAC *join_tac(TAC *c1, TAC *c2)
{
	TAC *t;

	if (c1 == NULL)
		return c2;
	if (c2 == NULL)
		return c1;

	/* Run down c2, until we get to the beginning and then add c1 */
	t = c2;
	while (t->prev != NULL)
		t = t->prev;

	t->prev = c1;
	return c2;
}

TAC *declare_var(char *name)
{
	return mk_tac(TAC_VAR, mk_var(name), NULL, NULL);
}

TAC *mk_tac(int op, SYM *a, SYM *b, SYM *c)
{
	TAC *t = (TAC *)malloc(sizeof(TAC));

	t->next = NULL; /* Set these for safety */
	t->prev = NULL;
	t->op = op;
	t->a = a;
	t->b = b;
	t->c = c;

	return t;
}

SYM *mk_label(char *name)
{
	SYM *t = mk_sym();

	t->type = SYM_LABEL;
	t->name = strdup(name);

	return t;
}

TAC *do_func(SYM *func, TAC *args, TAC *code)
{
	TAC *tlist; /* The backpatch list */

	TAC *tlab;	 /* Label at start of function */
	TAC *tbegin; /* BEGINFUNC marker */
	TAC *tend;	 /* ENDFUNC marker */

	tlab = mk_tac(TAC_LABEL, mk_label(func->name), NULL, NULL);
	tbegin = mk_tac(TAC_BEGINFUNC, NULL, NULL, NULL);
	tend = mk_tac(TAC_ENDFUNC, NULL, NULL, NULL);

	tbegin->prev = tlab;
	code = join_tac(args, code);
	tend->prev = join_tac(tbegin, code);

	return tend;
}

SYM *mk_tmp(void)
{
	SYM *sym;
	char *name;
	int old = current_type;

	name = malloc(12);
	sprintf(name, "t%d", next_tmp++);
	current_type = T_INT; 
	sym = mk_var(name);
	current_type = old;
	return sym;
}

TAC *declare_para(char *name)
{
	SYM *v = mk_var(name);
	return mk_tac(TAC_FORMAL, v, NULL, NULL);
}

SYM *declare_func(char *name)
{
	SYM *sym = NULL;

	sym = lookup_sym(sym_tab_global, name);

	if (sym != NULL)
	{
		if (sym->type == SYM_FUNC)
		{
			error("func already declared");
			return NULL;
		}

		if (sym->type != SYM_UNDEF)
		{
			error("func name already used");
			return NULL;
		}

		return sym;
	}

	sym = mk_sym();
	sym->type = SYM_FUNC;
	sym->name = name;
	sym->address = NULL;

	insert_sym(&sym_tab_global, sym);
	return sym;
}

TAC *do_assign(SYM *var, EXP *exp)
{
	TAC *code;

	if (var->type != SYM_VAR)
		error("assignment to non-variable");

	/* 若左值为标量而右值为指针，且指针指向标量（如数组字段衰变得到的指针），
	   则按“取指针指向的第一个元素”的值来赋值（等价于 *rhs）。
	   这样可以支持 a00 = (pa+0)->a; 把数组字段当作 a[0] 使用。 */
	int lhs_scalar = (var->dtype == T_INT || var->dtype == T_CHAR);
	int rhs_ptr_to_scalar = (exp->ret && exp->ret->dtype == T_PTR &&
							 exp->ret->elem_dtype != T_UNDEF && exp->ret->elem_dtype != T_STRUCT);
	if (lhs_scalar && rhs_ptr_to_scalar)
	{
		TAC *ld = mk_tac(TAC_LOAD, var, exp->ret, NULL);
		ld->prev = exp->tac;
		return ld;
	}

	code = mk_tac(TAC_COPY, var, exp->ret, NULL);
	code->prev = exp->tac;

	return code;
}

TAC *do_input(SYM *var)
{
	TAC *code;

	if (var->type != SYM_VAR)
		error("input to non-variable");

	code = mk_tac(TAC_INPUT, var, NULL, NULL);

	return code;
}

TAC *do_output(SYM *s)
{
	TAC *code;

	code = mk_tac(TAC_OUTPUT, s, NULL, NULL);

	return code;
}

EXP *do_bin(int binop, EXP *exp1, EXP *exp2)
{
	/* 指针算术优先处理 */
	if ((binop == TAC_ADD || binop == TAC_SUB) &&
		((exp1->ret && exp1->ret->dtype == T_PTR) || (exp2->ret && exp2->ret->dtype == T_PTR)))
	{
		/* 归一化为 ptr (+|-) int */
		EXP *ptr = exp1, *off = exp2;
		int sign = +1;
		if (exp1->ret->dtype != T_PTR && exp2->ret->dtype == T_PTR)
		{
			ptr = exp2;
			off = exp1;
		}
		else if (exp1->ret->dtype == T_PTR && exp2->ret->dtype == T_PTR && binop == TAC_SUB)
		{
			/* ptr - ptr => (ptrdiff)/sizeof(elem) */
			int esz;
			if (ptr->ret->ptr_level > 1)
			{
				esz = size_of_dtype(T_PTR);
			}
			else if (ptr->ret->tnode && ((TNode *)ptr->ret->tnode)->kind == T_ARRAY)
			{
				esz = size_of_tnode((TNode *)ptr->ret->tnode);
			}
			else
			{
				esz = (ptr->ret->elem_dtype == T_STRUCT) ? (ptr->ret->elem_sdef ? ptr->ret->elem_sdef->size : 0)
														 : size_of_dtype((ptr->ret->elem_dtype == T_UNDEF) ? T_INT : ptr->ret->elem_dtype);
			}
			TAC *code = join_tac(ptr->tac, off->tac);
			SYM *t = mk_tmp();
			TAC *d = mk_tac(TAC_VAR, t, NULL, NULL);
			d->prev = code;
			TAC *sub = mk_tac(TAC_SUB, t, ptr->ret, off->ret);
			sub->prev = d;
			SYM *q = mk_tmp();
			TAC *dq = mk_tac(TAC_VAR, q, NULL, NULL);
			dq->prev = sub;
			TAC *div = mk_tac(TAC_DIV, q, t, mk_const(esz > 0 ? esz : 4));
			div->prev = dq;
			return mk_exp(NULL, q, div);
		}
		if (binop == TAC_SUB && ptr == exp2)
			sign = -1;

		int esz = (ptr->ret->elem_dtype == T_STRUCT) ? (ptr->ret->elem_sdef ? ptr->ret->elem_sdef->size : 0)
													 : size_of_dtype((ptr->ret->elem_dtype == T_UNDEF) ? T_INT : ptr->ret->elem_dtype);
		if (esz <= 0)
			esz = 4;

		SYM *t_mul = mk_tmp();
		TAC *d_mul = mk_tac(TAC_VAR, t_mul, NULL, NULL);
		TAC *m = mk_tac(TAC_MUL, t_mul, off->ret, mk_const(esz));
		m->prev = d_mul;

		SYM *addr = mk_tmp_typed(T_PTR, ptr->ret->elem_dtype, NULL, ptr->ret->elem_sdef);
		TAC *d_addr = mk_tac(TAC_VAR, addr, NULL, NULL);
		TAC *code = join_tac(ptr->tac, off->tac);
		d_addr->prev = join_tac(code, m);
		TAC *op = mk_tac(sign > 0 ? TAC_ADD : TAC_SUB, addr, ptr->ret, t_mul);
		op->prev = d_addr;
		return mk_exp(NULL, addr, op);
	}
	TAC *temp; /* TAC code for temp symbol */
	TAC *ret;  /* TAC code for result */

	temp = mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
	temp->prev = join_tac(exp1->tac, exp2->tac);
	ret = mk_tac(binop, temp->a, exp1->ret, exp2->ret);
	ret->prev = temp;

	exp1->ret = temp->a;
	exp1->tac = ret;
	exp1->dtype = T_INT; // 算术结果一律 int
	return exp1;
}

EXP *do_cmp(int binop, EXP *exp1, EXP *exp2)
{
	TAC *temp; /* TAC code for temp symbol */
	TAC *ret;  /* TAC code for result */

	temp = mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
	temp->prev = join_tac(exp1->tac, exp2->tac);
	ret = mk_tac(binop, temp->a, exp1->ret, exp2->ret);
	ret->prev = temp;

	exp1->ret = temp->a;
	exp1->tac = ret;
	exp1->dtype = T_INT; // 比较结果为 int 的 0/1
	return exp1;
}

EXP *do_un(int unop, EXP *exp)
{
	TAC *temp; /* TAC code for temp symbol */
	TAC *ret;  /* TAC code for result */

	temp = mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
	temp->prev = exp->tac;
	ret = mk_tac(unop, temp->a, exp->ret, NULL);
	ret->prev = temp;

	exp->ret = temp->a;
	exp->tac = ret;
	exp->dtype = T_INT;
	return exp;
}

TAC *do_call(char *name, EXP *arglist)
{
	EXP *alt;  /* For counting args */
	TAC *code; /* Resulting code */
	TAC *temp; /* Temporary for building code */

	code = NULL;
	for (alt = arglist; alt != NULL; alt = alt->next)
		code = join_tac(code, alt->tac);

	/* 按语法从左到右生成 ACTUAL，保持最后一个为第一个形参（与现有帧布局匹配） */
	while (arglist != NULL)
	{
		temp = mk_tac(TAC_ACTUAL, arglist->ret, NULL, NULL);
		temp->prev = code;
		code = temp;
		arglist = arglist->next;
	}

	temp = mk_tac(TAC_CALL, NULL, (SYM *)strdup(name), NULL);
	temp->prev = code;
	code = temp;

	return code;
}

EXP *do_call_ret(char *name, EXP *arglist)
{
	EXP *alt;
	SYM *ret;
	TAC *code;
	TAC *temp;

	/* 根据被调函数设置返回值类型 */
	SYM *f = lookup_sym(sym_tab_global, name);
	int rtype = T_INT;
	if (f && f->type == SYM_FUNC)
		rtype = f->dtype;

	ret = mk_tmp();
	ret->dtype = rtype;

	code = mk_tac(TAC_VAR, ret, NULL, NULL);

	for (alt = arglist; alt != NULL; alt = alt->next)
		code = join_tac(code, alt->tac);

	while (arglist != NULL)
	{
		temp = mk_tac(TAC_ACTUAL, arglist->ret, NULL, NULL);
		temp->prev = code;
		code = temp;
		arglist = arglist->next;
	}

	temp = mk_tac(TAC_CALL, ret, (SYM *)strdup(name), NULL);
	temp->prev = code;
	code = temp;

	return mk_exp(NULL, ret, code);
}

char *mk_lstr(int i)
{
	char lstr[10] = "L";
	sprintf(lstr, "L%d", i);
	return (strdup(lstr));
}

TAC *do_if(EXP *exp, TAC *stmt)
{
	TAC *label = mk_tac(TAC_LABEL, mk_label(mk_lstr(next_label++)), NULL, NULL);
	TAC *code = mk_tac(TAC_IFZ, label->a, exp->ret, NULL);

	code->prev = exp->tac;
	code = join_tac(code, stmt);
	label->prev = code;

	return label;
}

TAC *do_test(EXP *exp, TAC *stmt1, TAC *stmt2)
{
	TAC *label1 = mk_tac(TAC_LABEL, mk_label(mk_lstr(next_label++)), NULL, NULL);
	TAC *label2 = mk_tac(TAC_LABEL, mk_label(mk_lstr(next_label++)), NULL, NULL);
	TAC *code1 = mk_tac(TAC_IFZ, label1->a, exp->ret, NULL);
	TAC *code2 = mk_tac(TAC_GOTO, label2->a, NULL, NULL);

	code1->prev = exp->tac; /* Join the code */
	code1 = join_tac(code1, stmt1);
	code2->prev = code1;
	label1->prev = code2;
	label1 = join_tac(label1, stmt2);
	label2->prev = label1;

	return label2;
}

// 短路与：res=0; ifz e1 goto end; ifz e2 goto end; res=1; end:
EXP *do_logic_and(EXP *e1, EXP *e2)
{
	SYM *res = mk_tmp();
	TAC *code = mk_tac(TAC_VAR, res, NULL, NULL);

	SYM *l_end = mk_label(mk_lstr(next_label++));

	// e1
	code = join_tac(code, e1->tac);
	TAC *c0 = mk_tac(TAC_COPY, res, mk_const(0), NULL);
	c0->prev = code;
	code = c0;

	TAC *ifz1 = mk_tac(TAC_IFZ, l_end, e1->ret, NULL);
	ifz1->prev = code;
	code = ifz1;

	// e2
	code = join_tac(code, e2->tac);
	TAC *ifz2 = mk_tac(TAC_IFZ, l_end, e2->ret, NULL);
	ifz2->prev = code;
	code = ifz2;

	// true -> res=1
	TAC *c1 = mk_tac(TAC_COPY, res, mk_const(1), NULL);
	c1->prev = code;
	code = c1;

	TAC *lab_end = mk_tac(TAC_LABEL, l_end, NULL, NULL);
	lab_end->prev = code;
	code = lab_end;

	return mk_exp(NULL, res, code);
}

// 短路或：res=0; ifz e1 goto check; res=1; goto end; check: ifz e2 goto end; res=1; end:
EXP *do_logic_or(EXP *e1, EXP *e2)
{
	SYM *res = mk_tmp();
	TAC *code = mk_tac(TAC_VAR, res, NULL, NULL);

	SYM *l_check = mk_label(mk_lstr(next_label++));
	SYM *l_end = mk_label(mk_lstr(next_label++));

	// e1
	code = join_tac(code, e1->tac);
	TAC *c0 = mk_tac(TAC_COPY, res, mk_const(0), NULL);
	c0->prev = code;
	code = c0;

	TAC *ifz1 = mk_tac(TAC_IFZ, l_check, e1->ret, NULL);
	ifz1->prev = code;
	code = ifz1;

	TAC *c1a = mk_tac(TAC_COPY, res, mk_const(1), NULL);
	c1a->prev = code;
	code = c1a;

	TAC *g_end = mk_tac(TAC_GOTO, l_end, NULL, NULL);
	g_end->prev = code;
	code = g_end;

	TAC *lab_check = mk_tac(TAC_LABEL, l_check, NULL, NULL);
	lab_check->prev = code;
	code = lab_check;

	// e2
	code = join_tac(code, e2->tac);
	TAC *ifz2 = mk_tac(TAC_IFZ, l_end, e2->ret, NULL);
	ifz2->prev = code;
	code = ifz2;

	TAC *c1b = mk_tac(TAC_COPY, res, mk_const(1), NULL);
	c1b->prev = code;
	code = c1b;

	TAC *lab_end = mk_tac(TAC_LABEL, l_end, NULL, NULL);
	lab_end->prev = code;
	code = lab_end;

	return mk_exp(NULL, res, code);
}

// while: start: cond; ifz end; body; goto start; end:
TAC *do_while(EXP *exp, TAC *stmt)
{
	SYM *l_start = mk_label(mk_lstr(next_label++));
	SYM *l_end = mk_label(mk_lstr(next_label++));

	// 重写 break/continue
	for (TAC *p = stmt; p != NULL; p = p->prev)
	{
		if (p->op == TAC_BREAK)
		{
			p->op = TAC_GOTO;
			p->a = l_end;
			p->b = p->c = NULL;
		}
		if (p->op == TAC_CONTINUE)
		{
			p->op = TAC_GOTO;
			p->a = l_start;
			p->b = p->c = NULL;
		}
	}

	TAC *code = mk_tac(TAC_LABEL, l_start, NULL, NULL); // start:
	code = join_tac(code, exp->tac);					// cond code
	TAC *ifz = mk_tac(TAC_IFZ, l_end, exp->ret, NULL);	// ifz -> end
	ifz->prev = code;
	code = ifz;

	code = join_tac(code, stmt);						  // body
	TAC *g_start = mk_tac(TAC_GOTO, l_start, NULL, NULL); // goto start
	g_start->prev = code;
	code = g_start;

	TAC *lab_end = mk_tac(TAC_LABEL, l_end, NULL, NULL); // end:
	lab_end->prev = code;
	code = lab_end;

	return code;
}

// do...while: start: body; cont: cond; ifz end; goto start; end:
TAC *do_do_while(EXP *exp, TAC *stmt)
{
	SYM *l_start = mk_label(mk_lstr(next_label++));
	SYM *l_cont = mk_label(mk_lstr(next_label++));
	SYM *l_end = mk_label(mk_lstr(next_label++));

	for (TAC *p = stmt; p != NULL; p = p->prev)
	{
		if (p->op == TAC_BREAK)
		{
			p->op = TAC_GOTO;
			p->a = l_end;
			p->b = p->c = NULL;
		}
		if (p->op == TAC_CONTINUE)
		{
			p->op = TAC_GOTO;
			p->a = l_cont;
			p->b = p->c = NULL;
		}
	}

	TAC *code = mk_tac(TAC_LABEL, l_start, NULL, NULL);	   // start:
	code = join_tac(code, stmt);						   // body
	TAC *lab_cont = mk_tac(TAC_LABEL, l_cont, NULL, NULL); // cont:
	lab_cont->prev = code;
	code = lab_cont;

	code = join_tac(code, exp->tac);				   // cond code
	TAC *ifz = mk_tac(TAC_IFZ, l_end, exp->ret, NULL); // ifz -> end
	ifz->prev = code;
	code = ifz;

	TAC *g_start = mk_tac(TAC_GOTO, l_start, NULL, NULL); // goto start
	g_start->prev = code;
	code = g_start;

	TAC *lab_end = mk_tac(TAC_LABEL, l_end, NULL, NULL); // end:
	lab_end->prev = code;
	code = lab_end;

	return code;
}

// for(init; cond; iter) body:
// init; start: cond; ifz end; body; cont: iter; goto start; end:
TAC *do_for(TAC *init, EXP *cond, TAC *iter, TAC *body)
{
	if (cond == NULL)
		cond = mk_exp(NULL, mk_const(1), NULL);

	SYM *l_start = mk_label(mk_lstr(next_label++));
	SYM *l_cont = mk_label(mk_lstr(next_label++));
	SYM *l_end = mk_label(mk_lstr(next_label++));

	for (TAC *p = body; p != NULL; p = p->prev)
	{
		if (p->op == TAC_BREAK)
		{
			p->op = TAC_GOTO;
			p->a = l_end;
			p->b = p->c = NULL;
		}
		if (p->op == TAC_CONTINUE)
		{
			p->op = TAC_GOTO;
			p->a = l_cont;
			p->b = p->c = NULL;
		}
	}

	TAC *code = mk_tac(TAC_LABEL, l_start, NULL, NULL); // start:
	code = join_tac(code, cond->tac);					// cond
	TAC *ifz = mk_tac(TAC_IFZ, l_end, cond->ret, NULL); // ifz -> end
	ifz->prev = code;
	code = ifz;

	code = join_tac(code, body);						   // body
	TAC *lab_cont = mk_tac(TAC_LABEL, l_cont, NULL, NULL); // cont:
	lab_cont->prev = code;
	code = lab_cont;

	code = join_tac(code, iter);						  // iter
	TAC *g_start = mk_tac(TAC_GOTO, l_start, NULL, NULL); // goto start
	g_start->prev = code;
	code = g_start;

	TAC *lab_end = mk_tac(TAC_LABEL, l_end, NULL, NULL); // end:
	lab_end->prev = code;
	code = lab_end;

	// 放在最前面的 init
	return join_tac(init, code);
}

static void rewrite_break_only(TAC *code, SYM *l_end)
{
	for (TAC *p = code; p; p = p->prev)
	{
		if (p->op == TAC_BREAK)
		{
			p->op = TAC_GOTO;
			p->a = l_end;
			p->b = p->c = NULL;
		}
	}
}

// 保留直落语义：不在块末尾补 goto end，避免重复跳转；无主体的 case 不生成 label
TAC *do_switch(EXP *switch_exp, TAC *case_list)
{
	// tmp = switch_exp
	SYM *tmp = mk_tmp();
	TAC *code = mk_tac(TAC_VAR, tmp, NULL, NULL);
	code = join_tac(code, switch_exp->tac);
	code = join_tac(code, mk_tac(TAC_COPY, tmp, switch_exp->ret, NULL));

	// end label
	SYM *end_label = parser_switch_end ? parser_switch_end : mk_label(mk_lstr(next_label++));
	TAC *lab_end = mk_tac(TAC_LABEL, end_label, NULL, NULL);

	TAC *dispatch = NULL; // 判等+跳转链
	TAC *bodies = NULL;	  // 仅包含“有主体”的 case/default 块

	SYM *default_label = NULL;
	TAC *default_body = NULL;
	int default_has_body = 0;

	// 直落目标：记录最近的“有主体”的标签（从后往前扫描）
	SYM *next_body_label = NULL;

	for (TAC *it = case_list; it; it = it->prev)
	{
		if (it->op != TAC_CASE)
			continue;

		SYM *k = it->a;			   // 常量，NULL 表示 default
		SYM *lbl = it->b;		   // 该 case 标签
		TAC *bod = (TAC *)it->etc; // 该 case 的语句链（无主体则为 NULL）

		int has_body = (bod != NULL);

		if (k == NULL)
		{
			// default
			default_label = lbl;
			default_body = bod;
			default_has_body = has_body;

			if (has_body)
			{
				rewrite_break_only(default_body, end_label);
				TAC *blk = mk_tac(TAC_LABEL, lbl, NULL, NULL);
				blk = join_tac(blk, default_body);
				bodies = bodies ? join_tac(bodies, blk) : blk;
				next_body_label = lbl;
			}
			continue;
		}

		// 分派：支持直落到后面最近的“有主体”的标签；否则 default；否则 end
		SYM *target = has_body ? lbl
							   : (next_body_label ? next_body_label
												  : (default_has_body ? default_label : end_label));

		SYM *skip = mk_label(mk_lstr(next_label++));
		EXP *cmp = do_cmp(TAC_EQ, mk_exp(NULL, tmp, NULL), mk_exp(NULL, k, NULL));
		TAC *cmp_code = cmp->tac;
		TAC *ifz = mk_tac(TAC_IFZ, skip, cmp->ret, NULL);
		ifz->prev = cmp_code;
		TAC *g_tgt = mk_tac(TAC_GOTO, target, NULL, NULL);
		g_tgt->prev = ifz;
		TAC *lab_skip = mk_tac(TAC_LABEL, skip, NULL, NULL);
		lab_skip->prev = g_tgt;
		dispatch = dispatch ? join_tac(dispatch, lab_skip) : lab_skip;

		// 有主体的 case：只生成 “label -> body”（不补 goto end）
		if (has_body)
		{
			rewrite_break_only(bod, end_label);
			TAC *blk = mk_tac(TAC_LABEL, lbl, NULL, NULL);
			blk = join_tac(blk, bod);
			bodies = bodies ? join_tac(bodies, blk) : blk;
			next_body_label = lbl;
		}
	}

	// 分派未命中：跳 default 或 end
	SYM *fall = default_label ? default_label : end_label;
	TAC *g_fall = mk_tac(TAC_GOTO, fall, NULL, NULL);

	// 汇总：code(求值) -> dispatch -> g_fall -> bodies -> end
	code = join_tac(code, dispatch);
	code = join_tac(code, g_fall);
	code = join_tac(code, bodies);
	code = join_tac(code, lab_end);
	return code;
}

/* &var -> 产生指针临时，TAC_ADDR */
EXP *do_addr_var(SYM *var)
{
	int elem = (var->dtype == T_ARRAY) ? var->elem_dtype : var->dtype;
	SDEF *esd = NULL;
	if (elem == T_STRUCT)
	{
		esd = (var->dtype == T_ARRAY) ? var->elem_sdef : var->sdef;
	}
	SYM *ret = mk_tmp_typed(T_PTR, elem, NULL, esd);
	TAC *decl = mk_tac(TAC_VAR, ret, NULL, NULL);
	TAC *addr = mk_tac(TAC_ADDR, ret, var, NULL);
	addr->prev = decl;
	return mk_exp(NULL, ret, addr);
}

/* *ptr -> LOAD */
EXP *do_deref(EXP *ptr_exp)
{
	if (!ptr_exp->ret || ptr_exp->ret->dtype != T_PTR)
		return do_un(TAC_NEG, ptr_exp); /* 防御：非指针，退化为旧路径（不会发生于正确语义） */

	int level = (ptr_exp->ret->ptr_level > 0) ? ptr_exp->ret->ptr_level : 1;
	int leaf = ptr_exp->ret->elem_dtype;
	/* 多级指针：*ptr 返回仍为指针，层数减一，LOAD 一个指针值 */
	if (level > 1)
	{
		SYM *ret = mk_tmp_typed(T_PTR, leaf, NULL, ptr_exp->ret->elem_sdef);
		ret->ptr_level = level - 1;
		TAC *decl = mk_tac(TAC_VAR, ret, NULL, NULL);
		TAC *code = join_tac(ptr_exp->tac, decl);
		TAC *ld = mk_tac(TAC_LOAD, ret, ptr_exp->ret, NULL);
		ld->prev = code;
		return mk_exp(NULL, ret, ld);
	}
	/* 单级指针：返回叶子元素的值（标量）。结构体整体作为右值仍不支持 */
	if (leaf == T_STRUCT)
		error("cannot dereference struct as rvalue; use '->field'");
	SYM *ret = mk_tmp_typed((leaf == T_UNDEF) ? T_INT : leaf, T_UNDEF, NULL, NULL);
	TAC *decl = mk_tac(TAC_VAR, ret, NULL, NULL);
	TAC *code = join_tac(ptr_exp->tac, decl);
	TAC *ld = mk_tac(TAC_LOAD, ret, ptr_exp->ret, NULL);
	ld->prev = code;
	return mk_exp(NULL, ret, ld);
}

/* base[idx] 读取：数组名自动衰变为指针，计算地址后 LOAD */
EXP *do_index(EXP *base, EXP *idx)
{
	EXP *base_ptr = base;
	if (base->ret->dtype == T_ARRAY)
	{
		base_ptr = do_addr_var(base->ret);
		/* 传播多维数组的类型信息：指向元素类型 */
		if (base->ret->tnode)
		{
			base_ptr->ret->tnode = ((TNode *)base->ret->tnode)->elem;
			if (base_ptr->ret->tnode && ((TNode *)base_ptr->ret->tnode)->kind == T_ARRAY)
				base_ptr->ret->elem_dtype = T_ARRAY;
		}
	}
	else if (base->ret->dtype != T_PTR)
	{
		error("indexing non-pointer/non-array");
	}

	int elem = (base_ptr->ret->elem_dtype == T_UNDEF) ? T_INT : base_ptr->ret->elem_dtype;
	int esz;
	if (base_ptr->ret->ptr_level > 1)
		esz = size_of_dtype(T_PTR);
	else if (base_ptr->ret->tnode && ((TNode *)base_ptr->ret->tnode)->kind == T_ARRAY)
		esz = size_of_tnode((TNode *)base_ptr->ret->tnode);
	else
		esz = (elem == T_STRUCT) ? (base_ptr->ret->elem_sdef ? base_ptr->ret->elem_sdef->size : 0)
								 : size_of_dtype(elem);
	if (esz <= 0)
		esz = 4;

	SYM *t_mul = mk_tmp();
	TAC *d_mul = mk_tac(TAC_VAR, t_mul, NULL, NULL);
	TAC *m = mk_tac(TAC_MUL, t_mul, idx->ret, mk_const(esz));
	m->prev = d_mul;

	SYM *addr = mk_tmp_typed(T_PTR, elem, NULL, base_ptr->ret->elem_sdef);
	TAC *d_addr = mk_tac(TAC_VAR, addr, NULL, NULL);
	d_addr->prev = join_tac(base_ptr->tac, idx->tac);
	TAC *add = mk_tac(TAC_ADD, addr, base_ptr->ret, t_mul);
	add->prev = join_tac(d_addr, m);

	/* 元素为结构体或数组：返回元素地址（指针），供后续 . / [] 使用；否则正常 LOAD */
	if (elem == T_STRUCT || (base_ptr->ret->tnode && ((TNode *)base_ptr->ret->tnode)->kind == T_ARRAY))
	{
		if (base_ptr->ret->tnode && ((TNode *)base_ptr->ret->tnode)->kind == T_ARRAY)
		{
			addr->tnode = ((TNode *)base_ptr->ret->tnode)->elem;
			if (addr->tnode && ((TNode *)addr->tnode)->kind == T_ARRAY)
				addr->elem_dtype = T_ARRAY;
		}
		return mk_exp(NULL, addr, add);
	}
	else
	{
		SYM *ret = mk_tmp_typed(elem, T_UNDEF, NULL, NULL);
		TAC *d_ret = mk_tac(TAC_VAR, ret, NULL, NULL);
		d_ret->prev = add;
		TAC *ld = mk_tac(TAC_LOAD, ret, addr, NULL);
		ld->prev = d_ret;
		return mk_exp(NULL, ret, ld);
	}
}

/* a[idx] = rhs */
TAC *do_assign_index(SYM *base_var, EXP *idx, EXP *rhs)
{
	EXP *base = mk_exp(NULL, base_var, NULL);
	if (base_var->dtype == T_ARRAY)
		base = do_addr_var(base_var);
	else if (base_var->dtype != T_PTR)
		error("indexing non-pointer/non-array");

	int elem = (base->ret->elem_dtype == T_UNDEF) ? T_INT : base->ret->elem_dtype;
	int esz = (elem == T_STRUCT) ? (base->ret->elem_sdef ? base->ret->elem_sdef->size : 0)
								 : size_of_dtype(elem);
	if (esz <= 0)
		esz = 4;

	SYM *t_mul = mk_tmp();
	TAC *d_mul = mk_tac(TAC_VAR, t_mul, NULL, NULL);
	TAC *m = mk_tac(TAC_MUL, t_mul, idx->ret, mk_const(esz));
	m->prev = d_mul;

	SYM *addr = mk_tmp_typed(T_PTR, elem, NULL, base->ret->elem_sdef);
	TAC *d_addr = mk_tac(TAC_VAR, addr, NULL, NULL);
	d_addr->prev = join_tac(base->tac, idx->tac);
	TAC *add = mk_tac(TAC_ADD, addr, base->ret, t_mul);
	add->prev = join_tac(d_addr, m);

	TAC *store = mk_tac(TAC_STORE, addr, rhs->ret, NULL);
	store->prev = join_tac(add, rhs->tac);
	return store;
}

/* 通用版本：允许 base 表达式为指针或数组，例如 s.arr[i] = v / p[i] = v */
TAC *do_assign_index_exp(EXP *base_exp, EXP *idx, EXP *rhs)
{
	EXP *base_ptr = base_exp;
	if (base_exp->ret->dtype == T_ARRAY)
	{
		base_ptr = do_addr_var(base_exp->ret);
		if (base_exp->ret->tnode)
		{
			base_ptr->ret->tnode = ((TNode *)base_exp->ret->tnode)->elem;
			if (base_ptr->ret->tnode && ((TNode *)base_ptr->ret->tnode)->kind == T_ARRAY)
				base_ptr->ret->elem_dtype = T_ARRAY;
		}
	}
	else if (base_exp->ret->dtype != T_PTR)
	{
		error("indexing non-pointer/non-array");
	}

	int elem = (base_ptr->ret->elem_dtype == T_UNDEF) ? T_INT : base_ptr->ret->elem_dtype;
	int esz;
	if (base_ptr->ret->ptr_level > 1)
		esz = size_of_dtype(T_PTR);
	else if (base_ptr->ret->tnode && ((TNode *)base_ptr->ret->tnode)->kind == T_ARRAY)
		esz = size_of_tnode((TNode *)base_ptr->ret->tnode);
	else
		esz = (elem == T_STRUCT) ? (base_ptr->ret->elem_sdef ? base_ptr->ret->elem_sdef->size : 0)
								 : size_of_dtype(elem);
	if (esz <= 0)
		esz = 4;

	SYM *t_mul = mk_tmp();
	TAC *d_mul = mk_tac(TAC_VAR, t_mul, NULL, NULL);
	TAC *m = mk_tac(TAC_MUL, t_mul, idx->ret, mk_const(esz));
	m->prev = d_mul;

	SYM *addr = mk_tmp_typed(T_PTR, elem, NULL, base_ptr->ret->elem_sdef);
	TAC *d_addr = mk_tac(TAC_VAR, addr, NULL, NULL);
	d_addr->prev = join_tac(base_ptr->tac, idx->tac);
	TAC *add = mk_tac(TAC_ADD, addr, base_ptr->ret, t_mul);
	add->prev = join_tac(d_addr, m);

	TAC *store = mk_tac(TAC_STORE, addr, rhs->ret, NULL);
	store->prev = join_tac(add, rhs->tac);
	return store;
}

/* *ptr = rhs */
TAC *do_assign_deref(EXP *ptr_exp, EXP *rhs)
{
	TAC *store = mk_tac(TAC_STORE, ptr_exp->ret, rhs->ret, NULL);
	store->prev = join_tac(ptr_exp->tac, rhs->tac);
	return store;
}

/* 数组名在表达式位置衰变为指针 */
EXP *exp_from_symbol(SYM *s)
{
	if (s->dtype == T_ARRAY)
	{
		EXP *e = do_addr_var(s);
		if (s->tnode)
		{
			e->ret->tnode = ((TNode *)s->tnode)->elem;
			if (e->ret->tnode && ((TNode *)e->ret->tnode)->kind == T_ARRAY)
				e->ret->elem_dtype = T_ARRAY;
		}
		return e;
	}
	return mk_exp(NULL, s, NULL);
}

/* 取字段地址：base(.|->)field -> 统一得到指针值 */
static EXP *compute_field_addr(EXP *base, char *fname, int is_arrow)
{
	SDEF *def = NULL;
	EXP *base_ptr = NULL;

	if (!is_arrow)
	{
		if (!base->ret)
			error("'.' base must be a struct object");

		/* 辅助：提取 tnode 叶子类型（跳过多维数组层） */
		TNode *tn = (TNode *)base->ret->tnode;
		while (tn && tn->kind == T_ARRAY)
			tn = tn->elem;
		int leaf_kind = tn ? tn->kind : T_UNDEF;

		if (base->ret->dtype == T_STRUCT && base->ret->sdef)
		{
			/* 结构体变量：按取地址处理 */
			def = base->ret->sdef;
			if (base->ret->type != SYM_VAR)
				error("'.' base must be a variable");
			base_ptr = do_addr_var(base->ret);
		}
		else if (base->ret->dtype == T_PTR && base->ret->elem_dtype == T_STRUCT && base->ret->elem_sdef)
		{
			/* 指向结构体的指针，允许使用 '.' 视作 '->' */
			def = base->ret->elem_sdef;
			base_ptr = base;
		}
		else if (base->ret->dtype == T_PTR && base->ret->elem_dtype == T_ARRAY && leaf_kind == T_STRUCT)
		{
			/* 指向“结构体数组元素”的地址：索引后得到的指针，其 elem_dtype 可能是 T_ARRAY，tnode 叶子为 struct */
			def = tn ? tn->sdef : NULL;
			if (!def)
				error("'.' base struct array element unresolved");
			base_ptr = base;
		}
		else
		{
			error("'.' base must be a struct object");
		}
	}
	else
	{
		if (!base->ret || base->ret->dtype != T_PTR || base->ret->elem_dtype != T_STRUCT || !base->ret->elem_sdef)
		{
			fprintf(stderr, "debug: '->' base name=%s dtype=%d elem_dtype=%d elem_sdef=%p\n",
					base->ret ? base->ret->name : "(null)",
					base->ret ? base->ret->dtype : -1,
					base->ret ? base->ret->elem_dtype : -1,
					base->ret ? (void *)base->ret->elem_sdef : NULL);
			error("'->' base must be a pointer to struct");
		}
		def = base->ret->elem_sdef;
		base_ptr = base;
	}

	FIELD *fld = find_field(def, fname);
	if (!fld)
		error("unknown field: %s", fname);

	SYM *addr = mk_tmp_typed(T_PTR, T_UNDEF, NULL, NULL);
	TAC *d_addr = mk_tac(TAC_VAR, addr, NULL, NULL);
	TAC *code = join_tac(base_ptr->tac, d_addr);
	TAC *add = mk_tac(TAC_ADD, addr, base_ptr->ret, mk_const(fld->offset));
	add->prev = code;

	/* 供 LOAD/STORE 使用的按字节/字宽选择 */
	if (fld->dtype == T_ARRAY)
	{
		addr->elem_sdef = (fld->elem_dtype == T_STRUCT) ? fld->elem_sdef : NULL;
		/* 若是多维数组(tnode存在)，指针衰变应指向首元素：丢弃最外层一维 */
		if (fld->tnode)
		{
			TNode *full = (TNode *)fld->tnode; /* full 描述完整多维 */
			TNode *elem = full->elem;		   /* 首元素类型(去掉第一维) */
			addr->tnode = elem;				   /* 指针的 tnode 指向剩余维度 */
			if (elem && elem->kind == T_ARRAY)
			{
				addr->elem_dtype = T_ARRAY; /* 仍然是数组元素(还有多维) */
			}
			else if (elem && elem->kind == T_STRUCT)
			{
				addr->elem_dtype = T_STRUCT;
				addr->elem_sdef = elem->sdef;
			}
			else if (elem)
			{
				addr->elem_dtype = elem->kind; /* 标量叶子 */
			}
			else
			{
				/* 退化：没有 elem（不应发生），保持原 elem_dtype */
				addr->elem_dtype = fld->elem_dtype;
			}
		}
		else
		{
			/* 单维数组：指针指向标量/结构体元素 */
			addr->elem_dtype = fld->elem_dtype;
		}
	}
	else if (fld->dtype == T_STRUCT)
	{
		addr->elem_dtype = T_STRUCT;
		addr->elem_sdef = fld->sdef;
	}
	else if (fld->dtype == T_PTR)
	{
		addr->elem_dtype = T_PTR;
	}
	else
	{
		addr->elem_dtype = fld->dtype; /* 标量 */
		addr->elem_sdef = NULL;
	}
	addr->etc = (void *)fld; /* 关键：把字段描述传下去 */

	return mk_exp(NULL, addr, add);
}

EXP *do_field_select(EXP *base, char *fname, int is_arrow)
{
	EXP *addr = compute_field_addr(base, fname, is_arrow);
	FIELD *fld = (FIELD *)addr->ret->etc;

	int val_dtype = T_UNDEF, val_elem_dtype = T_UNDEF;
	SDEF *val_sdef = NULL, *val_elem_sdef = NULL;

	if (fld)
	{
		if (fld->dtype == T_ARRAY)
		{
			/* 数组字段：返回指向该数组首元素的指针值，供后续索引/指针算术使用。
			   在赋值到标量时，由 do_assign 进行自动解引用为 a[0]。 */
			return addr;
		}
		else if (fld->dtype == T_PTR)
		{
			/* 指针字段：保存其指向类型，支持后续 q->v */
			val_dtype = T_PTR;
			val_elem_dtype = fld->elem_dtype;
			if (val_elem_dtype == T_STRUCT)
				val_elem_sdef = fld->elem_sdef;
		}
		else if (fld->dtype == T_STRUCT)
		{
			error("cannot use whole struct as rvalue");
		}
		else
		{
			val_dtype = fld->dtype; /* 标量 */
		}
	}
	else
	{
		int elem = addr->ret->elem_dtype;
		if (elem == T_STRUCT)
			error("cannot use whole struct as rvalue");
		val_dtype = elem;
	}

	SYM *ret = mk_tmp_typed(val_dtype, val_elem_dtype, val_sdef, val_elem_sdef);
	TAC *d = mk_tac(TAC_VAR, ret, NULL, NULL);
	d->prev = addr->tac;
	TAC *ld = mk_tac(TAC_LOAD, ret, addr->ret, NULL);
	ld->prev = d;
	return mk_exp(NULL, ret, ld);
}

TAC *do_assign_field_select(EXP *base, char *fname, int is_arrow, EXP *rhs)
{
	EXP *addr = compute_field_addr(base, fname, is_arrow);
	TAC *store = mk_tac(TAC_STORE, addr->ret, rhs->ret, NULL);
	store->prev = join_tac(addr->tac, rhs->tac);
	return store;
}

/* 地址形式：& (base . fname) / & (base -> fname) */
EXP *addr_field_select(EXP *base, char *fname, int is_arrow)
{
	return compute_field_addr(base, fname, is_arrow);
}

/* 地址形式：& (base[idx]) */
EXP *addr_index(EXP *base, EXP *idx)
{
	EXP *base_ptr = base;
	if (base->ret->dtype == T_ARRAY)
	{
		base_ptr = do_addr_var(base->ret);
		if (base->ret->tnode)
		{
			base_ptr->ret->tnode = ((TNode *)base->ret->tnode)->elem;
			if (base_ptr->ret->tnode && ((TNode *)base_ptr->ret->tnode)->kind == T_ARRAY)
				base_ptr->ret->elem_dtype = T_ARRAY;
		}
	}
	else if (base->ret->dtype != T_PTR)
	{
		error("indexing non-pointer/non-array");
	}

	int elem = (base_ptr->ret->elem_dtype == T_UNDEF) ? T_INT : base_ptr->ret->elem_dtype;
	int esz;
	if (base_ptr->ret->ptr_level > 1)
		esz = size_of_dtype(T_PTR);
	else if (base_ptr->ret->tnode && ((TNode *)base_ptr->ret->tnode)->kind == T_ARRAY)
		esz = size_of_tnode((TNode *)base_ptr->ret->tnode);
	else
		esz = (elem == T_STRUCT) ? (base_ptr->ret->elem_sdef ? base_ptr->ret->elem_sdef->size : 0)
								 : size_of_dtype(elem);
	if (esz <= 0)
		esz = 4;

	SYM *t_mul = mk_tmp();
	TAC *d_mul = mk_tac(TAC_VAR, t_mul, NULL, NULL);
	TAC *m = mk_tac(TAC_MUL, t_mul, idx->ret, mk_const(esz));
	m->prev = d_mul;

	SYM *addr = mk_tmp_typed(T_PTR, elem, NULL, base_ptr->ret->elem_sdef);
	TAC *d_addr = mk_tac(TAC_VAR, addr, NULL, NULL);
	d_addr->prev = join_tac(base_ptr->tac, idx->tac);
	TAC *add = mk_tac(TAC_ADD, addr, base_ptr->ret, t_mul);
	add->prev = join_tac(d_addr, m);

	if (base_ptr->ret->tnode && ((TNode *)base_ptr->ret->tnode)->kind == T_ARRAY)
	{
		addr->tnode = ((TNode *)base_ptr->ret->tnode)->elem;
		if (addr->tnode && ((TNode *)addr->tnode)->kind == T_ARRAY)
			addr->elem_dtype = T_ARRAY;
	}
	return mk_exp(NULL, addr, add);
}

DLIST *dl_new(int len, DLIST *next)
{
	DLIST *p = (DLIST *)malloc(sizeof(DLIST));
	p->len = len;
	p->next = next;
	return p;
}

int dl_count(DLIST *p)
{
	int n = 0;
	for (; p; p = p->next)
		n++;
	return n;
}

void dl_to_array(DLIST *p, int *out)
{
	int n = dl_count(p);
	int k = n - 1;
	while (p)
	{
		out[k--] = p->len;
		p = p->next;
	}
}

SYM *get_var(char *name)
{
	SYM *sym = NULL; /* Pointer to looked up symbol */

	if (scope)
		sym = lookup_sym(sym_tab_local, name);

	if (sym == NULL)
		sym = lookup_sym(sym_tab_global, name);

	if (sym == NULL)
	{
		error("name not declared as local/global variable");
		return NULL;
	}

	if (sym->type != SYM_VAR)
	{
		error("not a variable");
		return NULL;
	}

	return sym;
}

EXP *mk_exp(EXP *next, SYM *ret, TAC *code)
{
	EXP *exp = (EXP *)malloc(sizeof(EXP));

	exp->next = next;
	exp->ret = ret;
	exp->tac = code;
	exp->dtype = ret ? ret->dtype : T_INT; // 默认 int 类型

	return exp;
}

SYM *mk_text(char *text)
{
	SYM *sym = NULL;

	sym = lookup_sym(sym_tab_global, text);
	if (sym != NULL)
		return sym;

	sym = mk_sym();
	sym->type = SYM_TEXT;
	sym->dtype = T_INT;
	sym->name = text;
	sym->label = next_label++;
	insert_sym(&sym_tab_global, sym);
	return sym;
}

SYM *mk_const(int n)
{
	SYM *sym = NULL;
	char name[16];
	sprintf(name, "%d", n);

	sym = lookup_sym(sym_tab_global, name);
	if (sym != NULL)
		return sym;

	sym = mk_sym();
	sym->type = SYM_INT;
	sym->dtype = T_INT;
	sym->value = n;
	sym->name = strdup(name);
	insert_sym(&sym_tab_global, sym);
	return sym;
}

/* 字符常量，避免与整型常量重名 */
SYM *mk_char(int ch)
{
	SYM *sym = NULL;
	char name[32];
	sprintf(name, "c:%d", (int)(unsigned char)ch);

	sym = lookup_sym(sym_tab_global, name);
	if (sym != NULL)
		return sym;

	sym = mk_sym();
	sym->type = SYM_CHAR;
	sym->dtype = T_CHAR;
	sym->value = (int)(unsigned char)ch;
	sym->name = strdup(name);
	insert_sym(&sym_tab_global, sym);
	return sym;
}

char *to_str(SYM *s, char *str)
{
	if (s == NULL)
		return "NULL";

	switch (s->type)
	{
	case SYM_FUNC:
	case SYM_VAR:
		return s->name;

	case SYM_TEXT:
		sprintf(str, "L%d", s->label);
		return str;

	case SYM_INT:
		sprintf(str, "%d", s->value);
		return str;

	case SYM_CHAR:
		sprintf(str, "%d", s->value); 
		return str;

	case SYM_LABEL: // 允许打印标签名
		return s->name;

	default:
		error("unknown TAC arg type");
		return "?";
	}
}

void out_str(FILE *f, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(f, format, args);
	va_end(args);
}

void out_sym(FILE *f, SYM *s)
{
	out_str(f, "%p\t%s", s, s->name);
}

void out_tac(FILE *f, TAC *i)
{
	char sa[12]; /* For text of TAC args */
	char sb[12];
	char sc[12];

	switch (i->op)
	{
	case TAC_UNDEF:
		fprintf(f, "undef");
		break;

	case TAC_ADD:
		fprintf(f, "%s = %s + %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

	case TAC_SUB:
		fprintf(f, "%s = %s - %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

	case TAC_MUL:
		fprintf(f, "%s = %s * %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

	case TAC_DIV:
		fprintf(f, "%s = %s / %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

	case TAC_EQ:
		fprintf(f, "%s = (%s == %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

	case TAC_NE:
		fprintf(f, "%s = (%s != %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

	case TAC_LT:
		fprintf(f, "%s = (%s < %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

	case TAC_LE:
		fprintf(f, "%s = (%s <= %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

	case TAC_GT:
		fprintf(f, "%s = (%s > %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

	case TAC_GE:
		fprintf(f, "%s = (%s >= %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

	case TAC_NEG:
		fprintf(f, "%s = - %s", to_str(i->a, sa), to_str(i->b, sb));
		break;

	case TAC_COPY:
		fprintf(f, "%s = %s", to_str(i->a, sa), to_str(i->b, sb));
		break;

	case TAC_GOTO:
		fprintf(f, "goto %s", i->a->name);
		break;

	case TAC_IFZ:
		fprintf(f, "ifz %s goto %s", to_str(i->b, sb), i->a->name);
		break;

	case TAC_ACTUAL:
		fprintf(f, "actual %s", to_str(i->a, sa));
		break;

	case TAC_FORMAL:
		fprintf(f, "formal %s", to_str(i->a, sa));
		break;

	case TAC_CALL:
		if (i->a == NULL)
			fprintf(f, "call %s", (char *)i->b);
		else
			fprintf(f, "%s = call %s", to_str(i->a, sa), (char *)i->b);
		break;

	case TAC_INPUT:
		fprintf(f, "input %s", to_str(i->a, sa));
		break;

	case TAC_OUTPUT:
		fprintf(f, "output %s", to_str(i->a, sa));
		break;

	case TAC_RETURN:
		fprintf(f, "return %s", to_str(i->a, sa));
		break;

	case TAC_LABEL:
		fprintf(f, "label %s", i->a->name);
		break;

	case TAC_VAR:
		fprintf(f, "var %s", to_str(i->a, sa));
		break;

	case TAC_CASE:
		if (i->a)
			fprintf(f, "case %s -> %s", to_str(i->a, sa), i->b->name);
		else
			fprintf(f, "default -> %s", i->b->name);
		break;

	case TAC_BREAK:
		fprintf(f, "break");
		break;

	case TAC_CONTINUE:
		fprintf(f, "continue");
		break;

	case TAC_BEGINFUNC:
		fprintf(f, "begin");
		break;

	case TAC_ENDFUNC:
		fprintf(f, "end");
		break;

	case TAC_STORE:
		fprintf(f, "*%s = %s", to_str(i->a, sa), to_str(i->b, sb));
		break;

	case TAC_LOAD:
		fprintf(f, "%s = *%s", to_str(i->a, sa), to_str(i->b, sb));
		break;

	case TAC_ADDR:
		fprintf(f, "%s = &%s", to_str(i->a, sa), to_str(i->b, sb));
		break;

	default:
		error("unknown TAC opcode");
		break;
	}
}
