//bysouffle
/**
   实验2.4队列的链式表示和实现
    编写一个程序实现链队列的各种基本运算，并在此基础上设计一个主程序，完成如下功能：
    (1)初始化并建立链队列。
    (2)入链队列。
    (3)出链队列。
    (4)遍历链队列。
**/
#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2



typedef struct QNode
{
	int data;
	struct QNode *next;

}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;

}LinkQueue;


int InitQueue(LinkQueue &Q)		//初始化
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front)
		exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;

}

int EnQueue(LinkQueue &Q, int e)		//入队
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;

	return OK;
}

int DeQueue(LinkQueue &Q, int &e)		//出队
{
           	if (Q.front == Q.rear)
		return ERROR;
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return OK;

}
int visit(int e)
{
	printf("%d", e);
	return OK;
}
int QueueTraverse(LinkQueue Q)
{
	QueuePtr q;
	if (Q.front == NULL)
		exit(OVERFLOW);
	q = Q.front->next;
	while (q) 
	{
		visit(q->data);
		q = q->next;
	}
	return OK;
}

int main()
{
	int i = 0;
	int e;
	LinkQueue Q;
	printf("初始化链队列...\n");
	InitQueue(Q);
	printf("%d 初始化成功\n", InitQueue(Q));
	printf("入链队列\n");		//入队
	for (i = 0; i <= 7; i++)
	{
		EnQueue(Q, i);
	}
	printf("操作成功");
	printf("打印队列元素：");
	QueueTraverse(Q);
	printf("\n");

	printf("出链队列\n");		//出队
	DeQueue(Q, e);
	printf("操作成功");
	printf("打印队列元素：");
	QueueTraverse(Q);
	printf("\n出队元素为：%d", e);
	printf("\n");

	printf("遍历链队列\n");		//遍历
	QueueTraverse(Q);

	system("pause");


}



