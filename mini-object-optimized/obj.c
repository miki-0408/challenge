#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include "tac.h"
#include "obj.h"

/* 全局生成状态 */
int tos; /* 静态区顶部（全局数据大小） */
int tof; /* 当前栈帧顶部 */
int oof; /* 形参区偏移 */
int oon; /* 下一帧相对偏移（调用参数累计） */
struct rdesc rdesc[R_NUM];
int reg_use_counter = 0;

static inline void touch_reg(int r)
{
	if (r >= 0 && r < R_NUM)
		rdesc[r].last_use = ++reg_use_counter;
}

void rdesc_clear(int r)
{
	rdesc[r].var = NULL;
	rdesc[r].mod = 0;
	rdesc[r].last_use = 0;
}

void rdesc_fill(int r, SYM *s, int mod)
{
	int old;
	for (old = R_GEN; old < R_NUM; old++)
	{
		if (rdesc[old].var == s)
		{
			rdesc_clear(old);
		}
	}

	rdesc[r].var = s;
	rdesc[r].mod = mod;
	touch_reg(r);
}

void asm_write_back(int r)
{
	if ((rdesc[r].var != NULL) && rdesc[r].mod)
	{
		if (rdesc[r].var->scope == 1) /* 局部变量写回到当前帧 */
		{
			out_str(file_s, "	STO (R%u+%u),R%u\n", R_BP, rdesc[r].var->offset, r);
		}
		else /* 全局变量写回到静态区 */
		{
			out_str(file_s, "	LOD R%u,STATIC\n", R_TP);
			out_str(file_s, "	STO (R%u+%u),R%u\n", R_TP, rdesc[r].var->offset, r);
		}
		rdesc[r].mod = UNMODIFIED;
	}
}

void asm_load(int r, SYM *s)
{
	/* already in a reg */
	for (int i = R_GEN; i < R_NUM; i++)
	{
		if (rdesc[i].var == s)
		{
			/* load from the reg */
			out_str(file_s, "	LOD R%u,R%u\n", r, i);

			/* update rdesc */
			rdesc_fill(r, s, rdesc[i].mod);
			touch_reg(r);
			return;
		}
	}

	/* 若不在寄存器中，根据类型执行加载 */
	switch (s->type)
	{
	case SYM_INT:
		out_str(file_s, "	LOD R%u,%u\n", r, s->value);
		break;

	case SYM_VAR:
		if (s->scope == 1) /* 局部变量 */
		{
			if ((s->offset) >= 0)
				out_str(file_s, "	LOD R%u,(R%u+%d)\n", r, R_BP, s->offset);
			else
				out_str(file_s, "	LOD R%u,(R%u-%d)\n", r, R_BP, -(s->offset));
		}
		else /* 全局变量 */
		{
			out_str(file_s, "	LOD R%u,STATIC\n", R_TP);
			out_str(file_s, "	LOD R%u,(R%u+%d)\n", r, R_TP, s->offset);
		}
		break;

	case SYM_TEXT:
		out_str(file_s, "	LOD R%u,L%u\n", r, s->label);
		break;
	}

	rdesc_fill(r, s, UNMODIFIED);
	touch_reg(r);
}

int reg_alloc(SYM *s)
{
	int r;

	/* 若变量已在寄存器中，直接返回该寄存器 */
	for (r = R_GEN; r < R_NUM; r++)
	{
		if (rdesc[r].var == s)
		{
			touch_reg(r);
			return r;
		}
	}

	/* 选择空寄存器 */
	for (r = R_GEN; r < R_NUM; r++)
	{
		if (rdesc[r].var == NULL)
		{
			asm_load(r, s);
			rdesc_fill(r, s, UNMODIFIED);
			touch_reg(r);
			return r;
		}
	}

	/* 选择未修改的最久未使用寄存器（LRU） */
	int cand = -1;
	int oldest = INT_MAX;
	for (r = R_GEN; r < R_NUM; r++)
	{
		if (!rdesc[r].mod)
		{
			if (rdesc[r].last_use < oldest)
			{
				oldest = rdesc[r].last_use;
				cand = r;
			}
		}
	}
	if (cand >= 0)
	{
		asm_load(cand, s);
		rdesc_fill(cand, s, UNMODIFIED);
		touch_reg(cand);
		return cand;
	}

	/* 否则选择最久未使用寄存器进行溢出写回（LRU） */
	cand = -1;
	oldest = INT_MAX;
	for (r = R_GEN; r < R_NUM; r++)
	{
		if (rdesc[r].last_use < oldest)
		{
			oldest = rdesc[r].last_use;
			cand = r;
		}
	}
	if (cand < 0)
		cand = R_GEN; /* fallback */
	asm_write_back(cand);
	asm_load(cand, s);
	rdesc_fill(cand, s, UNMODIFIED);
	touch_reg(cand);
	return cand;
}

