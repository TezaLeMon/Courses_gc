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

typedef int Status;

typedef int ElemType;	//�ɸ�����Ҫ�޸�Ԫ�ص�����

typedef struct DuLNode {
	ElemType        data;	//�������
	struct DuLNode *prior;	//���ֱ��ǰ����ָ��
	struct DuLNode *next;	//���ֱ�Ӻ�̵�ָ��
} DuLNode, *DuLinkList;

Status InitList(DuLinkList *L)
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	*L = (DuLNode *)malloc(sizeof(DuLNode));
	if (*L == NULL)
		exit(OVERFLOW);

	(*L)->prior = *L;
	(*L)->next = *L;
	return OK;
}

/* ɾ�����Ա� */
Status DestroyList(DuLinkList *L)
{
	DuLinkList q, p = *L; //ָ����Ԫ

	/* ��������(��ͷ���)�����ͷ�(ͬ������������priorָ�룬ֻ��next) */
	while (p != *L) {    //������Ϊ�գ���ѭ����ִ��
		q = p->prior; //ץס�������һ�����
		free(p);
		p = q;
	}
	free(p);
	*L = NULL;	//ͷָ����NULL
	return OK;
}

/* �ж��Ƿ�Ϊ�ձ� */
Status ListEmpty(DuLinkList L)
{
	/* �ж�ͷ����next�򼴿�(ͬ������) */
	if (L->next == L)
		return TRUE;
	else
		return FALSE;
}

/* ���ĳ��� */
int ListLength(DuLinkList L)
{
	DuLinkList p = L->next; //ָ����Ԫ���
	int len = 0;

	/* ѭ�������������м��� */
	while (p != L) {
		p = p->next;
		len++;
	}

	return len;
}

/* ��ָ��λ��ǰ����һ����Ԫ�� */
Status ListInsert(DuLinkList *L, int i, ElemType e)
{
#if 0
	DuLinkList s, p = *L;	//pָ��ͷ���
	int      pos = 1;

	/* Ѱ�ҵ�i�����(i�����Ǳ�+1) */
	while (p->next && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == NULL || pos > i - 1)  //iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����

	s = (DuLinkList)malloc(sizeof(DuLNode));
	if (s == NULL)
		return OVERFLOW;

	if (pos == i - 1) {
	}
	else {
		/* ע�⣬p������NULL */
		s->data = e; 	//�½��������ֵ
		s->prior = p->prior;
		p->prior->next = s;
		s->next = p;	//�½���next�ǵ�i��
		p->prior = s;	//��i-1����next���½��
	}
#else
	DuLinkList s, p = *L;	//pָ��ͷ���
	int      pos = 0;

	/* Ѱ�ҵ�i-1����� */
	while (p && pos < i - 1) {
		p = p->prior;
		pos++;
	}

	if (p == NULL || pos > i)  //iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����
	s = (DuLinkList)malloc(sizeof(DuLNode));
	if (s == NULL)
		return OVERFLOW;

	s->data = e; 	//�½��������ֵ

	s->next = p->next;  //�½���next�ǵ�i�����(��ʹp->next��NULLҲû����)
	s->prior = p;       //s��ǰ����p
	p->next->prior = s;
	p->next = s;        //p�ĺ����s
#endif

	return OK;
}

/* ɾ��ָ��λ�õ�Ԫ�أ�������ɾ��Ԫ�ص�ֵ����e�з��� */
Status ListDelete(DuLinkList *L, int i, ElemType *e)
{
#if 1
	DuLinkList p = *L;	//pָ��ͷ���
	int      pos = 0;

	/* Ѱ�ҵ�i����㣨p�ǵ�i����㣩 */
	while (p && pos < i) {
		p = p->prior;
		pos++;
	}

	if (p == NULL || pos > i)	//iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ��˵�i����㣬��ʱpָ���i�����

	*e = p->data;      //ȡ��i������ֵ
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);           //�ͷŵ�i�����
#else
	DuLinkList q, p = *L;	//pָ��ͷ���
	int      pos = 0;

	/* Ѱ�ҵ�i����㣨p->next�ǵ�i����㣩 */
	while (p->next && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == NULL || pos > i - 1)	//iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ��˵�i����㣬��ʱpָ���i-1�����

	q = p->next;       //qָ���i�����
	p->next = q->next; //��i-1������next��ָ���i+1��(��ʹNULLҲû��)
	if (q->next)
		q->next->prior = p;

	*e = q->data;      //ȡ��i������ֵ
	free(q);           //�ͷŵ�i�����
#endif

	return OK;
}

/* �������Ա� */
Status ListTraverse(DuLinkList L, Status(*visit)(ElemType e))
{
	extern int line_count; //��main�ж���Ĵ�ӡ���м����������㷨�޹أ�
	DuLinkList p = L->prior;
	line_count = 0;		//�������ָ���ʼֵ�����㷨�޹أ�

#if 1
	while (p != L && (*visit)(p->data) == TRUE) //ͬ������
		p = p->prior;

	if (p)
		return ERROR;

	printf("\n");//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
#else
	/* ������� */
	while (p->next) //ͬ������
		p = p->next;

	/* ִ�е��ˣ�pָ�����һ����� */
	while (p && p->prior && (*visit)(p->data) == TRUE) //ͬ������
		p = p->prior;

	printf("\n");//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
#endif

	return OK;
}

int line_count = 0;   //��ӡ����ʱ�ļ�����

#define MAX_NUM_PER_LINE 	10		//ÿ����������Ԫ�ظ���

/* ���ڷ���ĳ��Ԫ�ص�ֵ�ľ��庯������ListTraverse�еĺ���ָ�붨����ͬ������ʱ����
   Status ListTraverse(sqlist L, Status (*visit)(ElemType e)) */
Status MyVisit(ElemType e)
{
	printf("%3d->", e);

	/* ÿ���MAX_NUM_PER_LINE������ӡһ������ */
	if ((++line_count) % MAX_NUM_PER_LINE == 0)
		printf("\n");

	return OK;
}

void input(int *n, int *k, int *m) {
	printf("Լɪ��\n����������n��\n");
	scanf("%d", n);
	printf("�ӱ��k��ʼ��\n");
	scanf("%d", k);
	printf("����m���У�\n");
	scanf("%d", m);
}

void creat(DuLinkList *L,int n)
{
	int i;
	for (i = 1; i <= n; i++)
		ListInsert(L, 1, i);
	ListTraverse(*L, MyVisit);	//�˴�����MyVisit������
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
	printf("\n����˳��");
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