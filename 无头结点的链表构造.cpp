#ifndef circularchain_
#define circularchain_
#include<iostream>
#include<string>    //数组
#include<algorithm> //STL中的算法
#include<sstream>  //istringstream流
#include<exception>//异常处理
#include<vector>//迭代器
#include<numeric>//标准库中的数学操作函数
#include<iterator>
#include<array>
#include "chainNode.h"
using namespace std;
template<typename T>
class circularchain
{
public:
	circularchain(int initialCapacity=10);
	
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;
	void reverse();
protected:
	chainNode<T>* firstNode;
	int listSize;
};
template<typename T>
circularchain<T>::circularchain(int initialCapacity)
{
	if (initialCapacity<1)
	{
		ostringstream s;
		s << "Initial capacity= " << initialCapacity << "Must be>0";
		throw illegalParameterValue(s.str());
	}
	firstNode=NULL;
}
//插入函数
template<typename T>
void circularchain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex == 0)
		firstNode= new chainNode<T>(theElement, firstNode);
	else
	{
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		p->next = new chainNode<T>(theElement, p->next);
		p->next->next = firstNode;               //让最后一个指针指向首位，形成闭环
	}
	listSize++;
}
//输出函数
template<typename T>
void circularchain<T>::output(ostream& out) const
{
	out << firstNode->element << " ";
	for (chainNode<T>*p=firstNode->next; p !=firstNode; p = p->next)
		 out << p->element << " ";
}
//循环链表的翻转函数
template<typename T>
void circularchain<T>::reverse()
{
	    chainNode<T>*pr,*r;
		
		chainNode<T>*p = firstNode->next;   //把链表分成两段
		firstNode->next = firstNode;      //从p里面拿出节点插入只有一个节点的链表，注意此只有一个节点的链表也是循环链表
		                                  
		pr= firstNode;                    //保存起初的起始位置，作为后面插入的末位置
	while (p!=pr)
	{
		r = p->next;                      //保存好下一次要插入的元素
		
		p->next = firstNode;              //进行节点插入
		pr->next=p;
		firstNode = p;
		p = r;
	}
}
 
/*
————————————————
版权声明：本文为CSDN博主「Jeff_Winger」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/Jeff_Winger/article/details/78312520
*/