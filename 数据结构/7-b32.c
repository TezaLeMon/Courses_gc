// 1752762 ��1�� κ�ٴ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>		//malloc/realloc����

/* P.10 ��Ԥ���峣�������� */
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

#define N 3

typedef int Status;

typedef struct student {
	int   num;
	char  name[10];
	char  sex;
	float score;
	char  addr[30];
} ElemType;

typedef struct DuLNode {
	ElemType      data;	//�������
	struct DuLNode *prior;	//���ֱ��ǰ����ָ��
	struct DuLNode *next;	//���ֱ�Ӻ�̵�ָ��
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
	p = (*L)->next;	//pָ���һ����� 
	while (p != *L) {	//pδָ����ͷ
		q = p->next;
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
		return ERROR;
	memcpy(&s->data, &e, sizeof(ElemType));

	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;

	return OK;
}

Status MyVisit(ElemType e)
{
	printf("%d-%s-%c-%f-%s->\n", e.num, e.name, e.sex, e.score, e.addr);
	return OK;
}

Status ListTraverse(DuLinkList L, Status(*visit)(ElemType e))
{
	DuLinkList p = L->next;

	while (p != L && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p != L)
		return ERROR;

	printf("\n");
	return OK;
}

int main()
{
	ElemType e[] = { {1001, "����", 'M', 76.5, "�Ϻ���������"},
		  {1002, "����", 'F', 87, "�Ϻ���������"},
		  {1003, "����", 'M', 80, "�㽭ʡ������"},
		  {1004, "����", 'M', 54, "�㽭ʡ������"},
		  {1005, "ţ��", 'F', 85, "����ʡ�Ͼ���"},
		  {1006, "���", 'M', 60, "����ʡ������"} };


	int i, pos;
	DuLinkList L;
	ElemType e1;

	InitList_DuL(&L);

	printf("����6��Ԫ�أ�\n");
	for (i = 0; i < 6; i++)
		ListInsert_DuL(&L, i + 1, *(e + i));

	ListTraverse(L, MyVisit);//�˴�����MyVisit������

	printf("���뵽��Ԫ֮ǰ:\n������Ҫ����Ԫ�ص�ֵ(ѧ�� ���� �Ա� �ɼ� ��ַ)��\n");
	scanf("%d %s %c %f %s", &e1.num, e1.name, &e1.sex, &e1.score, e1.addr);
	printf("\n");
	ListInsert_DuL(&L, 1, e1);
	ListTraverse(L, MyVisit);//�˴�����MyVisit������

	printf("���뵽β�ڵ��:\n������Ҫ����Ԫ�ص�ֵ(ѧ�� ���� �Ա� �ɼ� ��ַ)��\n");
	scanf("%d %s %c %f %s", &e1.num, e1.name, &e1.sex, &e1.score, e1.addr);
	printf("\n");
	ListInsert_DuL(&L, 8, e1);
	ListTraverse(L, MyVisit);//�˴�����MyVisit������

	for (i = 0; i < N; i++) {
		printf("������Ҫ����Ԫ�ص�λ��\n");
		scanf("%d", &pos);
		printf("������Ҫ����Ԫ�ص�ֵ(ѧ�� ���� �Ա� �ɼ� ��ַ)��\n");
		scanf("%d %s %c %f %s", &e1.num, e1.name, &e1.sex, &e1.score, e1.addr);
		printf("\n");
		ListInsert_DuL(&L, pos, e1);
		ListTraverse(L, MyVisit);//�˴�����MyVisit������
	}

	DestroyList_DuL(&L);
	return 0;
}