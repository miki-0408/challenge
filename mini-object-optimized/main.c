#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "tac.h"
#include "mini.y.h"
#include "obj.h"
#include "cfg.h"
#include "opt.h"

FILE *file_x, *file_s;
int yyparse();
void error(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	fprintf(stderr, "错误: 第 %d 行: ", yylineno);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(0);
}

void tac_list()
{
	out_str(file_x, "\n# tac list\n\n");
	fflush(file_x);

	TAC *cur;
	// long safe_guard = 200000; /* prevent infinite loop if list is corrupted */
	for (cur = tac_first; cur != NULL; cur = cur->next)
	{
		out_str(file_x, "%p\t", cur);
		out_tac(file_x, cur);
		out_str(file_x, "\n");
	}
	fflush(file_x);
}


int main(int argc, char *argv[])
{
	if (argc != 2)
		error("用法: %s <文件名>\n", argv[0]);

	char *input = argv[1];
	if (input[strlen(input) - 1] != 'm')
		error("%s 不是以 .m 结尾\n", input);

	if (freopen(input, "r", stdin) == NULL)
		error("打开 %s 失败\n", input);

	char *output = strdup(input);

	output[strlen(output) - 1] = 'x';
	if ((file_x = fopen(output, "w")) == NULL)
		error("打开 %s 失败\n", output);

	output[strlen(output) - 1] = 's';
	if ((file_s = fopen(output, "w")) == NULL)
		error("打开 %s 失败\n", output);

	tac_init();
	yyparse();
	opt_run_all(input);
	tac_list();
	tac_obj();
	fflush(file_s);
	cfg_build_and_dump_txt(input);
	fclose(file_s);
	fclose(file_x);

	return 0;
}
