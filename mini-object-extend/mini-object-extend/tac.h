/* type of symbol */
#define SYM_UNDEF 0
#define SYM_VAR 1
#define SYM_FUNC 2
#define SYM_TEXT 3
#define SYM_INT 4
#define SYM_LABEL 5
#define SYM_CHAR 6

/* 基本数据类型（语义类型） */
#define T_UNDEF 0
#define T_INT 1
#define T_CHAR 2
#define T_PTR 3
#define T_ARRAY 4
#define T_STRUCT 5

/* type of tac */
#define TAC_UNDEF 0		 /* undefine */
#define TAC_ADD 1		 /* a=b+c */
#define TAC_SUB 2		 /* a=b-c */
#define TAC_MUL 3		 /* a=b*c */
#define TAC_DIV 4		 /* a=b/c */
#define TAC_EQ 5		 /* a=(b==c) */
#define TAC_NE 6		 /* a=(b!=c) */
#define TAC_LT 7		 /* a=(b<c) */
#define TAC_LE 8		 /* a=(b<=c) */
#define TAC_GT 9		 /* a=(b>c) */
#define TAC_GE 10		 /* a=(b>=c) */
#define TAC_NEG 11		 /* a=-b */
#define TAC_COPY 12		 /* a=b */
#define TAC_GOTO 13		 /* goto a */
#define TAC_IFZ 14		 /* ifz b goto a */
#define TAC_BEGINFUNC 15 /* function begin */
#define TAC_ENDFUNC 16	 /* function end */
#define TAC_LABEL 17	 /* label a */
#define TAC_VAR 18		 /* int a */
#define TAC_FORMAL 19	 /* formal a */
#define TAC_ACTUAL 20	 /* actual a */
#define TAC_CALL 21		 /* a=call b */
#define TAC_RETURN 22	 /* return a */
#define TAC_INPUT 23	 /* input a */
#define TAC_OUTPUT 24	 /* output a */
#define TAC_CASE 25		 /* case entry: a=const (or NULL for default), b=label, etc=body TAC */
#define TAC_BREAK 26	 /* break (will be重写为 goto) */
#define TAC_CONTINUE 27	 /* continue (将被循环语义重写为 goto) */
#define TAC_ADDR 28		 /* a = &b */
#define TAC_LOAD 29		 /* a = *b (b 为指针值) */
#define TAC_STORE 30	 /* *a = b (a 为指针值) */

/* 多维数组维度链表类型 */
typedef struct dimlist
{
	int len;
	struct dimlist *next;
} DLIST;

/* 结构体字段与定义类型（供语法/语义层使用） */
typedef struct field
{
	char *name;
	int dtype;					  /* T_INT/T_CHAR/T_PTR/T_ARRAY/T_STRUCT */
	int elem_dtype;				  /* 指针/数组元素类型 */
	int ptr_level;				  /* 指针层级 */
	void *tnode;				  /* 若为多维数组，指向类型结点（TNode） */
	int array_len;				  /* 数组长度（0 代表未定长或按 0 处理） */
	struct struct_def *sdef;	  /* 若字段自身为结构体，指向定义 */
	struct struct_def *elem_sdef; /* 若字段为指针/数组且元素为结构体 */
	int offset;					  /* 字段偏移（定义完成后填充） */
	struct field *next;
} FIELD;

typedef struct struct_def
{
	char *name;	   /* 标签名（可为匿名，内部生成） */
	FIELD *fields; /* 字段链表 */
	int size;	   /* 结构体总大小（简单顺序打包，无对齐） */
	struct struct_def *next;
} SDEF;

typedef struct sym
{
	int type;  /* 符号类别：SYM_VAR/SYM_FUNC/SYM_INT/... */
	int dtype; /* 语义类型：T_INT/T_CHAR/T_PTR/T_ARRAY/T_STRUCT */
	int scope; /* 0:global, 1:local */
	char *name;
	int offset;
	int value;
	int label;
	struct tac *address; /* SYM_FUNC */
	struct sym *next;
	void *etc;

	/* 复合类型信息 */
	int elem_dtype; /* 指针/数组的元素类型（T_INT/T_CHAR/…/T_STRUCT） */
	int ptr_level;	/* 指针层级 */
	int array_len;	/* 数组长度（一维），参数数组按指针处理可置 0 */

	/* 结构体信息 */
	SDEF *sdef;		 /* 若自身是 T_STRUCT，则指向结构体定义 */
	SDEF *elem_sdef; /* 若元素类型是结构体（指针/数组），指向元素结构体定义 */

	/* 数组类型信息（用于多维数组） */
	void *tnode; /* 指向内部类型描述结点，具体结构在 tac.c 中定义 */
} SYM;

typedef struct tac
{
	struct tac *next;
	struct tac *prev;
	int op;
	SYM *a;
	SYM *b;
	SYM *c;
	void *etc;
} TAC;

typedef struct exp
{
	struct exp *next; /* for argument list */
	TAC *tac;		  /* code */
	SYM *ret;		  /* return value */
	int dtype;		  /* 表达式类型 */
	void *etc;
} EXP;

