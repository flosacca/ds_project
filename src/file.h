#ifndef FILE_H
#define FILE_H

#include "ds.h"
#include <stdio.h>

int fileSize(const Str& path);

List<Str> findFiles(const Str& path);

inline Str read(const Str& path) {
	if (FILE* f = fopen(path.data(), "r")) {
		Str s(f, fileSize(path));
		fclose(f);
		return s;
	}
	return "";
}

inline void write(const Str& path, const Str& s) {
	FILE* f = fopen(path.data(), "w");
	fwrite(s.data(), 1, s.size(), f);
	fclose(f);
}

template <typename Function>
inline void open(const Str& path, const Str& opt, const Function& f) {
	if (FILE* p = fopen(path.data(), opt.data())) {
		f(p);
		fclose(p);
	}
}

#endif
