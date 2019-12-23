// This class treats its elements as raw data.

#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#include <string.h>
#include "algo.h"

template <typename T>

class Vec {
public:
	explicit Vec(int n = 0, const T& v = T()):
		n(abs(n)), cap(max(abs(n), 4))
	{
		a = static_cast<T*>(malloc(sizeof(T) * cap));
		for (int i = 0; i < n; ++i)
			a[i] = v;
	}

	Vec(const Vec& r):
		n(r.n), cap(r.n)
	{
		a = static_cast<T*>(malloc(sizeof(T) * cap));
		memcpy(a, r.a, sizeof(T)*n);
	}

	Vec& operator=(const Vec& r) {
		n = r.n;
		cap = n;
		free(a);
		a = static_cast<T*>(malloc(sizeof(T) * cap));
		memcpy(a, r.a, sizeof(T)*n);
		return *this;
	}

	~Vec() { free(a); }

	T& operator[](int i) {
		return a[i];
	}

	const T& operator[](int i) const {
		return a[i];
	}

	T& at(int i) {
		return i < 0 ? a[n+i] : a[i];
	}

	const T& at(int i) const {
		return i < 0 ? a[n+i] : a[i];
	}

	bool empty() const { return !n; }
	int size() const { return n; }
	int capacity() const { return cap; }

	T* begin() { return a; }
	T* end() { return a+n; }

	const T* begin() const { return a; }
	const T* end() const { return a+n; }

	T& top() { return a[n-1]; }
	const T& top() const { return a[n-1]; }

	Vec& push(const T& v) {
		if (n == cap)
			extend();
		a[n++] = v;
		return *this;
	}

	template <typename InputIt>
	Vec& push(InputIt l, InputIt r) {
		while (l != r)
			push(*l++);
		return *this;
	}

	Vec& operator<<(const T& v) {
		return push(v);
	}

	T& pop() { return a[--n]; }

	T* find(T& v) {
		for (auto& e: *this)
			if (v == e)
				return &e;
		return nullptr;
	}

	template <typename Predicate>
	T* find(const Predicate& p) {
		for (auto& e: *this)
			if (p(e))
				return &e;
		return nullptr;
	}

	const T* find(const T& v) const {
		for (auto& e: *this)
			if (v == e)
				return &e;
		return nullptr;
	}

	template <typename Predicate>
	const T* find(const Predicate& p) const {
		for (auto& e: *this)
			if (p(e))
				return &e;
		return nullptr;
	}

	template <typename Function>
	Vec& each(const Function& f) {
		for (auto& e: *this)
			f(e);
		return *this;
	}

	template <typename Function>
	const Vec& each(const Function& f) const {
		for (auto& e: *this)
			f(e);
		return *this;
	}

	template <typename Function>
	Vec& each_with_index(const Function& f) {
		int i = 0;
		for (auto& e: *this)
			f(e, i++);
		return *this;
	}

	template <typename Function>
	const Vec& each_with_index(const Function& f) const {
		int i = 0;
		for (auto& e: *this)
			f(e, i++);
		return *this;
	}

protected:
	void realloc(int l) {
		cap = l;
		T* b = static_cast<T*>(malloc(sizeof(T)*l));
		memcpy(b, a, sizeof(T)*n);
		free(a);
		a = b;
	}

	void extend() {
		realloc(cap*2);
	}

	T* a;
	int n, cap;
};

#endif
