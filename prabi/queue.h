#pragma once
#ifndef _QUEUE_HEADER_
#define _QUEUE_HEADER_
#include <atomic>
template<typename T>
class atomic_queue
{
	class __item
	{
	public:
		T _v;
		__item* next = nullptr;
		__item(const T& r) :_v(r) {}
	};
	std::atomic<__item*> top = nullptr;
	std::atomic<__item*> end = nullptr;
private:
	void swap(atomic_queue& _rhs) 
	{
		__item* t;
		t = top.load();
		top.store(_rhs.top.load());
		_rhs.top.store(t);

		t = end.load();
		end.store(_rhs.end.load());
		_rhs.end.store(t);
	}
public:
	atomic_queue()
	{
		top.store(nullptr);
		end.store(nullptr);
	}
	~atomic_queue() 
	{
		auto _p = top.load();
		while (_p != nullptr) 
		{
			auto _rp = _p;
			_p =_p->next;
			delete _rp;
		}
	};
	atomic_queue& operator=(const atomic_queue&) = delete;
	atomic_queue& operator=(atomic_queue&& rhs) 
	{
		rhs.swap(*this);
		atomic_queue().swap(rhs);
		return *this;
	}
	inline void push_back(const __item& rhs)
	{
		__item* newItem = new __item(rhs._v);
		__item* tail = nullptr;
		do tail = end.load();
		while (!end.compare_exchange_weak(tail, newItem));
		if (tail == nullptr)
			top.store(newItem);
		else
			tail->next = newItem;
	}
	inline bool empty()
	{
		return top.load() == nullptr;
	}
	inline T pop_front()
	{
		__item* head = top.load();
		end.compare_exchange_weak(head, nullptr);
		__item* target = nullptr;
		do
		{
			head = top.load();
			target = head->next;
		} while (!top.compare_exchange_weak(head, target));
		T res = head->_v;
		delete head;
		return res;
	}
};

#endif // !_QUEUE_HEADER_

