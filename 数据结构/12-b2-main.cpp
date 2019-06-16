// 1752762 计1班 魏鹳达
#include <iostream>
#include <iomanip>
#include "12-b2-linear_list_DL.cpp" 
#include "12-b2-double1.h"
#include "12-b2-student.h"

using namespace std;

#define INSERT_NUM		115		//初始插入表中的元素数量
#define MAX_NUM_PER_LINE 	10		//每行最多输出的元素个数

int line_count = 0;   //打印链表时的计数器

//用以区分测试用例
//通过改变此处来更改类型！ int/double1/student/string
//#define ELEMTYPE_IS_INT	//实际无用
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

/* 用于比较两个值是否相等的具体函数，与LocateElem中的函数指针定义相同，调用时代入
   int LocateElem(sqlist L, ElemType e, Status (*compare)(ElemType e1, ElemType e2)) */
template<class ElemType>
Status MyCompare(ElemType e1, ElemType e2)
{
	if (e1 == e2)
		return TRUE;
	else
		return FALSE;
}

/* 用于访问某个元素的值的具体函数，与ListTraverse中的函数指针定义相同，调用时代入
   Status ListTraverse(sqlist L, Status (*visit)(ElemType e)) */
template<class ElemType>
Status MyVisit(ElemType e)
{
	cout << setw(3) << e << "->";

	/* 每输出MAX_NUM_PER_LINE个，打印一个换行 */
	if ((++line_count) % MAX_NUM_PER_LINE == 0)
		cout << endl;

	return OK;
}

int main()
{
	LinkList<MY_TYPE> L;
	MY_TYPE e1, e2;
	int      i, pos;

	cout << "空表=" << ((L.ListEmpty() == TRUE) ? "TRUE" : "FALSE") << endl;
	cout << "表长=" << L.ListLength() << endl;

	cout << "插入" << INSERT_NUM << "个元素：" << endl;

#if defined ELEMTYPE_IS_DOUBLE1
	for (i = INSERT_NUM; i > 0; i--)
		L.ListInsert(1, double(i)*0.1);
#elif defined ELEMTYPE_IS_STUDENT
	MY_TYPE e[] = { MY_TYPE(1001, "张三", 'M', 76.5, "上海市杨浦区"),
					MY_TYPE(1002, "李四", 'F', 87, "上海市普陀区"),
					MY_TYPE(1003, "王五", 'M', 80, "浙江省杭州市"),
					MY_TYPE(1004, "赵六", 'M', 54, "浙江省绍兴市"),
					MY_TYPE(1005, "牛七", 'F', 85, "江苏省南京市"),
					MY_TYPE(1006, "马八", 'M', 60, "江苏省苏州市") };
	for (i = 0; i < 6; i++)
		L.ListInsert(i + 1, *(e + i));
#elif  defined ELEMTYPE_IS_STRING
	MY_TYPE e[] = { MY_TYPE("上海市杨浦区"),
					MY_TYPE("上海市普陀区"),
					MY_TYPE("浙江省杭州市"),
					MY_TYPE("浙江省绍兴市"),
					MY_TYPE("江苏省南京市"),
					MY_TYPE("江苏省苏州市") };
	for (i = 0; i < 6; i++)
		L.ListInsert(i + 1, *(e + i));
#else
	for (i = INSERT_NUM * 2; i > 0; i -= 2)
		L.ListInsert(1, i);
#endif


	L.ListTraverse(MyVisit);//此处传入MyVisit函数名
	cout << endl;

	cout << "空表=" << ((L.ListEmpty() == TRUE) ? "TRUE" : "FALSE") << endl;
	cout << "表长=" << L.ListLength() << endl;

	/* 分别取第1、最后、以及小于第1、大于最后的4种情况下的的元素值、前驱值、后继值
	   最后再加一个任意输入值 */
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
				cout << "请输入要取元素的位序[1.." << L.ListLength() << "]：" << endl;
				cin >> pos;
				break;
		}

		if (L.GetElem(pos, e1) == OK) {
			cout << "第" << pos << "个元素=" << e1 << endl;

			/* 只有取得了某个元素，才能取前驱和后继 */
			if (L.PriorElem(e1, e2) == OK)
				cout << "第" << pos << "个元素(" << e1 << ")的前驱=" << e2 << endl;
			else
				cout << "无法取得第" << pos << "个元素(" << e1 << ")的前驱" << endl;

			if (L.NextElem(e1, e2) == OK)
				cout << "第" << pos << "个元素(" << e1 << ")的后继=" << e2 << endl << endl;
			else
				cout << "无法取得第" << pos << "个元素(" << e1 << ")的后继" << endl << endl;
		}
		else
			cout << "无法取得第" << pos << "个元素" << endl << endl;
	} // end of for

	cout << "请输入要查找的元素：" << endl;
	cin >> e1;
	if ((pos = L.LocateElem(e1, MyCompare)) > 0)
		cout << "元素" << e1 << "的位序=" << pos << endl;
	else
		cout << "找不到元素" << e1 << endl;

	cout << endl << "请输入要插入元素的值：" << endl;
	cin >> e1;
	cout << "请输入要插入元素的位序：" << endl;
	cin >> pos;
	if (L.ListInsert(pos, e1) == OK) {
		cout << "在" << pos << "前插入元素" << e1 << "成功" << endl;
		cout << "新表为：" << endl;
		L.ListTraverse(MyVisit);
	}
	else
		cout << "在" << pos << "前插入元素" << e1 << "失败" << endl;

	cout << endl << "请输入要删除元素的位序：" << endl;
	cin >> pos;
	if (L.ListDelete(pos, e1) == OK) {
		cout << "删除第" << pos << "元素=" << e1 << "成功" << endl;
		cout << "新表为：" << endl;
		L.ListTraverse(MyVisit);
	}
	else
		cout << "删除第" << pos << "元素=" << e1 << "失败" << endl;

	cout << endl << "清空表：" << endl;
	L.ClearList();
	cout << "空表=" << ((L.ListEmpty() == TRUE) ? "TRUE" : "FALSE") << endl;
	cout << "表长=" << L.ListLength() << endl;

	return 0;
}
