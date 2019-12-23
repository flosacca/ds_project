#ifndef PAIR_H
#define PAIR_H

#include "str.h"

template <typename T1 = Str, typename T2 = T1>

struct Pair {
	T1 first;
	T2 second;

	int cmp(const Pair& p) const {
		if (first != p.first)
			return first < p.first ? -1 : 1;
		if (second != p.second)
			return second < p.second ? -1 : 1;
		return 0;
	}
};

template <typename T>

struct Pair<T, T> {
	T first;
	T second;

	int cmp(const Pair& p) const {
		if (first != p.first)
			return first < p.first ? -1 : 1;
		if (second != p.second)
			return second < p.second ? -1 : 1;
		return 0;
	}

	T& operator[](int i) {
		return i == 0 ? first : second;
	}

	const T& operator[](int i) const {
		return i == 0 ? first : second;
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
