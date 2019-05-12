// 1752762 ��1�� κ�ٴ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc����

# define MAXSIZE 1000

/* P.10 ��Ԥ���峣�������� */
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int Status;

typedef int ElemType;

typedef struct LNode {
	ElemType      data;	//�������
	struct LNode *next;	//���ֱ�Ӻ�̵�ָ��
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

//�ӱ�����������һ�����
int Malloc(LinkList L)
{
	int i = L[0].next - L;
	if (L[0].next)	//�жϱ��������Ƿ�Ϊ�� 
		L[0].next = L[i].next;
	else
		return 0;
	return i;
}

//���±�Ϊk�Ŀ��н����յ���������
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
	printf("���뼯�� A ��Ԫ��:\n");
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

	printf("���뼯�� B ��Ԫ��:\n");
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
	int S = Malloc(L);	//����ͷ���S  
	difference(L, S);
	Print(L, S);
	return 0;
}