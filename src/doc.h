#ifndef DOC_H
#define DOC_H

#include "ds.h"
#include "splitter.h"

class Doc {
public:
	Doc();

	// Return [(count, times, id)]
	OrderedList<Array<int, 3>> search(const Str& words) const;

	// Return [id]
	Vec<int> recommend(const Str& title, int count) const;

	Str title(int id) const {
		if (auto v = titles.find(id))
			return *v;
		return "";
	}

private:
	Splitter sp;
	Dic<Str, OrderedList<Pair<int>>> occurs;
	Dic<int, Str> titles;
	Dic<Str, Pair<int, Set<Str>>> tags;
};

#endif