/* global var */
extern FILE *file_x, *file_s;
extern int yylineno, scope, next_tmp, next_label;
extern SYM *sym_tab_global, *sym_tab_local;
extern TAC *tac_first, *tac_last;
extern SYM *parser_switch_end; /* set by parser when parsing switch to support break */

/* 当前声明类型与当前函数（用于类型检查） */
extern int current_type; 
extern SYM *current_function;
extern SDEF *current_sdef;
extern int current_elem_dtype;	/* 指针/数组的元素类型 */
extern int current_ptr_level;	/* 指针层级（当前用 0/1） */
extern int current_array_len;	/* 数组长度（0 表未指定） */
extern SDEF *current_elem_sdef; /* 若元素类型是结构体 */

/* function */
void tac_init();
void tac_complete();
TAC *join_tac(TAC *c1, TAC *c2);
void out_str(FILE *f, const char *format, ...);
void out_sym(FILE *f, SYM *s);
void out_tac(FILE *f, TAC *i);
SYM *mk_label(char *name);
SYM *mk_tmp(void);
SYM *mk_const(int n);
SYM *mk_text(char *text);
SYM *mk_char(int ch); /* 字符常量 */
TAC *mk_tac(int op, SYM *a, SYM *b, SYM *c);
EXP *mk_exp(EXP *next, SYM *ret, TAC *code);
char *mk_lstr(int i);
SYM *get_var(char *name);
SYM *declare_func(char *name);
TAC *declare_var(char *name);
TAC *declare_para(char *name);
TAC *do_func(SYM *name, TAC *args, TAC *code);
TAC *do_assign(SYM *var, EXP *exp);
TAC *do_output(SYM *var);
TAC *do_input(SYM *var);
TAC *do_call(char *name, EXP *arglist);
TAC *do_if(EXP *exp, TAC *stmt);
TAC *do_test(EXP *exp, TAC *stmt1, TAC *stmt2);
TAC *do_while(EXP *exp, TAC *stmt);
TAC *do_switch(EXP *switch_exp, TAC *case_list);
TAC *do_for(TAC *init, EXP *cond, TAC *iter, TAC *body);
TAC *do_do_while(EXP *cond, TAC *body);
EXP *do_logic_and(EXP *e1, EXP *e2);
EXP *do_logic_or(EXP *e1, EXP *e2);
EXP *do_bin(int binop, EXP *exp1, EXP *exp2);
EXP *do_cmp(int binop, EXP *exp1, EXP *exp2);
EXP *do_un(int unop, EXP *exp);
EXP *do_call_ret(char *name, EXP *arglist);
/* 指针/数组 */
int size_of_dtype(int dtype);
TAC *declare_var_ptr(char *name, int level);
TAC *declare_var_array(char *name, int len);
TAC *declare_para_ptr(char *name, int level);
TAC *declare_para_array(char *name, int len);

EXP *do_addr_var(SYM *var);
EXP *do_deref(EXP *ptr_exp);
EXP *do_index(EXP *base, EXP *idx); /* 读取 base[idx] */
TAC *do_assign_index(SYM *base_var, EXP *idx, EXP *rhs);
TAC *do_assign_index_exp(EXP *base_exp, EXP *idx, EXP *rhs);
TAC *do_assign_deref(EXP *ptr_exp, EXP *rhs);
EXP *exp_from_symbol(SYM *s);
/* 结构体与 typedef */
SDEF *struct_define(char *tag, FIELD *fields);
SDEF *struct_lookup(const char *tag);
/* 若不存在则创建占位的结构体标签（size=0, fields=NULL） */
SDEF *struct_forward(const char *tag);
FIELD *field_from_current(char *name, int ptr_level, int array_len);
FIELD *field_from_current_dl(char *name, int ptr_level, DLIST *dims);
FIELD *field_join(FIELD *list, FIELD *item);

void typedef_add(const char *name, int dtype, int elem_dtype, int ptr_level, int array_len, SDEF *sdef, SDEF *elem_sdef);
int is_typedef_name(const char *name);
int typedef_get(const char *name, int *dtype, int *elem_dtype, int *ptr_level, int *array_len, SDEF **sdef, SDEF **elem_sdef);

/* 成员访问与赋值 */
EXP *do_field_select(EXP *base, char *fname, int is_arrow);
TAC *do_assign_field_select(EXP *base, char *fname, int is_arrow, EXP *rhs);

/* 按符号求大小（含结构体与结构体数组） */
int size_of_symbol(SYM *s);
int size_of_symbol_elem(SYM *s);
FIELD *field_from_current(char *name, int ptr_level, int array_len);
void error(const char *format, ...);

/* 多维数组支持 */
/* 通过维度数组声明多维数组变量（例如 lens=[10,20,30] 表示 a[10][20][30]） */
TAC *declare_var_array_multi_lens(char *name, int *lens, int n);

/* 取地址扩展：字段与下标的地址 */
/* & (base . fname) / & (base -> fname) */
EXP *addr_field_select(EXP *base, char *fname, int is_arrow);
/* & (base[idx]) */
EXP *addr_index(EXP *base, EXP *idx);

DLIST *dl_new(int len, DLIST *next);
int dl_count(DLIST *p);
void dl_to_array(DLIST *p, int *out);