void asm_bin(char *op, SYM *a, SYM *b, SYM *c)
{
	int reg_b = reg_alloc(b);
	int reg_c = reg_alloc(c);

	out_str(file_s, "	%s R%u,R%u\n", op, reg_b, reg_c);
	rdesc_fill(reg_b, a, MODIFIED);
}

void asm_cmp(int op, SYM *a, SYM *b, SYM *c)
{
	int reg_b = reg_alloc(b);
	int reg_c = reg_alloc(c);

	out_str(file_s, "	SUB R%u,R%u\n", reg_b, reg_c);
	out_str(file_s, "	TST R%u\n", reg_b);

	switch (op)
	{
	case TAC_EQ:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JEZ R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		break;

	case TAC_NE:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JEZ R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		break;

	case TAC_LT:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JLZ R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		break;

	case TAC_LE:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JGZ R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		break;

	case TAC_GT:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JGZ R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		break;

	case TAC_GE:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JLZ R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		break;
	}

	/* Delete c from the descriptors and insert a */
	rdesc_clear(reg_b);
	rdesc_fill(reg_b, a, MODIFIED);
}

void asm_cond(char *op, SYM *a, char *l)
{
	for (int r = R_GEN; r < R_NUM; r++)
		asm_write_back(r);

	if (a != NULL)
	{
		int r;

		for (r = R_GEN; r < R_NUM; r++) /* Is it in reg? */
		{
			if (rdesc[r].var == a)
				break;
		}

		if (r < R_NUM)
			out_str(file_s, "	TST R%u\n", r);
		else
			out_str(file_s, "	TST R%u\n", reg_alloc(a)); /* Load into new register */
	}

	out_str(file_s, "	%s %s\n", op, l);
}

void asm_call(SYM *a, SYM *b)
{
	int r;
	for (int r = R_GEN; r < R_NUM; r++)
		asm_write_back(r);
	for (int r = R_GEN; r < R_NUM; r++)
		rdesc_clear(r);
	out_str(file_s, "	STO (R2+%d),R2\n", tof + oon); /* store old bp */
	oon += 4;
	out_str(file_s, "	LOD R4,R1+32\n");			   /* return addr: 4*8=32 */
	out_str(file_s, "	STO (R2+%d),R4\n", tof + oon); /* store return addr */
	oon += 4;
	out_str(file_s, "	LOD R2,R2+%d\n", tof + oon - 8); /* load new bp */
	out_str(file_s, "	JMP %s\n", (char *)b);			 /* jump to new func */
	if (a != NULL)
	{
		r = reg_alloc(a);
		out_str(file_s, "	LOD R%u,R%u\n", r, R_TP);
		rdesc[r].mod = MODIFIED;
	}
	oon = 0;
}

void asm_return(SYM *a)
{
	for (int r = R_GEN; r < R_NUM; r++)
		asm_write_back(r);
	for (int r = R_GEN; r < R_NUM; r++)
		rdesc_clear(r);

	if (a != NULL) /* return value */
	{
		asm_load(R_TP, a);
	}

	out_str(file_s, "	LOD R3,(R2+4)\n"); /* return address */
	out_str(file_s, "	LOD R2,(R2)\n");   /* restore bp */
	out_str(file_s, "	JMP R3\n");		   /* return */
}

void asm_head()
{
	char head[] =
		"	# head\n"
		"	LOD R2,STACK\n"
		"	STO (R2),0\n"
		"	LOD R4,EXIT\n"
		"	STO (R2+4),R4\n";

	out_str(file_s, "%s", head);
}

void asm_tail()
{
	char tail[] =
		"\n	# tail\n"
		"EXIT:\n"
		"	END\n";

	out_str(file_s, "%s", tail);
}

void asm_str(SYM *s)
{
	char *t = s->name; /* The text */
	int i;

	out_str(file_s, "L%u:\n", s->label); /* Label for the string */
	out_str(file_s, "	DBS ");			 /* Label for the string */

	for (i = 1; t[i + 1] != 0; i++)
	{
		if (t[i] == '\\')
		{
			switch (t[++i])
			{
			case 'n':
				out_str(file_s, "%u,", '\n');
				break;

			case '\"':
				out_str(file_s, "%u,", '\"');
				break;
			}
		}
		else
			out_str(file_s, "%u,", t[i]);
	}

	out_str(file_s, "0\n"); /* End of string */
}

