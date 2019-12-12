#ifndef HASH_H
#define HASH_H

#include <string.h>
#include <time.h>
#include "type.h"

inline u64 hash(int v) {
	return v;
}

inline u64 hash(char c) {
	return c;
}

inline u64 hash(const char* s, int l = -1) {
	static u64 b = 1 + 2*time(0);
	if (l < 0)
		l = strlen(s);
	u64 a = 0;
	while (l--)
		a = b*a + *s++;
	return a;
}

inline u64 hash(const char* l, const char* r) {
	return hash(l, r-l);
}

#endif
