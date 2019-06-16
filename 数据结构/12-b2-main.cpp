// 1752762 ��1�� κ�ٴ�
#include <iostream>
#include <iomanip>
#include "12-b2-linear_list_DL.cpp" 
#include "12-b2-double1.h"
#include "12-b2-student.h"

using namespace std;

#define INSERT_NUM		115		//��ʼ������е�Ԫ������
#define MAX_NUM_PER_LINE 	10		//ÿ����������Ԫ�ظ���

int line_count = 0;   //��ӡ����ʱ�ļ�����

//�������ֲ�������
//ͨ���ı�˴����������ͣ� int/double1/student/string
//#define ELEMTYPE_IS_INT	//ʵ������
//#define ELEMTYPE_IS_DOUBLE1
#define ELEMTYPE_IS_STRING
//#define ELEMTYPE_IS_STUDENT

#if defined ELEMTYPE_IS_DOUBLE1
#define MY_TYPE double1
#elif defined ELEMTYPE_IS_STRING
#define MY_TYPE string
#elif defined ELEMTYPE_IS_STUDENT
#define MY_TYPE student
#else
#define MY_TYPE int
#endif

/* ���ڱȽ�����ֵ�Ƿ���ȵľ��庯������LocateElem�еĺ���ָ�붨����ͬ������ʱ����
   int LocateElem(sqlist L, ElemType e, Status (*compare)(ElemType e1, ElemType e2)) */
template<class ElemType>
Status MyCompare(ElemType e1, ElemType e2)
{
	if (e1 == e2)
		return TRUE;
	else
		return FALSE;
}

/* ���ڷ���ĳ��Ԫ�ص�ֵ�ľ��庯������ListTraverse�еĺ���ָ�붨����ͬ������ʱ����
   Status ListTraverse(sqlist L, Status (*visit)(ElemType e)) */
template<class ElemType>
Status MyVisit(ElemType e)
{
	cout << setw(3) << e << "->";

	/* ÿ���MAX_NUM_PER_LINE������ӡһ������ */
	if ((++line_count) % MAX_NUM_PER_LINE == 0)
		cout << endl;

	return OK;
}

int main()
{
	LinkList<MY_TYPE> L;
	MY_TYPE e1, e2;
	int      i, pos;

	cout << "�ձ�=" << ((L.ListEmpty() == TRUE) ? "TRUE" : "FALSE") << endl;
	cout << "��=" << L.ListLength() << endl;

	cout << "����" << INSERT_NUM << "��Ԫ�أ�" << endl;

#if defined ELEMTYPE_IS_DOUBLE1
	for (i = INSERT_NUM; i > 0; i--)
		L.ListInsert(1, double(i)*0.1);
#elif defined ELEMTYPE_IS_STUDENT
	MY_TYPE e[] = { MY_TYPE(1001, "����", 'M', 76.5, "�Ϻ���������"),
					MY_TYPE(1002, "����", 'F', 87, "�Ϻ���������"),
					MY_TYPE(1003, "����", 'M', 80, "�㽭ʡ������"),
					MY_TYPE(1004, "����", 'M', 54, "�㽭ʡ������"),
					MY_TYPE(1005, "ţ��", 'F', 85, "����ʡ�Ͼ���"),
					MY_TYPE(1006, "���", 'M', 60, "����ʡ������") };
	for (i = 0; i < 6; i++)
		L.ListInsert(i + 1, *(e + i));
#elif  defined ELEMTYPE_IS_STRING
	MY_TYPE e[] = { MY_TYPE("�Ϻ���������"),
					MY_TYPE("�Ϻ���������"),
					MY_TYPE("�㽭ʡ������"),
					MY_TYPE("�㽭ʡ������"),
					MY_TYPE("����ʡ�Ͼ���"),
					MY_TYPE("����ʡ������") };
	for (i = 0; i < 6; i++)
		L.ListInsert(i + 1, *(e + i));
#else
	for (i = INSERT_NUM * 2; i > 0; i -= 2)
		L.ListInsert(1, i);
#endif


	L.ListTraverse(MyVisit);//�˴�����MyVisit������
	cout << endl;

	cout << "�ձ�=" << ((L.ListEmpty() == TRUE) ? "TRUE" : "FALSE") << endl;
	cout << "��=" << L.ListLength() << endl;

	/* �ֱ�ȡ��1������Լ�С�ڵ�1����������4������µĵ�Ԫ��ֵ��ǰ��ֵ�����ֵ
	   ����ټ�һ����������ֵ */
	for (i = 0; i < 5; i++) {
		int pos;
		switch (i) {
			case 0:
				pos = 1;
				break;
			case 1:
				pos = L.ListLength();
				break;
			case 2:
				pos = -1;
				break;
			case 3:
				pos = L.ListLength() + 1;
				break;
			case 4:
				cout << "������ҪȡԪ�ص�λ��[1.." << L.ListLength() << "]��" << endl;
				cin >> pos;
				break;
		}

		if (L.GetElem(pos, e1) == OK) {
			cout << "��" << pos << "��Ԫ��=" << e1 << endl;

			/* ֻ��ȡ����ĳ��Ԫ�أ�����ȡǰ���ͺ�� */
			if (L.PriorElem(e1, e2) == OK)
				cout << "��" << pos << "��Ԫ��(" << e1 << ")��ǰ��=" << e2 << endl;
			else
				cout << "�޷�ȡ�õ�" << pos << "��Ԫ��(" << e1 << ")��ǰ��" << endl;

			if (L.NextElem(e1, e2) == OK)
				cout << "��" << pos << "��Ԫ��(" << e1 << ")�ĺ��=" << e2 << endl << endl;
			else
				cout << "�޷�ȡ�õ�" << pos << "��Ԫ��(" << e1 << ")�ĺ��" << endl << endl;
		}
		else
			cout << "�޷�ȡ�õ�" << pos << "��Ԫ��" << endl << endl;
	} // end of for

	cout << "������Ҫ���ҵ�Ԫ�أ�" << endl;
	cin >> e1;
	if ((pos = L.LocateElem(e1, MyCompare)) > 0)
		cout << "Ԫ��" << e1 << "��λ��=" << pos << endl;
	else
		cout << "�Ҳ���Ԫ��" << e1 << endl;

	cout << endl << "������Ҫ����Ԫ�ص�ֵ��" << endl;
	cin >> e1;
	cout << "������Ҫ����Ԫ�ص�λ��" << endl;
	cin >> pos;
	if (L.ListInsert(pos, e1) == OK) {
		cout << "��" << pos << "ǰ����Ԫ��" << e1 << "�ɹ�" << endl;
		cout << "�±�Ϊ��" << endl;
		L.ListTraverse(MyVisit);
	}
	else
		cout << "��" << pos << "ǰ����Ԫ��" << e1 << "ʧ��" << endl;

	cout << endl << "������Ҫɾ��Ԫ�ص�λ��" << endl;
	cin >> pos;
	if (L.ListDelete(pos, e1) == OK) {
		cout << "ɾ����" << pos << "Ԫ��=" << e1 << "�ɹ�" << endl;
		cout << "�±�Ϊ��" << endl;
		L.ListTraverse(MyVisit);
	}
	else
		cout << "ɾ����" << pos << "Ԫ��=" << e1 << "ʧ��" << endl;

	cout << endl << "��ձ�" << endl;
	L.ClearList();
	cout << "�ձ�=" << ((L.ListEmpty() == TRUE) ? "TRUE" : "FALSE") << endl;
	cout << "��=" << L.ListLength() << endl;

	return 0;
}
