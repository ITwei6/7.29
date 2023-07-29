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
		Ref operator*()//����*�������Ϊԭ��ָ���еĽ����ò�����list����Ҫ��
		{
			return _node->val;
		}
		Ptr operator->()  //const����ʹ�� ���ص�Ӧ����const T *
		{
			return &_node->val;
		}
		Self& operator++()//����++�����
		{
			_node = _node->next;
			return *this;
		}
		Self& operator++(int)//����++�����
		{
			Self* temp(this);

			_node = _node->next;
			return *temp;
		}
		Self& operator--()//����--�����
		{
			_node = _node->prev;
			return *this;
		}
		Self& operator--(int)//����--�����
		{
			Self* temp(this);

			_node = _node->prev;
			return *temp;
		}
		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}
		Node* _node;//ԭ��ָ��
	};
	//ʹ��ԭ��ָ����Ϊ���������������󣬵������Ľ����ú�++��������list��������Ҫ��
	//�������ｫԭ��ָ����з�װ��Ȼ��ʹ����������شﵽ������Ҫ��Ч��
	//����list�ĵ�������һ���Զ������ͣ�����Զ������������ԭ��ָ��
	//template <class T,class Ref>
	//struct _list_iterator
	//{
	//	typedef listNode<T> Node;
	//	typedef _list_iterator<T, Ref> Self;
	//	_list_iterator(Node* node)
	//		:_node(node)
	//	{}
	//	Ref& operator*()//����*�������Ϊԭ��ָ���еĽ����ò�����list����Ҫ��
	//	{
	//		return _node->val;
	//	}
	//	T* operator->()
	//	{
	//		return &_node->val;
	//	}
	//	Self& operator++()//����++�����
	//	{
	//		_node = _node->next;
	//		return *this;
	//	}
	//	Self& operator++(int)//����++�����
	//	{
	//		Node* temp(this);

	//		_node = _node->next;
	//		return *temp;
	//	}
	//	bool operator!=(const Self& it)
	//	{
	//		return _node != it._node;
	//	}
	//	Node* _node;//ԭ��ָ��
	//};

	//template <class T>
	//struct _list_iterator
	//{
	//	typedef listNode<T> Node;

	//	_list_iterator( Node* node)
	//		:_node(node)
	//	{}
	//   T& operator*()//����*�������Ϊԭ��ָ���еĽ����ò�����list����Ҫ��
	//	{
	//		return _node->val;
	//	}
	//	_list_iterator<T>& operator++()//����++�����
	//	{
	//		_node = _node->next;
	//		return *this;
	//	}

	//	bool operator!=(const _list_iterator<T>& it)
	//	{
	//		return _node != it._node;
	//	}
	//	Node* _node;//ԭ��ָ��
	//};



	//����������ģʽ --->���������--��������������Ҹ�����������������������κ����������ԣ�ֻҪ��������������Ϳ���������������


	template <class T>
	class list//��ͷ˫��ѭ���б�
	{
	public:
		typedef listNode<T> Node;
		//typedef _list_iterator<T> iterator;//���Զ���ĵ���������ͳһ����Ϊiterator
		//typedef _list_iterator<T,T&> iterator;//��ͨ������
		typedef _list_iterator<T, T&,T*> iterator;//��ͨ������
		//typedef _list_iterator<T, const T&> const_iterator;//const������
		typedef _list_iterator<T, const T&,const T*> const_iterator;//const������
		//const�����������ƣ�
		//����Ҫ���const�������ǣ�1.������ָ������ݲ��ܱ��޸�2.��������������޸�
		//1.const T* iterator     2.T* const iterator
		//typedef const _list_iterator<T> const_iterator;��������ǵڶ������const���ε��������װ�ĵ�������˵����������������ܱ��޸ģ���������ָ������ݲ����޸�

		//��ȷ�������ǣ�������ʱ���ʵ����ݣ�����ʱ����const T&���͵����ݣ��������ػ��������ݾ��޷��ٱ��޸�
		//�е��˻�ѡ�񿽱�һ�ݷ�װ�ĵ�������Ȼ����������ͬ���ͽ�������������غ����������Ͳ�ͬ����ͨ������������ֵ��T&,const����������������constT&.
		//��������ʵ��̫�����ˣ������������һ��ģ���������������ĵ������������͵ġ�

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
			//�������Ĺ���֧����ʽ����ת��
		}
		iterator end()
		{
			return _head;
		}
		const_iterator begin()const
		{
			return _head->next;
			//return _list_iterator(_head->next)
			//�������Ĺ���֧����ʽ����ת��
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
			////β��������Ҫ�ҵ�β
			//Node* tail = _head->prev;
			////�ҵ�β�����½������
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
             //��û���ת���ɽ���ָ�룬������ʵ�����������,�����������ΪʲôҪ��struct����������������Ա����
			Node* cur = pos._node;
			Node* prev = cur->prev;

			Node* newnode = new Node(x);

			prev->next = newnode;
			newnode->prev = prev;
			
			newnode->next = cur;
			cur->prev = newnode;
			sz++;
			return newnode;//�����²������λ��
		
		}
		iterator erase(iterator pos)
		{
			assert(pos != end());//����ɾ���ڱ�λ
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
		void clear()//������ݣ��������ڱ�λ
		{
			iterator it = begin();
			while (it != end())
			{
				it=erase(it);
			
			}
			sz = 0;
		}
	private:
		Node* _head;//��װ����һ��ָ�����ָ��
		size_t sz;
	};
	void test2(const list<int> lt)
	{

		list<int>::const_iterator cit = lt.begin();
		while (cit != lt.end())
		{
			//(*it) += 1;//�����÷��ص���const T&�����ʾΪ���������ܱ��޸�
			cout << *cit << " ";
			++cit;
			//��Ϊit���Զ������ͣ��Զ�������++�ͻ�ȥ�����������������
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
		int _b;//�����������Ա�����ǹ��еĿ��Է���
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
			//(*it) += 1;//�����÷��ص���const T&�����ʾΪ���������ܱ��޸�
			cout << *it << " ";
			++it;
			//��Ϊit���Զ������ͣ��Զ�������++�ͻ�ȥ�����������������
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
			//(*it) += 1;//�����÷��ص���const T&�����ʾΪ���������ܱ��޸�
			//cout << (*it)._a << (*it)._b<<" ";
			//�����������ʵĻ�����ôӦ��Ҳ����ʹ�ü�ͷ�����ʳ�Աitģ�����ָ�룬ֻ�������Զ������͵�ָ��
			cout << it->_a << it->_b << " ";
		//��������ܹ����->��������ط���ֵ��T* Ҳ����ָ��������͵�ָ�� it->_a   it.operator->() ���ص���T* T*����ʵ�_a����Ҫ�ټ���һ��->�ſ���
			//��it->->_a ���������Զ�����һ����ͷ��Ϊ�˿ɶ��ԡ�
			++it;
			//��Ϊit���Զ������ͣ��Զ�������++�ͻ�ȥ�����������������
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
				//(*it) += 1;//�����÷��ص���const T&�����ʾΪ���������ܱ��޸�
				cout << *it << " ";
				++it;
				//��Ϊit���Զ������ͣ��Զ�������++�ͻ�ȥ�����������������
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
				//(*it) += 1;//�����÷��ص���const T&�����ʾΪ���������ܱ��޸�
				cout << *it << " ";
				++it;
				//��Ϊit���Զ������ͣ��Զ�������++�ͻ�ȥ�����������������
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
		//list<int> lt2(lt);//ǳ����---�������ʲô���⣿
		lt1 = lt2;
		list<int>::iterator it = lt1.begin();
		while (it != lt1.end())
		{
			//(*it) += 1;//�����÷��ص���const T&�����ʾΪ���������ܱ��޸�
			cout << *it << " ";
			++it;
			//��Ϊit���Զ������ͣ��Զ�������++�ͻ�ȥ�����������������
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
				//(*it) += 1;//�����÷��ص���const T&�����ʾΪ���������ܱ��޸�
				cout << *rit << " ";
				++rit;
				//��Ϊit���Զ������ͣ��Զ�������++�ͻ�ȥ�����������������
			}
			cout << endl;
			
	}
};