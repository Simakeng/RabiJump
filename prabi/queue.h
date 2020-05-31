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
public:
	atomic_queue()
	{
		top.store(nullptr);
		end.store(nullptr);
	}
	~atomic_queue() = default;
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

