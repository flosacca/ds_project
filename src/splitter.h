#ifndef SPLITTER_H
#define SPLITTER_H

#include "ds.h"
#include "file.h"

class DicFile: public Set<Str> {
public:
	template <typename Container>
	DicFile(const Container& c):
		Set<Str>(c.size())
	{
		for (auto&& s: c)
			add(s);
	}

	DicFile(const Str& fileName):
		DicFile(read(fileName).rsplit())
	{}
};

class Splitter {
public:
	Splitter(const std::initializer_list<Str> f):
		main(f.begin()[0]),
		stop(f.begin()[1]),
		pre(f.begin()[2]),
		punc(f.begin()[3])
	{
		main.merge(stop);
		stop.merge(pre);
	}

	List<Str> split(const Str& s) const; // s: UTF-8

private:
	DicFile main, stop, pre, punc;
};

#endif
