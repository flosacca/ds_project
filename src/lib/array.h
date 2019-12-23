#ifndef ARRAY_H
#define ARRAY_H

template <typename T, int N>

struct Array {
	T a[N];

	operator T*() { return a; }
	T* begin() { return a; }
	T* end() { return a+N; }

	operator const T*() const { return a; }
	const T* begin() const { return a; }
	const T* end() const { return a+N; }

	int cmp(const Array& r) const {
		for (int i = 0; i < N; ++i) {
			if (a[i] < r[i])
				return -1;
			if (a[i] > r[i])
				return 1;
		}
		return 0;
	}

	template <typename Function>
	Array& each(const Function& f) {
		for (auto& e: *this)
			f(e);
		return *this;
	}

	template <typename Function>
	const Array& each(const Function& f) const {
		for (auto& e: *this)
			f(e);
		return *this;
	}
};

template <typename T, int N>
inline bool operator==(const Array<T, N>& a, const Array<T, N>& b) {
	return a.cmp(b) == 0;
}

template <typename T, int N>
inline bool operator!=(const Array<T, N>& a, const Array<T, N>& b) {
	return a.cmp(b) != 0;
}

template <typename T, int N>
inline bool operator<(const Array<T, N>& a, const Array<T, N>& b) {
	return a.cmp(b) < 0;
}

template <typename T, int N>
inline bool operator>(const Array<T, N>& a, const Array<T, N>& b) {
	return a.cmp(b) > 0;
}

template <typename T, int N>
inline bool operator<=(const Array<T, N>& a, const Array<T, N>& b) {
	return a.cmp(b) <= 0;
}

template <typename T, int N>
inline bool operator>=(const Array<T, N>& a, const Array<T, N>& b) {
	return a.cmp(b) >= 0;
}

#endif
