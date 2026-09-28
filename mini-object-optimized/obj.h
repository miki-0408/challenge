/* 寄存器编号定义 */
#define R_UNDEF -1
#define R_FLAG 0
#define R_IP 1
#define R_BP 2
#define R_JP 3
#define R_TP 4
#define R_GEN 5
#define R_NUM 16

/* 栈帧偏移常量 */
#define FORMAL_OFF -4 /* 第一个形参位置 */
#define OBP_OFF 0	  /* 动态链（上一帧的基址） */
#define RET_OFF 4	  /* 返回地址 */
#define LOCAL_OFF 8	  /* 局部变量起始位置 */

#define MODIFIED 1
#define UNMODIFIED 0

struct rdesc /* 寄存器描述符 */
{
	struct sym *var; /* 当前寄存器中的变量 */
	int mod;		 /* 是否被修改（脏） */
	int last_use;	 /* 最近使用计数（用于 LRU） */
};

extern int tos; /* 静态区顶部（全局区大小） */
extern int tof; /* 当前栈帧顶部 */
extern int oof; /* 形参区偏移（向下增长） */
extern int oon; /* 下一个栈帧的相对偏移（调用实参区累计） */

void tac_obj();
