#ifndef SPLITTER_H
#define SPLITTER_H

#include "ds.h"

class Splitter {
public:
	Splitter(const Array<Str, 4>&);

	List<Str> split(const Str&) const;

private:
	Set<Str> main, stop, pre, punc;
};

#endif
