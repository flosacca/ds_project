#ifndef STR_H
#define STR_H

#include <stdio.h>
#include "vec.h"
#include "list.h"
#include "hash.h"

class Str: private Vec<char> {
public:
	using Vec<char>::operator[];
	using Vec<char>::at;
	using Vec<char>::empty;
	using Vec<char>::size;

private:
	template <typename CharType>

	class BasicIt {
	private:
		CharType* i;

	public:
		BasicIt(CharType* i = nullptr): i(i) {}

		operator CharType*() const {
			return i;
		}

		BasicIt& operator++() {
			++i;
			return *this;
		}

		BasicIt operator++(int) {
			BasicIt j = i;
			++i;
			return j;
		}

		BasicIt& operator--() {
			--i;
			return *this;
		}

		BasicIt operator--(int) {
			BasicIt j = i;
			--i;
			return j;
		}

		BasicIt& operator+=(int d) {
			i += d;
			return *this;
		}

		BasicIt& operator-=(int d) {
			i -= d;
			return *this;
		}

		BasicIt& move(char c) {
			while (*i && *i != c)
				++i;
			return *this;
		}

		template <typename Predicate>
		BasicIt& move(Predicate pred) {
			while (*i && !pred(*i))
				++i;
			return *this;
		}

		template <typename T>
		BasicIt find(T arg) const {
			BasicIt j = i;
			j.move(arg);
			return j;
		}

		bool match(const Str& s) const {
			for (int j = 0; s[j]; ++j)
				if (i[j] != s[j])
					return false;
			return true;
		}
	};

public:
	using It = BasicIt<char>;
	using ConstIt = BasicIt<const char>;

	Str(const char* s = "", int l = -1):
		Vec<char>(l < 0 ? -strlen(s)-1 : -l-1)
	{
		memcpy(a, s, --n);
		a[n] = 0;
	}

	Str(const char* l, const char* r):
		Str(l, r-l)
	{}

	Str(const Str& s):
		Str(s.a, s.n)
	{}

	Str(FILE* f, int l):
		Vec<char>(-l-1)
	{
		n = !f ? 0 : fread(a, 1, l, f);
		a[n] = 0;
	}

	Str& operator=(const Str& s) {
		n = s.n;
		cap = n+1;
		free(a);
		a = static_cast<char*>(malloc(cap));
		memcpy(a, s.a, n+1);
		return *this;
	}

	Str& operator=(const char* s) {
		n = strlen(s);
		cap = n+1;
		free(a);
		a = static_cast<char*>(malloc(cap));
		memcpy(a, s, n+1);
		return *this;
	}

	void read(FILE* f, int l) {
		cap = l+1;
		free(a);
		a = static_cast<char*>(malloc(cap));
		n = fread(a, 1, l, f);
		a[n] = 0;
	}

	char* data() {
		return a;
	}

	const char* data() const {
		return a;
	}

	It begin() {
		return a;
	}

	ConstIt begin() const {
		return a;
	}

	It end() {
		return a+n;
	}

	ConstIt end() const {
		return a+n;
	}

	Str& concat(char c) {
		if (n+1 == cap)
			extend();
		a[n++] = c;
		a[n] = 0;
		return *this;
	}

	Str& concat(const char* s, int l) {
		realloc(n+l+1);
		memcpy(a+n, s, l);
		n += l;
		a[n] = 0;
		return *this;
	}

	Str& concat(const char* s) {
		return concat(s, strlen(s));
	}

	Str& concat(const Str& s) {
		return concat(s.a, s.n);
	}

	Str& operator+=(char c) {
		return concat(c);
	}

	Str& operator+=(const char* s) {
		return concat(s);
	}

	Str& operator+=(const Str& s) {
		return concat(s);
	}

	Str& operator<<(char c) {
		return concat(c);
	}

	Str& operator<<(const char* s) {
		return concat(s);
	}

	Str& operator<<(const Str& s) {
		return concat(s);
	}

	char pop() {
		char c = a[--n];
		a[n] = 0;
		return c;
	}

	int cmp(const Str& s) const {
		for (int i = 0;; ++i) {
			if (a[i] < s[i])
				return -1;
			if (a[i] > s[i])
				return 1;
			if (!a[i])
				return 0;
		}
	}

	Str slice(int i, int l = -1) const {
		return Str(a+i, l < 0 ? n-i : min(n-i, l));
	}

	Str lstrip() const {
		return Str(begin().find(notSpace), end());
	}

	Str rstrip() const {
		int i = n-1;
		while (i > -1 && isSpace(a[i]))
			--i;
		return slice(0, i+1);
	}

	Str strip() const {
		return rstrip().lstrip();
	}

	int index(char c) const {
		for (int i = 0; i < n; ++i)
			if (c == a[i])
				return i;
		return -1;
	}

	int index(const Str& s) const {
		for (int i = 0; i < n; ++i)
			if (It(a+i).match(s))
				return i;
		return -1;
	}

	int rindex(char c) const {
		for (int i = n-1; i > -1; --i)
			if (c == a[i])
				return i;
		return -1;
	}

	Str sub(const Str& p, const Str& r) const {
		Str s;
		It i = a;
		while (*i) {
			if (i.match(p)) {
				s << r;
				i += p.size();
			} else {
				s << *i++;
			}
		}
		return s;
	}

	template <typename Function>
	List<Str> rsplit(Function step) const {
		List<Str> list;
		It i = a;
		while (*i) {
			while (*i) {
				int d = step(i);
				if (!d)
					break;
				i += d;
			}
			It j = i;
			while (*j && !step(j))
				++j;
			if (i != j)
				list << Str(i, j);
			i = j;
		}
		return list;
	}

	List<Str> rsplit(char c) const {
		return rsplit([c] (It i)->bool {
			return c == *i;
		});
	}

	List<Str> rsplit() const {
		return rsplit([] (It i)->bool {
			return isSpace(*i);
		});
	}

	template <typename Function>
	List<Str> split(Function step) const {
		return reversed(rsplit(step));
	}

	List<Str> split(char c) const {
		return reversed(rsplit(c));
	}

	List<Str> split() const {
		return reversed(rsplit());
	}

	template <typename Container>
	static Str join(const Container& c, const Str& d = "") {
		Str s;
		auto i = c.begin();
		if (i == c.end())
			return s;
		while (true) {
			s << *i++;
			if (i == c.end())
				break;
			s << d;
		}
		return s;
	}
};

inline u64 hash(const Str& s) {
	return hash(s.data(), s.size());
}

inline Str operator+(const Str& a, const Str& b) {
	Str s = a;
	return s << b;
}

inline bool operator==(const Str& a, const Str& b) {
	return a.cmp(b) == 0;
}

inline bool operator!=(const Str& a, const Str& b) {
	return a.cmp(b) != 0;
}

inline void puts(const Str& s) {
	puts(s.data());
}

inline void fputs(const Str& s, FILE* f) {
	fputs(s.data(), f);
}

inline void print(const Str& s) {
	fputs(s.data(), stdout);
}

inline void err(const Str& s, const Str& d = "\n") {
	fputs((s+d).data(), stderr);
}

#endif