void asm_static(void)
{
	int i;

	SYM *sl;

	for (sl = sym_tab_global; sl != NULL; sl = sl->next)
	{
		if (sl->type == SYM_TEXT)
			asm_str(sl);
	}

	out_str(file_s, "STATIC:\n");
	out_str(file_s, "	DBN 0,%u\n", tos);
	out_str(file_s, "STACK:\n");
}

void asm_code(TAC *c)
{
	int r;

	switch (c->op)
	{
	case TAC_UNDEF:
		error("cannot translate TAC_UNDEF");
		return;

	case TAC_ADD:
		asm_bin("ADD", c->a, c->b, c->c);
		return;

	case TAC_SUB:
		asm_bin("SUB", c->a, c->b, c->c);
		return;

	case TAC_MUL:
		asm_bin("MUL", c->a, c->b, c->c);
		return;

	case TAC_DIV:
		asm_bin("DIV", c->a, c->b, c->c);
		return;

	case TAC_NEG:
		asm_bin("SUB", c->a, mk_const(0), c->b);
		return;

	case TAC_EQ:
	case TAC_NE:
	case TAC_LT:
	case TAC_LE:
	case TAC_GT:
	case TAC_GE:
		asm_cmp(c->op, c->a, c->b, c->c);
		return;

	case TAC_COPY:
		r = reg_alloc(c->b);
		rdesc_fill(r, c->a, MODIFIED);
		return;

	case TAC_INPUT:
		r = reg_alloc(c->a);
		out_str(file_s, "	ITI\n");
		out_str(file_s, "	LOD R%u,R15\n", r);
		rdesc[r].mod = MODIFIED;
		return;

	case TAC_OUTPUT:
		if (c->a->type == SYM_VAR)
		{
			r = reg_alloc(c->a);
			out_str(file_s, "	LOD R15,R%u\n", r);
			out_str(file_s, "	OTI\n");
		}
		else if (c->a->type == SYM_TEXT)
		{
			r = reg_alloc(c->a);
			out_str(file_s, "	LOD R15,R%u\n", r);
			out_str(file_s, "	OTS\n");
		}
		return;

	case TAC_GOTO:
		asm_cond("JMP", NULL, c->a->name);
		return;

	case TAC_IFZ:
		asm_cond("JEZ", c->b, c->a->name);
		return;

	case TAC_LABEL:
		for (int r = R_GEN; r < R_NUM; r++)
			asm_write_back(r);
		for (int r = R_GEN; r < R_NUM; r++)
			rdesc_clear(r);
		out_str(file_s, "%s:\n", c->a->name);
		return;

	case TAC_ACTUAL:
		r = reg_alloc(c->a);
		out_str(file_s, "	STO (R2+%d),R%u\n", tof + oon, r);
		oon += 4;
		return;

	case TAC_CALL:
		asm_call(c->a, c->b);
		return;

	case TAC_BEGINFUNC:
		/* We reset the top of stack, since it is currently empty apart from the link information. */
		scope = 1;
		tof = LOCAL_OFF;
		oof = FORMAL_OFF;
		oon = 0;
		return;

	case TAC_FORMAL:
		c->a->scope = 1; /* parameter is special local var */
		c->a->offset = oof;
		oof -= 4;
		return;

	case TAC_VAR:
		if (scope)
		{
			c->a->scope = 1; /* local var */
			c->a->offset = tof;
			tof += 4;
		}
		else
		{
			c->a->scope = 0; /* global var */
			c->a->offset = tos;
			tos += 4;
		}
		return;

	case TAC_RETURN:
		asm_return(c->a);
		return;

	case TAC_ENDFUNC:
		asm_return(NULL);
		scope = 0;
		return;

	default:
		/* Don't know what this one is */
		error("unknown TAC opcode to translate");
		return;
	}
}

void tac_obj()
{
	tof = LOCAL_OFF; /* TOS allows space for link info */
	oof = FORMAL_OFF;
	oon = 0;

	for (int r = 0; r < R_NUM; r++)
		rdesc[r].var = NULL;

	asm_head();

	TAC *cur;
	for (cur = tac_first; cur != NULL; cur = cur->next)
	{
		out_str(file_s, "\n	# ");
		out_tac(file_s, cur);
		out_str(file_s, "\n");
		asm_code(cur);
	}
	asm_tail();
	asm_static();
	fflush(file_s);
}
