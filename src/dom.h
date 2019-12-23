#ifndef DOM_H
#define DOM_H

#include "ds.h"

class DOM {
public:
	struct Node {
		Str tag;
		Dic<Str, Str> attrs;
		Vec<Node*> children;
		Str::ConstIt l, r;

		Node(const Str& s = ""): tag(s) {}

		Str innerHTML() const {
			return Str(l, r);
		}

		Node*& top() {
			return children.top();
		}

		Node& operator<<(Node* v) {
			children << v;
			return *this;
		}

		template <typename Predicate>
		Node* find(const Predicate& p) {
			return find(this, p);
		}

		template <typename Function>
		Node& each(const Function& f) {
			dfs(this, f);
			return *this;
		}

	private:
		template <typename Predicate>
		static Node* find(Node* v, const Predicate& p) {
			if (p(v))
				return v;
			for (Node* w: v->children)
				if (Node* a = find(w, p))
					return a;
			return nullptr;
		}

		template <typename Function>
		static void dfs(Node* v, const Function& f) {
			f(v);
			for (Node* w: v->children)
				dfs(w, f);
		}
	};

	Node* r;

	DOM(const Str& html): r(parse(html)) {}

	DOM(const DOM&) = delete;
	DOM& operator=(const DOM&) = delete;

	~DOM() { clear(r); }

	template <typename Predicate>
	Node* find(const Predicate& p) {
		return r->find(p);
	}

	template <typename Function>
	Node& each(const Function& f) {
		return r->each(f);
	}

private:
	static void clear(Node* v) {
		for (auto& w: v->children)
			clear(w);
		delete v;
	}

	static void p(Node* v);

	static Node* parse(const Str& html);
};

#endif
