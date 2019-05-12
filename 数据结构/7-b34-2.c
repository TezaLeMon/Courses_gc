// 1752762 计1班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>		//malloc/realloc函数

/* P.10 的预定义常量和类型 */
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int Status;

typedef int ElemType;	//可根据需要修改元素的类型

typedef struct DuLNode {
	ElemType        data;	//存放数据
	struct DuLNode *prior;	//存放直接前驱的指针
	struct DuLNode *next;	//存放直接后继的指针
} DuLNode, *DuLinkList;

Status InitList(DuLinkList *L)
{
	/* 申请头结点空间，赋值给头指针 */
	*L = (DuLNode *)malloc(sizeof(DuLNode));
	if (*L == NULL)
		exit(OVERFLOW);

	(*L)->prior = *L;
	(*L)->next = *L;
	return OK;
}

/* 删除线性表 */
Status DestroyList(DuLinkList *L)
{
	DuLinkList q, p = *L; //指向首元

	/* 整个链表(含头结点)依次释放(同单链表，不考虑prior指针，只用next) */
	while (p != *L) {    //若链表为空，则循环不执行
		q = p->prior; //抓住链表的下一个结点
		free(p);
		p = q;
	}
	free(p);
	*L = NULL;	//头指针置NULL
	return OK;
}

/* 判断是否为空表 */
Status ListEmpty(DuLinkList L)
{
	/* 判断头结点的next域即可(同单链表) */
	if (L->next == L)
		return TRUE;
	else
		return FALSE;
}

/* 求表的长度 */
int ListLength(DuLinkList L)
{
	DuLinkList p = L->next; //指向首元结点
	int len = 0;

	/* 循环整个链表，进行计数 */
	while (p != L) {
		p = p->next;
		len++;
	}

	return len;
}

/* 在指定位置前插入一个新元素 */
Status ListInsert(DuLinkList *L, int i, ElemType e)
{
#if 0
	DuLinkList s, p = *L;	//p指向头结点
	int      pos = 1;

	/* 寻找第i个结点(i可能是表长+1) */
	while (p->next && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == NULL || pos > i - 1)  //i值非法则返回
		return ERROR;

	//执行到此表示找到指定位置，p指向第i-1个结点

	s = (DuLinkList)malloc(sizeof(DuLNode));
	if (s == NULL)
		return OVERFLOW;

	if (pos == i - 1) {
	}
	else {
		/* 注意，p可能是NULL */
		s->data = e; 	//新结点数据域赋值
		s->prior = p->prior;
		p->prior->next = s;
		s->next = p;	//新结点的next是第i个
		p->prior = s;	//第i-1个的next是新结点
	}
#else
	DuLinkList s, p = *L;	//p指向头结点
	int      pos = 0;

	/* 寻找第i-1个结点 */
	while (p && pos < i - 1) {
		p = p->prior;
		pos++;
	}

	if (p == NULL || pos > i)  //i值非法则返回
		return ERROR;

	//执行到此表示找到指定位置，p指向第i-1个结点
	s = (DuLinkList)malloc(sizeof(DuLNode));
	if (s == NULL)
		return OVERFLOW;

	s->data = e; 	//新结点数据域赋值

	s->next = p->next;  //新结点的next是第i个结点(即使p->next是NULL也没问题)
	s->prior = p;       //s的前驱是p
	p->next->prior = s;
	p->next = s;        //p的后继是s
#endif

	return OK;
}

/* 删除指定位置的元素，并将被删除元素的值放入e中返回 */
Status ListDelete(DuLinkList *L, int i, ElemType *e)
{
#if 1
	DuLinkList p = *L;	//p指向头结点
	int      pos = 0;

	/* 寻找第i个结点（p是第i个结点） */
	while (p && pos < i) {
		p = p->prior;
		pos++;
	}

	if (p == NULL || pos > i)	//i值非法则返回
		return ERROR;

	//执行到此表示找到了第i个结点，此时p指向第i个结点

	*e = p->data;      //取第i个结点的值
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);           //释放第i个结点
#else
	DuLinkList q, p = *L;	//p指向头结点
	int      pos = 0;

	/* 寻找第i个结点（p->next是第i个结点） */
	while (p->next && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == NULL || pos > i - 1)	//i值非法则返回
		return ERROR;

	//执行到此表示找到了第i个结点，此时p指向第i-1个结点

	q = p->next;       //q指向第i个结点
	p->next = q->next; //第i-1个结点的next域指向第i+1个(即使NULL也没错)
	if (q->next)
		q->next->prior = p;

	*e = q->data;      //取第i个结点的值
	free(q);           //释放第i个结点
#endif

	return OK;
}

/* 遍历线性表 */
Status ListTraverse(DuLinkList L, Status(*visit)(ElemType e))
{
	extern int line_count; //在main中定义的打印换行计数器（与算法无关）
	DuLinkList p = L->prior;
	line_count = 0;		//计数器恢复初始值（与算法无关）

#if 1
	while (p != L && (*visit)(p->data) == TRUE) //同单链表
		p = p->prior;

	if (p)
		return ERROR;

	printf("\n");//最后打印一个换行，只是为了好看，与算法无关
#else
	/* 逆序输出 */
	while (p->next) //同单链表
		p = p->next;

	/* 执行到此，p指向最后一个结点 */
	while (p && p->prior && (*visit)(p->data) == TRUE) //同单链表
		p = p->prior;

	printf("\n");//最后打印一个换行，只是为了好看，与算法无关
#endif

	return OK;
}

int line_count = 0;   //打印链表时的计数器

#define MAX_NUM_PER_LINE 	10		//每行最多输出的元素个数

/* 用于访问某个元素的值的具体函数，与ListTraverse中的函数指针定义相同，调用时代入
   Status ListTraverse(sqlist L, Status (*visit)(ElemType e)) */
Status MyVisit(ElemType e)
{
	printf("%3d->", e);

	/* 每输出MAX_NUM_PER_LINE个，打印一个换行 */
	if ((++line_count) % MAX_NUM_PER_LINE == 0)
		printf("\n");

	return OK;
}

void input(int *n, int *k, int *m) {
	printf("约瑟夫环\n输入总人数n：\n");
	scanf("%d", n);
	printf("从编号k开始：\n");
	scanf("%d", k);
	printf("数到m出列：\n");
	scanf("%d", m);
}

void creat(DuLinkList *L,int n)
{
	int i;
	for (i = 1; i <= n; i++)
		ListInsert(L, 1, i);
	ListTraverse(*L, MyVisit);	//此处传入MyVisit函数名
}

int main()
{
	DuLinkList L;
	ElemType e1 = 0;
	int      i;
	int n, m, k;

	InitList(&L);

	input(&n, &k, &m);

	creat(&L, n);

	int out, len;
	printf("\n出列顺序：");
	line_count = 0;
	for (i = k; !ListEmpty(L);) {
		len = ListLength(L);
		i %= len;
		if (i == 0)
			i = len;
		out = i + m;
		out %= len;
		if (out == 0)
			out = len;
		i = out;

		ListDelete(&L, out, &e1);
		printf("%3d", e1);
		if ((++line_count) % MAX_NUM_PER_LINE == 0)
			printf("\n");
	}

	DestroyList(&L);

	return 0;
}