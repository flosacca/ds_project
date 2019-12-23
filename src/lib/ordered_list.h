#ifndef ORDERED_LIST_H
#define ORDERED_LIST_H

#include "list.h"

template <typename T>

class OrderedList: private List<T> {
private:
	using typename List<T>::Node;
	using List<T>::h;
	using List<T>::insert_after;
	using List<T>::erase_after;

public:
	using typename List<T>::It;
	using typename List<T>::ConstIt;
	using List<T>::empty;
	using List<T>::begin;
	using List<T>::end;
	using List<T>::top;
	using List<T>::pop;
	using List<T>::clear;
	using List<T>::size;
	using List<T>::find;
	using List<T>::each;
	using List<T>::each_with_index;

	OrderedList& push(const T& v) {
		if (!h || v <= h->v)
			List<T>::push(v);
		else {
			Node* i = h;
			while (i->r && i->r->v < v)
				i = i->r;
			insert_after(i, v);
		}
		return *this;
	}

	OrderedList& operator<<(const T& v) {
		return push(v);
	}

	OrderedList& erase(const T& v) {
		while (h && h->v == v)
			pop();
		if (Node* i = h)
			while (i) {
				while (i->r && i->r->v == v)
					erase_after(i);
				i = i->r;
			}
		return *this;
	}

	void edit(const T& v1, const T& v2) {
		erase(v1);
		push(v2);
	}
};

#endif
