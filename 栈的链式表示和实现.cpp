//bysouffle
/**
  实验2. 2栈的链式表示和实现
    编写一个程序实现链栈的各种基本运算，并在此基础上设计一个主程序，完成如下功能：
    (1)初始化链栈。
    (2)链栈置空。
    (3)入栈。
    (4)出栈。
    (5)取栈顶元素。
    (6)遍历链栈。
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

typedef struct QNode		//定义节点
{
	int data;
	struct QNode *next;
}QNode, *Node;

typedef struct			//构造栈
{
	Node top, rear;

}LinkStack;

int InitStack(LinkStack &S)			//初始化栈
{
	S.rear = (QNode *)malloc(sizeof(QNode));		//开辟存储空间
	if (!S.rear)
		exit(OVERFLOW);
	S.top = S.rear;			//初始化节点
	S.top->data=0 ;
	S.top->next = NULL;		//防止野指针
	return OK;
}

int ClearStack(LinkStack &S)		//置空
{
	if (S.top == S.rear)
	{
		return ERROR;
	}
	else
	{
		Node p=NULL;
		
		 while(S.top!=S.rear)
		{
			p = S.top;
			S.top = S.top->next;
			
			free(p);
			p = NULL;
		} 

		return OK;
	}

}

int Push(LinkStack &S, int e)		//入栈
{
	Node p = (QNode *)malloc(sizeof(QNode));
	if (!p)
	{
		exit(OVERFLOW);
	}
	p->data = e;
	p->next = S.top;
	S.top = p;
	return OK;
}

int Pop(LinkStack &S)		//出栈
{
	if (S.top == S.rear)
	{
		return ERROR;
	}
	else
	{
		Node p;
		p = S.top;
		S.top = S.top->next;
		free(p);
	}
	return OK;
}

int GetTop(LinkStack &S, int &e)		//获取栈顶元素
{
	if (S.top == S.rear)
	{
		return ERROR;
	}
	else
	{
		return e = S.top->data;
	}
	
}

int visit(int e)
{
	printf("%d", e);
	return OK;
}
int StackTraverse(LinkStack &S)		//遍历
{
	Node p;
	p = S.top;
	while (p!=S.rear)
	{
		visit(p->data);
		p = p->next;
	}
	return OK;
}


int main()
{
	int e;
	LinkStack S;
	InitStack(S);
	printf("初始化完成\n");		//初始化

	printf("--------插入元素1—10--------\n");		//插入元素
	for (int i = 1; i < 10; i++)
	{
		Push(S, i);
	}
	printf("插入完成\n");
	printf("输出栈中元素：\t");
	
	StackTraverse(S);
	printf("\n");

	printf("--------删除栈顶元素--------\n");		//删除栈顶元素
	Pop(S);
	printf("删除后元素为：\t");
	StackTraverse(S);
	printf("\n");
	printf("删除完成\n");

	printf("--------取栈顶元素--------\n");		//取栈顶元素赋予e
	e = GetTop(S, e);
	printf("取出的元素e = %d\n", e);
	printf("操作后元素为：\t");
	StackTraverse(S);
	printf("\n");
	printf("操作成功\n");

	printf("--------遍历顺序栈--------\n");		//遍历
	StackTraverse(S);
	printf("\n");
	StackTraverse(S);
	printf("\n");
	printf("--------置空顺序表--------\n");		//置空
	printf("操作前：\t");
	StackTraverse(S);
	printf("\n");
	printf("操作后：\t");
	ClearStack(S);
	StackTraverse(S);
	printf("\n");
	printf("over");

	system("pause");



}
