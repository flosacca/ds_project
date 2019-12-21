#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

using u64 = uint64_t;

inline bool isSpace(char c) {
	return isspace(c);
}

inline bool notSpace(char c) {
	return !isspace(c);
}

inline bool isAlpha(char c) {
	return isalpha(c);
}

inline bool notAlpha(char c) {
	return !isalpha(c);
}

inline bool isAlnum(char c) {
	return isalnum(c);
}

inline bool notAlnum(char c) {
	return !isalnum(c);
}

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
