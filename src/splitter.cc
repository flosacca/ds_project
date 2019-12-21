#include "splitter.h"
#include <functional>

List<Str> Splitter::split(const Str& s) const {
	List<Str> words;

	auto i = s.begin();
	auto j = i;

	while (*i) {
		auto k = next(j);

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

		auto u = next(k);
		auto v = !*u ? u : next(u);
		auto w = !*v ? v : next(v);
		auto p = !*w ? w : next(w);

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
			if (mid.has_hash(hash(j, k))) {
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
					if (i == j || next(i) == j)
						words << Str(i, r);
					else {
						words << Str(i, j);
						words << Str(j, r);
					}
					i = j = r;
					return true;
				}
			}
			return false;
		};

		if (!proc[0]() && !proc[1]() && !proc[2]())
			j = k;
	}

	return words.reverse();
}
