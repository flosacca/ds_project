#ifndef ALGO_H
#define ALGO_H

template <typename T>
inline T min(const T& a, const T& b) {
	return a < b ? a : b;
}

template <typename T>
inline T max(const T& a, const T& b) {
	return b < a ? a : b;
}

template <typename It>
inline It next(It i) {
	return ++i;
}

template <typename It>
inline It prev(It i) {
	return --i;
}

template <typename It>
inline int distance(It l, It r) {
	int d = 0;
	for (; l != r; ++l)
		++d;
	return d;
}

template <typename OutputContainer, typename InputContainer, typename Function>
inline OutputContainer map(InputContainer&& c, const Function& f) {
	OutputContainer r;
	c.each([&] (auto&& v) { r << f(v); });
	return r;
}

template <typename OutputContainer, typename InputContainer>
inline OutputContainer map(InputContainer&& c) {
	OutputContainer r;
	c.each([&] (auto&& v) { r << v; });
	return r;
}

template <typename OutputContainer, typename InputContainer, typename Predicate>
inline OutputContainer select(InputContainer&& c, const Predicate& p) {
	OutputContainer r;
	c.each([&] (auto&& v) { if (p(v)) r << v; });
	return r;
}

#endif
