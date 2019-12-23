#ifndef SET_H
#define SET_H

#include <initializer_list>
#include "utils.h"
#include "list.h"

template <typename T>

class Set {
private:
	int l, n;
	List<u64>* a;

public:
	explicit Set(int l = 4): l(l), n(0),
		a(new List<u64>[l])
	{}

	Set(const std::initializer_list<T>& r):
		Set(r.size())
	{
		for (const T& v: r)
			add(v);
	}

	Set(const Set& r):
		Set(r.l)
	{
		n = r.n;
		for (int i = 0; i < l; ++i)
			a[i] = r.a[i];
	}

	Set& operator=(const Set& r) {
		l = r.l;
		n = r.n;
		delete[] a;
		a = new List<u64>[l];
		for (int i = 0; i < l; ++i)
			a[i] = r.a[i];
		return *this;
	}

	~Set() { delete[] a; }

	int buckets_count() const {
		return l;
	}

	int size() const {
		return n;
	}

	bool has_hash(u64 k) const {
		return a[k%l].find(k);
	}

	bool has(const T& v) const {
		return has_hash(hash(v));
	}

	Set& add_hash(u64 k) {
		++n;
		if (l < n) {
			int m = n*2;
			auto b = new List<u64>[m];
			each_hash([=] (u64 k) {
				b[k%m] << k;
			});
			l = m;
			delete[] a;
			a = b;
		}
		a[k%l] << k;
		return *this;
	}

	Set& add(const T& v) {
		return add_hash(hash(v));
	}

	Set& operator<<(const T& v) {
		return add(v);
	}

	template <typename Function>
	const Set& each_hash(const Function& f) const {
		for (int i = 0; i < l; ++i)
			a[i].each(f);
		return *this;
	}

	Set& merge(const Set& r) {
		r.each_hash([&] (u64 k) {
			add_hash(k);
		});
		return *this;
	}
};

template <typename T>
Set<T> operator&(const Set<T>& a, const Set<T>& b) {
	int n = a.buckets_count();
	int m = b.buckets_count();
	if (n < m)
		return b & a;
	Set<T> s;
	b.each_hash([&] (u64 k) {
		if (a.has_hash(k))
			s.add_hash(k);
	});
	return s;
}

template <typename T>
Set<T> operator|(const Set<T>& a, const Set<T>& b) {
	int n = a.buckets_count();
	int m = b.buckets_count();
	if (n < m)
		return b | a;
	Set<T> s(a);
	b.each_hash([&] (u64 k) {
		if (!a.has_hash(k))
			s.add_hash(k);
	});
	return s;
}

#endif
