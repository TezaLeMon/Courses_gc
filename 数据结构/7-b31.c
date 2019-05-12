// 1752762 计1班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc函数

# define MAXSIZE 1000

/* P.10 的预定义常量和类型 */
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int Status;

typedef int ElemType;

typedef struct LNode {
	ElemType      data;	//存放数据
	struct LNode *next;	//存放直接后继的指针
} LNode, *LinkList;


Status InitList(LinkList L)
{
	int i;
	for (i = 0; i < MAXSIZE - 1; i++) {
		L[i].next = &L[i + 1];
	}
	L[MAXSIZE - 1].next = NULL;

	return OK;
}

//从备用链表分配出一个结点
int Malloc(LinkList L)
{
	int i = L[0].next - L;
	if (L[0].next)	//判断备用链表是否为空 
		L[0].next = L[i].next;
	else
		return 0;
	return i;
}

//将下标为k的空闲结点回收到备用链表
Status Free(LinkList L, int k)
{
	L[k].next = L[0].next;
	L[0].next = &L[k];
	return OK;
}

Status difference(LinkList L, int S)
{
	int t, r, k, i, j, p;
	r = S;
	printf("输入集合 A 的元素:\n");
	for (j = 1; j < MAXSIZE; j++)
	{
		scanf("%d", &t);
		if (t == -1)
			break;
		i = Malloc(L);
		L[i].data = t;
		L[r].next = &L[i];
		r = i;
	}
	L[r].next = NULL;

	printf("输入集合 B 的元素:\n");
	for (j = 1; j < MAXSIZE; j++)
	{
		scanf("%d", &t);
		if (t == -1)
			break;
		p = S;
		k = L[S].next - L; 
		while (k != L[r].next - L && L[k].data != t)
		{
			p = k;
			k = L[k].next - L;
		}
		if (k == L[r].next - L)
		{
			i = Malloc(L);
			L[i].data = t;
			L[i].next = L[r].next;
			L[r].next = &L[i];
		}
		else
		{
			L[p].next = L[k].next;
			Free(L, k);
			if (r == k)
			{
				r = p;
				L[r].next = NULL;
			}
		}
	}
	return OK;
}



void Print(LinkList L, int S)
{
	int k, i = 0;
	LinkList p = L[S].next;
	k = p - L;
	while (p)
	{
		if (i % 10)
			printf("\n");
		printf("%d ", L[k].data);
		p = L[k].next;
		k = p - L;
	}
}


int main()
{
	LinkList L = (LinkList)malloc(sizeof(LNode)*MAXSIZE);
	InitList(L);
	int S = Malloc(L);	//生成头结点S  
	difference(L, S);
	Print(L, S);
	return 0;
}