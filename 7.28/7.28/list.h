#pragma once
#include<iostream>
#include <stdio.h>
#include <assert.h>
#include "ReserveIterator.h"
using namespace std;
namespace tao
{

	template <class T>
	struct listNode
	{
		listNode<T>* next;
		listNode<T>* prev;
		T val;
		listNode(const T& val = T())
			:next(nullptr)
			, prev(nullptr)
			, val(val)
		{}
	};
	template <class T, class Ref,class Ptr>
	struct _list_iterator
	{
		typedef listNode<T> Node;
		typedef _list_iterator<T, Ref,Ptr> Self;
		_list_iterator(Node* node)
			:_node(node)
		{}
		Ref operator*()//重载*运算符因为原生指针中的解引用不符合list迭代要求
		{
			return _node->val;
		}
		Ptr operator->()  //const对象使用 返回的应该是const T *
		{
			return &_node->val;
		}
		Self& operator++()//重载++运算符
		{
			_node = _node->next;
			return *this;
		}
		Self& operator++(int)//后置++运算符
		{
			Self* temp(this);

			_node = _node->next;
			return *temp;
		}
		Self& operator--()//重载--运算符
		{
			_node = _node->prev;
			return *this;
		}
		Self& operator--(int)//后置--运算符
		{
			Self* temp(this);

			_node = _node->prev;
			return *temp;
		}
		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}
		Node* _node;//原生指针
	};
	//使用原生指针作为迭代器不符合需求，迭代器的解引用和++都不符合list迭代器的要求
	//所以这里将原生指针进行封装，然后使用运算符重载达到我们想要的效果
	//所以list的迭代器是一个自定义类型，这个自定义类型里存着原生指针
	//template <class T,class Ref>
	//struct _list_iterator
	//{
	//	typedef listNode<T> Node;
	//	typedef _list_iterator<T, Ref> Self;
	//	_list_iterator(Node* node)
	//		:_node(node)
	//	{}
	//	Ref& operator*()//重载*运算符因为原生指针中的解引用不符合list迭代要求
	//	{
	//		return _node->val;
	//	}
	//	T* operator->()
	//	{
	//		return &_node->val;
	//	}
	//	Self& operator++()//重载++运算符
	//	{
	//		_node = _node->next;
	//		return *this;
	//	}
	//	Self& operator++(int)//后置++运算符
	//	{
	//		Node* temp(this);

	//		_node = _node->next;
	//		return *temp;
	//	}
	//	bool operator!=(const Self& it)
	//	{
	//		return _node != it._node;
	//	}
	//	Node* _node;//原生指针
	//};

	//template <class T>
	//struct _list_iterator
	//{
	//	typedef listNode<T> Node;

	//	_list_iterator( Node* node)
	//		:_node(node)
	//	{}
	//   T& operator*()//重载*运算符因为原生指针中的解引用不符合list迭代要求
	//	{
	//		return _node->val;
	//	}
	//	_list_iterator<T>& operator++()//重载++运算符
	//	{
	//		_node = _node->next;
	//		return *this;
	//	}

	//	bool operator!=(const _list_iterator<T>& it)
	//	{
	//		return _node != it._node;
	//	}
	//	Node* _node;//原生指针
	//};



	//容器适配器模式 --->反向迭代器--给我正向迭代器我给你适配出反向迭代器，针对任何容器都可以，只要给我正向迭代器就可以适配出反向迭起


	template <class T>
	class list//带头双向循环列表
	{
	public:
		typedef listNode<T> Node;
		//typedef _list_iterator<T> iterator;//将自定义的迭代器名字统一命名为iterator
		//typedef _list_iterator<T,T&> iterator;//普通迭代器
		typedef _list_iterator<T, T&,T*> iterator;//普通迭代器
		//typedef _list_iterator<T, const T&> const_iterator;//const迭代器
		typedef _list_iterator<T, const T&,const T*> const_iterator;//const迭代器
		//const迭代器如何设计？
		//我们要求的const迭代器是：1.迭代器指向的内容不能被修改2.迭代器本身可以修改
		//1.const T* iterator     2.T* const iterator
		//typedef const _list_iterator<T> const_iterator;这种情况是第二种情况const修饰的是这个封装的迭代器，说明是这个迭代器不能被修改，而不是它指向的内容不能修改

		//正确的做法是，解引用时访问到数据，返回时返回const T&类型的数据，这样返回回来的数据就无法再被修改
		//有的人会选择拷贝一份封装的迭代器，然后其他都相同，就解引用运算符重载函数返回类型不同，普通迭代器，返回值是T&,const迭代器返回类型是constT&.
		//但这样做实在太冗余了，大佬是再添加一个模板参数来控制这里的迭代器返回类型的。

		typedef ReserveIterator<iterator, T&, T*> reserve_iterator;

		reserve_iterator rbegin()
		{
			return reserve_iterator(end());
		}
		reserve_iterator rend()
		{
			return reserve_iterator(begin());
		}
		iterator begin()
		{
			return _head->next;
			//return _list_iterator(_head->next)
			//单参数的构造支持隐式类型转化
		}
		iterator end()
		{
			return _head;
		}
		const_iterator begin()const
		{
			return _head->next;
			//return _list_iterator(_head->next)
			//单参数的构造支持隐式类型转化
		}
		const_iterator end()const
		{
			return _head;
		}
		list()
		{
			_head = new Node;
			_head->prev = _head;
			_head->next = _head;
			sz = 0;
		}
		list(const list<T>& lt1)
		{
			_head = new Node;
			_head->prev = _head;
			_head->next = _head;
			sz = 0;

			for (auto e : lt1)
			{
				push_back(e);
			}
		}
		void swap( list<T>& lt1)
		{
			std::swap(_head, lt1._head);
			std::swap(sz, lt1.sz);
		}
		list<T>& operator=( list<T>&lt1)
		{
			swap(lt1);
			return *this;
		}
		void push_front(const T& x)
		{
			insert(begin(),x);
		}
		void pop_front()
		{
			erase(begin());
		}
		void push_back(const T& x)
		{
			////尾插首先需要找到尾
			//Node* tail = _head->prev;
			////找到尾部后将新结点连接
			//Node* newnode = new Node(x);
			//tail->next = newnode;
			//newnode->prev = tail;

			//_head->prev = newnode;
			//newnode->next = _head;
			insert(end(), x);
		}
		void pop_back()
		{
			erase(--end());
		}
		iterator insert(iterator pos,const T& x)
		{
             //最好还是转化成结点的指针，这里访问迭代器不方便,这里就体现了为什么要用struct来定义迭代器让其成员共有
			Node* cur = pos._node;
			Node* prev = cur->prev;

			Node* newnode = new Node(x);

			prev->next = newnode;
			newnode->prev = prev;
			
			newnode->next = cur;
			cur->prev = newnode;
			sz++;
			return newnode;//返回新插入结点的位置
		
		}
		iterator erase(iterator pos)
		{
			assert(pos != end());//不能删除哨兵位
			Node* cur = pos._node;
			Node* prev = cur->prev;
			Node* next = cur->next;

			prev->next = next;
			next->prev = prev;

			delete cur;
			sz--;
			return next;
		}
		size_t size()
		{
			return sz;
		}
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		void clear()//清空数据，但不清哨兵位
		{
			iterator it = begin();
			while (it != end())
			{
				it=erase(it);
			
			}
			sz = 0;
		}
	private:
		Node* _head;//封装的是一个指向结点的指针
		size_t sz;
	};
	void test2(const list<int> lt)
	{

		list<int>::const_iterator cit = lt.begin();
		while (cit != lt.end())
		{
			//(*it) += 1;//解引用返回的是const T&这个表示为常量，不能被修改
			cout << *cit << " ";
			++cit;
			//因为it是自定义类型，自定义类型++就会去调用它的运算符重载
		}
		cout << endl;
	}
	struct A
	{
		A(int a = 1, int b = 2)
			:_a(a)
			, _b(b)
		{}
		int _a;
		int _b;//场景：假设成员变量是共有的可以访问
	};
	void test1()
	{
		list<int>  lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//(*it) += 1;//解引用返回的是const T&这个表示为常量，不能被修改
			cout << *it << " ";
			++it;
			//因为it是自定义类型，自定义类型++就会去调用它的运算符重载
		}
		cout << endl;
		//test2(lt);
	}
	void test3()
	{
		list<A>  lt;
		lt.push_back(A(1, 1));
		lt.push_back(A(2, 2));
		lt.push_back(A(3, 3));
		lt.push_back(A(4, 4));
		list<A>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//(*it) += 1;//解引用返回的是const T&这个表示为常量，不能被修改
			//cout << (*it)._a << (*it)._b<<" ";
			//可以这样访问的化，那么应该也可以使用箭头来访问成员it模拟的是指针，只不过是自定义类型的指针
			cout << it->_a << it->_b << " ";
		//不过这里很怪这个->运算符重载返回值是T* 也就是指向这个类型的指针 it->_a   it.operator->() 返回的是T* T*想访问到_a还需要再加上一个->才可以
			//即it->->_a 但编译器自动忽略一个箭头，为了可读性。
			++it;
			//因为it是自定义类型，自定义类型++就会去调用它的运算符重载
		}
		cout << endl;
		lt.clear();
	
		cout << lt.size() << endl;
	}
	void test4()
	{
		
			list<int>  lt;
			lt.push_back(1);
			lt.push_back(2);
			lt.push_back(3);
			lt.push_back(4);
			list<int>::iterator it = lt.begin();
			while (it != lt.end())
			{
				//(*it) += 1;//解引用返回的是const T&这个表示为常量，不能被修改
				cout << *it << " ";
				++it;
				//因为it是自定义类型，自定义类型++就会去调用它的运算符重载
			}
			cout << endl;
			lt.clear();
			lt.push_back(13);
			lt.push_back(22);
			lt.push_back(34);
			lt.push_back(45);
		    it = lt.begin();
			while (it != lt.end())
			{
				//(*it) += 1;//解引用返回的是const T&这个表示为常量，不能被修改
				cout << *it << " ";
				++it;
				//因为it是自定义类型，自定义类型++就会去调用它的运算符重载
			}
		
	}
	void test5()
	{
		list<int>  lt1;
		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		lt1.push_back(4);
		list<int>  lt2;
		lt2.push_back(100);
		lt2.push_back(200);
		lt2.push_back(300);
		lt2.push_back(400);
		//list<int> lt2(lt);//浅拷贝---》会出现什么问题？
		lt1 = lt2;
		list<int>::iterator it = lt1.begin();
		while (it != lt1.end())
		{
			//(*it) += 1;//解引用返回的是const T&这个表示为常量，不能被修改
			cout << *it << " ";
			++it;
			//因为it是自定义类型，自定义类型++就会去调用它的运算符重载
		}
		cout << endl;
	}
	void test7()
	{
			list<int>  lt;
			lt.push_back(1);
			lt.push_back(2);
			lt.push_back(3);
			lt.push_back(4);
			list<int>::reserve_iterator rit = lt.rbegin();
			while (rit != lt.rend())
			{
				//(*it) += 1;//解引用返回的是const T&这个表示为常量，不能被修改
				cout << *rit << " ";
				++rit;
				//因为it是自定义类型，自定义类型++就会去调用它的运算符重载
			}
			cout << endl;
			
	}
};