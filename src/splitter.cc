#include "splitter.h"
#include "file.h"
#include <functional>

Set<Str> readSet(const Str& fileName) {
	return map<Set<Str>>(read(fileName).rsplit());
}

Splitter::Splitter(const Array<Str, 4>& f):
	main(readSet(f[0])),
	stop(readSet(f[1])),
	pre(readSet(f[2])),
	punc(readSet(f[3]))
{}

List<Str> Splitter::split(const Str& s) const {
	List<Str> words;

	auto i = s.begin();
	auto j = i;

	while (*i) {
		auto k = nextChar(j);

		if ((k-j == 1 && !isAlnum(*j)) || punc.has_hash(hash(j, k))) {
			if (i != j)
				words << Str(i, j);
			i = j = k;
			continue;
		}

		if (!*k) {
			words << Str(i, k);
			break;
		}

		auto u = nextChar(k);
		auto v = !*u ? u : nextChar(u);
		auto w = !*v ? v : nextChar(v);
		auto p = !*w ? w : nextChar(w);

		std::function<bool()> proc[3];
		
		proc[0] = [&] ()->bool {
			if (pre.has_hash(hash(j, k))) {
				for (auto r: {p, w, v}) {
					if (main.has_hash(hash(k, r))) {
						if (i != j)
							words << Str(i, j);
						words << Str(j, r);
						i = j = r;
						return true;
					}
				}
			}
			return false;
		};

		proc[1] = [&] ()->bool {
			if (stop.has_hash(hash(j, k))) {
				for (auto r: {p, w, v}) {
					if (main.has_hash(hash(k, r))) {
						if (i != j)
							words << Str(i, j);
						words << Str(j, k);
						words << Str(k, r);
						i = j = r;
						return true;
					}
				}
			}
			return false;
		};

		proc[2] = [&] ()->bool {
			for (auto r: {p, w, v, u, k}) {
				if (main.has_hash(hash(j, r))) {
					if (i != j)
						words << Str(i, j);
					words << Str(j, r);
					i = j = r;
					return true;
				}
			}
			return false;
		};

		if (!proc[0]() && !proc[1]() && !proc[2]())
			j = k;
	}

	return select<List<Str>>(words, [&] (auto& w) {
		return !stop.has(w);
	});
}
