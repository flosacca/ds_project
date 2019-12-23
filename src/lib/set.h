#ifndef SET_H
#define SET_H

#include <initializer_list>
#include "utils.h"
#include "list.h"

template <typename T>

class Set {
public:
	Set(int n = 0): n(n) {
		a = new List<u64>[n];
	}

	Set(const std::initializer_list<T>& r):
		Set(r.size())
	{
		for (const T& v: r)
			add(v);
	}

	Set(const Set& r):
		Set(r.n)
	{
		for (int i = 0; i < n; ++i)
			a[i] = r.a[i];
	}

	Set& operator=(const Set& r) {
		n = r.n;
		delete[] a;
		a = new List<u64>[n];
		for (int i = 0; i < n; ++i)
			a[i] = r.a[i];
		return *this;
	}

	~Set() { delete[] a; }

	int buckets_count() const {
		return n;
	}

	int size() const {
		int s = 0;
		for (int i = 0; i < n; ++i)
			s += a[i].size();
		return s;
	}

	bool has_hash(u64 k) const {
		return a[k%n].find(k);
	}

	bool has(const T& v) const {
		return has_hash(hash(v));
	}

	Set& add_hash(u64 k) {
		a[k%n] << k;
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
		for (int i = 0; i < n; ++i)
			a[i].each(f);
		return *this;
	}

	Set& merge(const Set& r) {
		r.each_hash([&] (u64 k) {
			add_hash(k);
		});
		return *this;
	}

private:
	List<u64>* a;
	int n;
};

template <typename T>
Set<T> operator&(const Set<T>& a, const Set<T>& b) {
	int n = a.buckets_count();
	int m = b.buckets_count();
	if (n < m)
		return b & a;
	Set<T> s(m);
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
