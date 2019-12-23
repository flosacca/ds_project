#ifndef PAIR_H
#define PAIR_H

#include "str.h"

template <typename T1 = Str, typename T2 = T1>

struct Pair {
	T1 first;
	T2 second;

	int cmp(const Pair& p) {
		if (first != p.first)
			return first < p.first ? -1 : 1;
		if (second != p.second)
			return second < p.second ? -1 : 1;
		return 0;
	}
};

template <typename T>

struct Pair<T, T> {
	T a[2];

	operator T*() { return a; }
	operator const T*() const { return a; }

	int cmp(const Pair& p) const {
		if (a[0] != p.a[0])
			return a[0] < p.a[0] ? -1 : 1;
		if (a[1] != p.a[1])
			return a[1] < p.a[1] ? -1 : 1;
		return 0;
	}
};

template <typename T1, typename T2>
inline bool operator==(const Pair<T1, T2>& a, const Pair<T1, T2>& b) {
	return a.cmp(b) == 0;
}

template <typename T1, typename T2>
inline bool operator!=(const Pair<T1, T2>& a, const Pair<T1, T2>& b) {
	return a.cmp(b) != 0;
}

template <typename T1, typename T2>
inline bool operator<(const Pair<T1, T2>& a, const Pair<T1, T2>& b) {
	return a.cmp(b) < 0;
}

template <typename T1, typename T2>
inline bool operator>(const Pair<T1, T2>& a, const Pair<T1, T2>& b) {
	return a.cmp(b) > 0;
}

template <typename T1, typename T2>
inline bool operator<=(const Pair<T1, T2>& a, const Pair<T1, T2>& b) {
	return a.cmp(b) <= 0;
}

template <typename T1, typename T2>
inline bool operator>=(const Pair<T1, T2>& a, const Pair<T1, T2>& b) {
	return a.cmp(b) >= 0;
}

template <typename T1, typename T2>
inline Pair<T1, T2> makePair(const T1& first, const T2& second) {
	return {first, second};
}

#endif
