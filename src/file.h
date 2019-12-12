#ifndef FILE_H
#define FILE_H

#include "ds.h"

u64 fileSize(const Str& name);

List<Str> findFiles(const Str& pattern);

Str read(const Str& name);

void write(const Str& name, const Str& s);

#endif
