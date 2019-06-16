// 1752762 ��1�� κ�ٴ�
#include <iostream>
#include <cstdlib>
#include "12-b2-linear_list_DL.h"	//��ʽ����

using namespace std;

/* ���캯������ʼ�����Ա� */
template<class ElemType>
LinkList<ElemType>::LinkList()
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	head = new LNode<ElemType>;
	if (head == NULL)
		exit(OVERFLOW);

	head->next = head->prior = head;
}

/* ����������ɾ�����Ա� */
template<class ElemType>
LinkList<ElemType>::~LinkList()
{
	LNode<ElemType> *q, *p = head->next;

	/* ����Ԫ��㿪ʼ�����ͷ� */
	while (p != head) {    //������Ϊ��(ֻ��ͷ���)����ѭ����ִ��
		q = p->next; //ץס�������һ�����
		delete p;
		p = q;
	}

	delete head;
	head = NULL;	//ͷָ����NULL
}

/* ������Ա�����ͷ��㣩 */
template<class ElemType>
Status LinkList<ElemType>::ClearList()
{
	LNode<ElemType> *q, *p = head->next;

	/* ����Ԫ��㿪ʼ�����ͷ� */
	while (p != head) {
		q = p->next;   //ץס�������һ�����
		delete p;
		p = q;
	}

	head->next = head->prior = head;	//ͷ���ǰ����ָ���Լ�
	return OK;
}

/* �ж��Ƿ�Ϊ�ձ� */
template<class ElemType>
Status LinkList<ElemType>::ListEmpty()
{
	/* �ж�ͷ����next�򼴿� */
	if (head->next == head)
		return TRUE;
	else
		return FALSE;
}

/* ���ĳ��� */
template<class ElemType>
int LinkList<ElemType>::ListLength()
{
	LNode<ElemType> *p = head->next; //ָ����Ԫ���
	int    len = 0;

	/* ѭ�������������м��� */
	while (p != head) {
		p = p->next;
		len++;
	}

	return len;
}

/* ȡ����Ԫ�� */
template<class ElemType>
Status LinkList<ElemType>::GetElem(int i, ElemType &e)
{
	LNode<ElemType> *p = head->next;	//ָ����Ԫ���
	int  pos = 1;		//��ʼλ��Ϊ1

	/* ����ΪNULL �� δ����i��Ԫ�� */
	while (p != head && pos < i) {
		p = p->next;
		pos++;
	}

	if (p == head || pos > i)
		return ERROR;

	e = p->data;
	return OK;
}

/* ���ҷ���ָ��������Ԫ�� */
template<class ElemType>
int LinkList<ElemType>::LocateElem(ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LNode<ElemType> *p = head->next;	//ָ����Ԫ���
	int  pos = 1;		//��ʼλ��Ϊ1

	/* ѭ����������  */
	while (p != head && (*compare)(e, p->data) == FALSE) {
		p = p->next;
		pos++;
	}

	return p != head ? pos : 0;
}

/* ���ҷ���ָ��������Ԫ�ص�ǰ��Ԫ�� */
template<class ElemType>
Status LinkList<ElemType>::PriorElem(ElemType cur_e, ElemType &pre_e)
{
	LNode<ElemType> *p = head->next;	//ָ����Ԫ���

	if (p == head)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �ӵ�2����㿪ʼѭ����������(����Ƚ���ȣ���֤��ǰ��) */
	while (p->next != head && p->next->data != cur_e)
		p = p->next;

	if (p->next == head) //δ�ҵ�
		return ERROR;

	pre_e = p->data;
	return OK;
}

/* ���ҷ���ָ��������Ԫ�صĺ��Ԫ�� */
template<class ElemType>
Status LinkList<ElemType>::NextElem(ElemType cur_e, ElemType &next_e)
{
	LNode<ElemType> *p = head->next;  //��Ԫ���

	if (p == head)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �к�̽���ҵ�ǰ���ֵ����ʱ���� */
	while (p->next != head && p->data != cur_e)
		p = p->next;

	if (p->next == head)
		return ERROR;

	next_e = p->next->data;
	return OK;
}

/* ��ָ��λ��ǰ����һ����Ԫ�� */
template<class ElemType>
Status LinkList<ElemType>::ListInsert(int i, ElemType e)
{
	LNode<ElemType> *s, *p = head->next;	//pָ��ͷ���
	int   pos = 0;

	/* Ѱ�ҵ�i-1����� */
	while (p != head && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (pos > i - 1)  //iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����

	s = new LNode<ElemType>;
	if (s == NULL)
		return OVERFLOW;

	s->data = e; 	//�½��������ֵ

	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;

	return OK;
}

/* ɾ��ָ��λ�õ�Ԫ�أ�������ɾ��Ԫ�ص�ֵ����e�з��� */
template<class ElemType>
Status LinkList<ElemType>::ListDelete(int i, ElemType &e)
{
	LNode<ElemType> *q, *p = head;	//pָ��ͷ���
	int   pos = 0;

	/* Ѱ�ҵ�i����㣨p->next�ǵ�i����㣩 */
	while (p->next != head && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == head || pos > i - 1)	//iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ��˵�i����㣬��ʱpָ���i-1�����

	q = p->next;       //qָ���i�����
	p->next = q->next; //��i-1������next��ָ���i+1��
	q->next->prior = p;

	e = q->data;      //ȡ��i������ֵ
	delete q;           //�ͷŵ�i�����

	return OK;
}

/* �������Ա� */
template<class ElemType>
Status LinkList<ElemType>::ListTraverse(Status(*visit)(ElemType e))
{
	extern int line_count; //��main�ж���Ĵ�ӡ���м����������㷨�޹أ�
	LNode<ElemType> *p = head->next;

	line_count = 0;		//�������ָ���ʼֵ�����㷨�޹أ�
	while (p != head && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p)
		return ERROR;

	cout << endl;	//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	return OK;
}
