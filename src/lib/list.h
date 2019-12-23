#ifndef LIST_H
#define LIST_H

template <typename T>

class List {
protected:
	struct Node {
		T v;
		Node* r;
	};

	Node* h;

public:
	class ConstIt;

	class It {
		friend class List;
		friend class ConstIt;

	private:
		Node* i;

	public:
		It(Node* i = nullptr): i(i) {}

		operator T*() const { return &i->v; }
		T* operator->() const { return &i->v; }

		It& operator++() {
			i = i->r;
			return *this;
		}

		It operator++(int) {
			It j = i;
			i = i->r;
			return j;
		}
	};

	class ConstIt {
		friend class List;

	private:
		Node* i;

	public:
		ConstIt(Node* i = nullptr): i(i) {}
		ConstIt(It i): i(i.i) {}

		operator const T*() const { return &i->v; }
		const T* operator->() const { return &i->v; }

		ConstIt& operator++() {
			i = i->r;
			return *this;
		}

		ConstIt operator++(int) {
			ConstIt j = i;
			i = i->r;
			return j;
		}
	};

	List(): h(nullptr) {}

	List(const List& r): List() {
		for (auto&& v: r) {
			push(v);
		}
		reverse();
	}

	List& operator=(const List& r) {
		clear();
		for (auto&& v: r) {
			push(v);
		}
		reverse();
		return *this;
	}

	~List() { clear(); }

	bool empty() const { return !h; }

	It begin() { return h; }
	It end() { return nullptr; }

	ConstIt begin() const { return h; }
	ConstIt end() const { return nullptr; }

	T& top() { return h->v; }
	const T& top() const { return h->v; }

	List& push(const T& v) {
		h = new Node{v, h};
		return *this;
	}

	List& operator<<(const T& v) {
		return push(v);
	}

	List& pop() {
		Node* i = h->r;
		delete h;
		h = i;
		return *this;
	}

	void clear() { while (h) pop(); }

	int size() const {
		return distance(begin(), end());
	}

	List& reverse() {
		Node* i = nullptr;
		while (h) {
			Node* j = h->r;
			h->r = i;
			i = h;
			h = j;
		}
		h = i;
		return *this;
	}

	static void insert_after(It i, const T& v) {
		Node* o = i.i;
		o->r = new Node{v, o->r};
	}

	static void erase_after(It i) {
		Node* o = i.i;
		Node* j = o->r;
		o->r = j->r;
		delete j;
	}

	T* find(const T& v) {
		It i = h;
		while (i && v != *i)
			++i;
		return i;
	}

	const T* find(const T& v) const {
		ConstIt i = h;
		while (i && v != *i)
			++i;
		return i;
	}

	template <typename Predicate>
	T* find(const Predicate& p) {
		It i = h;
		while (i && !p(*i))
			++i;
		return i;
	}

	template <typename Predicate>
	const T* find(const Predicate& p) const {
		ConstIt i = h;
		while (i && !p(*i))
			++i;
		return i;
	}

	template <typename Function>
	List& each(const Function& f) {
		for (auto&& e: *this)
			f(e);
		return *this;
	}

	template <typename Function>
	const List& each(const Function& f) const {
		for (auto&& e: *this)
			f(e);
		return *this;
	}

	template <typename Function>
	List& each_with_index(const Function& f) {
		int i = 0;
		for (auto&& e: *this)
			f(e, i++);
		return *this;
	}

	template <typename Function>
	const List& each_with_index(const Function& f) const {
		int i = 0;
		for (auto&& e: *this)
			f(e, i++);
		return *this;
	}
};

template <typename T>
inline List<T> reversed(const List<T>& a) {
	List<T> r;
	for (auto&& v: a)
		r << v;
	return r;
}

#endif
