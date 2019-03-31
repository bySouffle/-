//bysouffle
/**
  实验2.1栈的顺序表示和实现
    编写一个程序实现顺序栈的各种基本运算，并在此基础上设计一个主程序，完成如下功能：
    (1)初始化顺序栈。
    (2)插入元素。
    (3)删除栈顶元素。
    (4)取栈顶元素。
    (5)遍历顺序栈。
    (6)置空顺序栈。
**/
#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100		//储存空间初始分配量
#define STACKINCREMENT 10		//存储空间分配增量
#define TRUE 1
#define FALSE 0

typedef struct
{
	int *base;
	int * top;
	int stacksize;		//当前分配的空间大小
}SqStack;

int InitStack(SqStack &S)		//初始化顺序栈
{
	S.base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;

}

int Push(SqStack &S, int &e)		//入栈
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (int *)realloc(S.base, (S.stacksize + 10) * sizeof(int));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += 100;
	}
	*S.top++ = e;	//*S.top=e;S.top++
	return OK;
}

int Pop(SqStack &S)		//删除栈顶元素
{
	if (S.top == S.base)
		return ERROR;
	S.top--;
	return OK;
}

int GetTop(SqStack &S, int &e)		//取栈顶赋值给e
{
	if (S.top == S.base)
		return ERROR;
	e = *(S.top--);
	return OK;
}
int visit(int e)		//visit判断
{
	return e >= 0 ? TRUE : FALSE;
}

int StackTraverse(SqStack S, int (*visit)(int))		//遍历顺序栈
{
	for (int *p = S.top; p >= S.base; p--) 
	{
		if (!(*visit)(*--p))
			return ERROR;
		
	}
	return OK;
}

void StackPrint(SqStack S)		//输出栈中元素
{
	int *p = S.base;
	while (p != S.top)
	{
		int i = 1;
			printf("%d\t", *p++);
			i++;

	}
}

int ClearStack(SqStack &S)		//清空顺序栈
{
	while (S.top != S.base)
	{
		--S.top;
	}
	return OK;
}


int main()
{
	int e;
	SqStack S;
	InitStack(S);
	printf("初始化完成\n");		//初始化

	printf("--------插入元素1—9--------\n");		//插入元素
	for (int i = 1; i < 10; i++)
	{
		Push(S, i);
	}
	printf("插入完成\n");
	printf("输出栈中元素：\t");
	StackPrint(S);
	printf("\n");

	printf("--------删除栈顶元素--------\n");		//删除栈顶元素
	Pop(S);
	printf("删除后元素为：\t");
	StackPrint(S);
	printf("\n");
	printf("删除完成\n");

	printf("--------取栈顶元素--------\n");		//取栈顶元素赋予e
	GetTop(S, e);
	printf("取出的元素e = %d\n", e);
	printf("操作后元素为：\t");
	StackPrint(S);
	printf("\n");
	printf("操作成功\n");

	printf("--------遍历顺序栈--------\n");		//遍历
	StackPrint(S);
	StackTraverse(S, *visit) ? puts("全是正数") : puts("有负数");
	printf("\n");
	int x = -1;
	Push(S, x);
	StackPrint(S);
	StackTraverse(S, *visit) ? puts("全是正数") : puts("有负数");
	printf("\n");
	printf("--------置空顺序表--------\n");		//置空
	printf("操作前：\t");
	StackPrint(S);
	printf("\n");
	printf("操作后：\t");
	ClearStack(S);
	StackPrint(S);
	printf("\n");

	system("pause");



}
