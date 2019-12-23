#ifndef DOM_H
#define DOM_H

#include "ds.h"

namespace DOM {

struct Node {
	Str tag;
	List<Pair<>> attrs;
	Vec<Node*> children;
	Str::ConstIt l, r;

	Node(const Str& s = ""): tag(s) {}

	Str innerHTML() const {
		return Str(l, r);
	}

	Node*& top() {
		return children.top();
	}

	Node* const& top() const {
		return children.top();
	}

	Node& operator<<(Node* v) {
		children << v;
		return *this;
	}
};

void clear(Node* v);

void p(Node* v);

Node* parse(const Str& html);

template <typename Predicate>
Node* find(Node* v, const Predicate& pred) {
	if (pred(v))
		return v;
	for (Node* w: v->children)
		if (Node* a = find(w, pred))
			return a;
	return nullptr;
}

template <typename Function>
void each(Node* v, const Function& f) {
	f(v);
	for (Node* w: v->children)
		each(w, f);
}

} // namespace DOM

#endif
