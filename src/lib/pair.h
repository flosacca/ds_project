#ifndef PAIR_H
#define PAIR_H

#include "str.h"

struct Pair {
	Str name, value;

	Str& operator[](int i) {
		return !i ? name : value;
	}

	const Str& operator[](int i) const {
		return !i ? name : value;
	}
};

inline bool operator==(const Pair& a, const Pair& b) {
	return a[0] == b[0] && a[1] == b[1];
}

inline bool operator!=(const Pair& a, const Pair& b) {
	return !(a==b);
}

#endif
