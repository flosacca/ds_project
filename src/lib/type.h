#ifndef TYPE_H
#define TYPE_H

#include <stdint.h>
#include <ctype.h>

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

#endif
