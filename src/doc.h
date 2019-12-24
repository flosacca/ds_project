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

	Vec<int> recommend(int id, int count) const {
		return recommend(title(id), count);
	}

	Str title(int id) const {
		if (auto info = infos.find(id))
			return *info->find("title");
		return "";
	}

	const Dic<Str, Str>& info(int id) const {
		return *infos.find(id);
	}

	int id(const Str& title) const {
		if (auto pair = tags.find(title))
			return pair->first;
		return -1;
	}

private:
	Splitter sp;
	Dic<Str, OrderedList<Pair<int>>> occurs;
	Dic<int, Dic<Str, Str>> infos;
	Dic<Str, Pair<int, Set<Str>>> tags;
};

#endif
