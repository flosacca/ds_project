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
		punc(f.begin()[1]),
		mid(f.begin()[2]),
		pre(f.begin()[3])
	{
		main.merge(mid);
	}

	// next UTF-8 char
	template <typename CharIt>
	static CharIt next(CharIt i) {
		return i + (~*i>>7&1 ? 1 : __builtin_clz(~*i<<24));
	}

	// s: UTF-8
	List<Str> split(const Str& s) const;

private:
	DicFile main, punc, mid, pre;
};

#endif
