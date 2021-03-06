//editor:bysouffle

/**
实验1.2单链表的操作
    请编制C程序，利用链式存储方式来实现线性表的创建、插入、删除和查找等操作。具体地说，就是要根据键盘输入的数据建立一个单链表，
并输出该单链表；然后根据屏幕菜单的选择，可以进行数据的插入或删除，并在插入或删除数据后，再输出单链表；最后在屏幕菜单中选择0，即
可结束程序的运行。
算法描述：本实验要求分别写出在带头结点的单链表中第i(从1开始计数）个位置插入元素、创建带头结点的单链表、在带头结点的单链表中删除
第i个位置的元素、顺序输出单链表的内容等的算法描述。
实验1.3 在完成实验1.2的基础上完成练习五的第1、8小题。
 1.单链表L是一个递减有序表，试编写高效算法，删除表中值大于min且小于max的结点，同时释放被删结点的空间，这里min和max是两个给定的
 参数。请分析你的算法时间复杂度。
 8.已知带头结点的单链表L中的结点是按整数值递增排列的，试写一算法，将值为x的结点插入到表L中，使得L仍然递增有序，并且分析算法的时
 间复杂度。
**/

#include<stdlib.h>
#include<stdio.h>

#define List_int_size 100  //初始分配量
#define Listincrement 10  //增加分配量
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996)
#pragma warning( disable : 4477)
#pragma warning( disable : 4703)


typedef struct LNode		//单链表存储结构
{
	int  data;		
	struct LNode *next;	
} LNode, *LinkList;


void CreateList_L(LinkList &L, int n)		//逆位序输入n个元素的值，建立带表头结点的单链表线性表
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;			// 先建立一个带头节点的单链表
	for (int i = n; i > 0; --i) 
	{
		LinkList p;			// 生成新的节点
		p = (LinkList)malloc(sizeof(LNode));		
		
		scanf("%d", &p->data);		// 输入新的节点的值
		p->next = L->next;		//插入到表头
		L->next = p;
	}
}





int display_L(LinkList L)		//输出所有元素
{
	printf("线性单链表为：");
	LinkList p = L->next;
	while (p != NULL)
	{
		printf("%d  ", p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}



int ListInsert_L(LinkList &L, int i, int e)
{
	//带头节点的单链表L中第i个位置之前插入元素e
	LinkList p;
	p = L;
	int j = 0;
	while (p && i - 1 > j)		//寻找第i-1个节点
	{ 
		p = p->next; 
		++j; 
	}  
	if (!p || j > i - 1) 
		return ERROR;		// i小于1或者大于表长加1
	LinkList s = (LinkList)malloc(sizeof(LNode));		//生成新的结点
	s->data = e;	//插入L中
	s->next = p->next;			
	p->next = s;
	return OK;
}



int ListDelete_L(LinkList &L, int i, int e)
{
	//在带头结点的单链表线性表L中，删除第i个元素，并由e返回其值
	LinkList p = L;
	int j = 0;
	while (p->next && j < i - 1)		//寻找第i个节点，并令p指向其前驱
	{
		p = p->next; ++j;
	}
	if (!(p->next) || j > i - 1) return ERROR;		//删除位置不合理
	LinkList q = p->next; p->next = p->next->next;		//删除并释放节点
	e = q->data; free(q);
	return  OK;
}


int GetElem_L(LinkList L, int i, int &e)
{
	//L为带头节点的头指针
	//当第i个元素存在时，其赋值给e并返回OK,否则ERROR
	LinkList p;
	p = L->next;
	int j = 1;		// 初始化p指向第一个节点，j计数器
	while (p && j < i) {
		p = p->next; ++j;
	}
	if (!p || j > i) return ERROR;
	e = p->data;
	printf("查找的元素为 %d\n", e);
	return OK;
}


int  Del_min_max(LinkList L, int min, int max)
{
	LNode *p, *q, *s;
	p = L;
	while (p->next && p->next->data >= max)		//找比max大的前一个元素位置 
		p = p->next;		//p指向第一个不大于max结点的前驱
		q = p->next;		//q指向第一个大于max的结点 
	while (q &&q->data > min)		//找比min大的第一个元素位置
	{
		s = q; 
		q = q->next;
		free(s);		//删除结点
	}
	p->next = q;
	return OK;
}


int Insert_2(LinkList L, int e)			//递增单链表插入
{
	LinkList p, q, s;
	p = L;
	
	while (p->next && p->next->data < e)		//寻找小于e的位置
	{
		s = (LinkList)malloc(sizeof(LNode));		//生成新的结点
		s->data = e;		//插入数据
		q = p->next;		
		p = p->next;
	}
	q->next = s;
	s->next = p;
	return OK;
}

void menu()
{

	printf("\n*********************************\n");
	printf("****  1.创建        2.插入   ****\n");
	printf("****  3.删除        4.查找   ****\n");
	printf("****  5.删除min_max间的结点  ****\n");
	printf("****  6.递增单链表插入       ****\n");
	printf("****  0.退出                 ****\n");
	printf("*********************************\n");
}
enum op
{
	EXIT,
	CREATE,
	INSERT,
	DEL,
	LOCATE,
	MIN_MAX,
	INS_2,
};		//对应switch


int main()
{

	LinkList L;
	int i = 1;
	while (i)
	{
		menu();
		printf("请选择：");
		scanf("%d", &i);
		switch (i)
		{
		case CREATE:		//建立链表
			printf("请输入节点个数:");
			int n;
			scanf("%d", &n);
			printf("逆位序输入元素的值：");
			CreateList_L(L, n);
			display_L(L);
			break;


		case INSERT:		//插入元素
			
			int i, e;
			printf("插入位数 i = ");
			scanf("%d", &i);
			printf("插入元素 e = ");
			scanf("%d", &e);
			ListInsert_L(L, i, e);
			display_L(L);
			break;

		case DEL:		//删除元素
		
			printf("删除元素位数 i = ");
			scanf("%d", &i);
			ListDelete_L(L, i, e);
			display_L(L);
			break;

		case LOCATE:		//定位元素
			printf("查找的第i元素i = ");
			scanf("%d", &i);
			e = GetElem_L(L,i ,e);
			
		case MIN_MAX:		//删除min与max间元素
			printf("请输入节点个数:");
			scanf("%d", &n);
			printf("递增输入元素的值：");
			CreateList_L(L, n);
			display_L(L);
			int a, b;
			printf("请输入删除元素最小值 min = ");
			scanf("%d", &a);
			printf("请输入删除元素最大值 max = ");
			scanf("%d", &b);
			Del_min_max(L, a, b);
			display_L(L);
			break;

		case INS_2:		//删除min与max间元素
			printf("请输入节点个数:");
			scanf("%d", &n);
			printf("递减输入元素的值：");
			CreateList_L(L, n);
			display_L(L);
			printf("请输入插入元素 e = ");
			scanf("%d", &e);
			Insert_2(L,e);
			display_L(L);
			break;
		case EXIT:		//退出
			exit(0);

		default:
			printf("选择错误");
			break;
		}
	}
}
