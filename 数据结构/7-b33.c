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

#define N 5

typedef int Status;

typedef struct student {
	int   num;
	char  name[10];
	char  sex;
	float score;
	char  addr[30];
} ET, *ElemType;

typedef struct DuLNode {
	ElemType      data;	//存放数据
	struct DuLNode *prior;	//存放直接前驱的指针
	struct DuLNode *next;	//存放直接后继的指针
} DuLNode, *DuLinkList;

Status InitList_DuL(DuLinkList *L) {
	*L = (DuLinkList)malloc(sizeof(DuLNode));
	if (*L)
		(*L)->next = (*L)->prior = *L;
	else
		exit(OVERFLOW);
	return OK;
}

Status DestroyList_DuL(DuLinkList *L) {
	DuLinkList q, p;
	p = (*L)->next;	//p指向第一个结点 
	while (p != *L) {	//p未指到表头
		q = p->next;

		free(p->data);
		free(p);

		p = q;
	}
	free(*L);
	*L = NULL;
	return OK;
}

Status GetElemP_DuL(DuLinkList *L, int i, DuLinkList *e)
{
	DuLinkList p = (*L)->next;
	int j = 1;

	while (p != *L && j < i) {
		p = p->next;
		j++;
	}

	if (p == *L || j > i)
		return ERROR;

	*e = p;

	return OK;
}

Status ListInsert_DuL(DuLinkList *L, int i, ElemType e) {
	DuLinkList p = (*L)->next, s;

	int j = 1;
	while (p != *L && j < i) {
		p = p->next;
		j++;
	}
	if (j > i)
		return ERROR;

	s = (DuLinkList)malloc(sizeof(DuLNode));
	if (!s)
		return OVERFLOW;

	s->data = (ElemType)malloc(sizeof(ET));
	if (s->data == NULL)
		return OVERFLOW;
	memcpy(s->data, e, sizeof(ET));

	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;

	return OK;
}

Status ListDelete(DuLinkList *L, int i, ElemType *e) {
	DuLinkList p;
	if (i < 1)			//i值不合法
		return ERROR;

	if (!GetElemP_DuL(L, i, &p))	//第i个元素不存在
		return ERROR;

	memcpy(*e, p->data, sizeof(ET));

	p->prior->next = p->next;
	p->next->prior = p->prior;

	free(p->data);
	free(p);
	return OK;
}

Status MyVisit(ElemType e)
{
	printf("%d-%s-%c-%f-%s->\n", e->num, e->name, e->sex, e->score, e->addr);
	return OK;
}

Status ListTraverse(DuLinkList L, Status(*visit)(ElemType e))
{
	DuLinkList p = L->prior;

	while (p != L && (*visit)(p->data) == TRUE)
		p = p->prior;

	if (p != L)
		return ERROR;

	printf("\n");
	return OK;
}

int main()
{
	ET       e[] = { {1001, "张三", 'M', 76.5, "上海市杨浦区"},
		  {1002, "李四", 'F', 87, "上海市普陀区"},
		  {1003, "王五", 'M', 80, "浙江省杭州市"},
		  {1004, "赵六", 'M', 54, "浙江省绍兴市"},
		  {1005, "牛七", 'F', 85, "江苏省南京市"},
		  {1006, "马八", 'M', 60, "江苏省苏州市"} };

	int i, pos;
	DuLinkList L;
	ElemType e1 = (ElemType)malloc(sizeof(ET));

	InitList_DuL(&L);

	printf("插入6个元素：\n");
	for (i = 0; i < 6; i++)
		ListInsert_DuL(&L, i + 1, e + i);

	ListTraverse(L, MyVisit);//此处传入MyVisit函数名

	for (i = 0; i < N; i++) {
		printf("请输入要删除元素的位序\n");
		scanf("%d", &pos);
		printf("\n");
		if (ListDelete(&L, pos, &e1))
			ListTraverse(L, MyVisit);//此处传入MyVisit函数名
		else
			printf("输入位序不存在\n");
	}

	DestroyList_DuL(&L);
	return 0;
}