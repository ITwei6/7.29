#pragma once

template <class Iterator,class Ref,class Ptr>

struct ReserveIterator
{
	typedef ReserveIterator<Iterator, Ref, Ptr> Self;
	ReserveIterator(Iterator it)
		:_it(it)
	{}//�������������ʼ��
	Ref operator*()//�����ã������ǰһ��λ�ã����ֶԳ�
	{
		Iterator tmp = _it;
		return *(--tmp);
		//�����������ģ��������  class<T ,T& ,T*>
	}
	Self& operator++()
	{
		--_it;
		return *this;
	}
	Self& operator--()
	{
		++_it;
		return *this;
	}
	bool operator!=(Self it)
	{
		return _it != it._it;
	}
	Iterator _it;//�ײ��װһ�����������

};