#ifndef SET_H
#define SET_H

#include <initializer_list>
#include "hash.h"
#include "list.h"

class BasicSet {
public:
	BasicSet(int n): n(n) {
		a = new List<u64>[n];
	}

	BasicSet(const BasicSet& r):
		BasicSet(r.n)
	{
		for (int i = 0; i < n; ++i)
			a[i] = r.a[i];
	}

	~BasicSet() {
		delete[] a;
	}

	bool has(u64 v) const {
		return a[v%n].find(v);
	}

	void add(u64 v) {
		a[v%n] << v;
	}

	void merge(const BasicSet& r) {
		for (int i = 0; i < r.n; ++i)
			for (u64 v: r.a[i]) {
				add(v);
			}
	}

private:
	List<u64>* a;
	const int n;
};

template <typename T>

class Set: public BasicSet {
public:
	using BasicSet::add;
	using BasicSet::has;

	Set(int n): BasicSet(n) {}

	template <typename S>
	Set(const std::initializer_list<S>& r):
		BasicSet(r.size())
	{
		for (const T& v: r)
			BasicSet::add(hash(v));
	}

	void add(const T& v) {
		BasicSet::add(hash(v));
	}

	bool has(const T& v) const {
		return BasicSet::has(hash(v));
	}
};

#endif
