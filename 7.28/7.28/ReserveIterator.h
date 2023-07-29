#pragma once

template <class Iterator,class Ref,class Ptr>

struct ReserveIterator
{
	typedef ReserveIterator<Iterator, Ref, Ptr> Self;
	ReserveIterator(Iterator it)
		:_it(it)
	{}//用正向迭代器初始化
	Ref operator*()//解引用，解的是前一个位置，保持对称
	{
		Iterator tmp = _it;
		return *(--tmp);
		//正向迭代器的模板类型是  class<T ,T& ,T*>
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
	Iterator _it;//底层封装一个正向迭代器

};