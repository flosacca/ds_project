#include "dom.h"

const Set<Str> VoidElements{
	"area",
	"base",
	"br",
	"col",
	"command",
	"embed",
	"hr",
	"img",
	"input",
	"keygen",
	"link",
	"meta",
	"param",
	"source",
	"track",
	"wbr"
};

void DOM::p(Node* v) {
	static int d = 0;
	for (int i = 0; i < d; ++i)
		print("  ");
	++d;

	print(v->tag + ":");
	v->attrs.each([] (auto& k, auto& v) {
		print(" " + k + "=\"" + v + "\"");
	});
	puts("");

	for (auto& w: v->children)
		p(w);

	--d;
}

bool isDelim(char c) {
	return c == '>' || isSpace(c);
}

DOM::Node* DOM::parse(const Str& html) {
	Stack<Node*> s;
	s << new Node;
	auto i = html.begin();

	while (*i.move('<')) {
		if (*++i == '!') {
			i.move('>');
			continue;
		}

		bool closing = *i == '/';
		if (closing)
			++i;

		auto j = i.find(notAlpha);
		Str tag(i, j);

		if (!closing) {
			Node* v = new Node(tag);
			*s.top() << v;
			i = j;

			while (*i) {
				if (*i.move(notSpace) == '>')
					break;
				j = i.find([=] (char c) {
					return c == '=' || isDelim(c);
				});

				Str name(i, j);
				i = j;

				if (*i.move(notSpace) != '=')
					continue;
				++i;

				if (*i.move(notSpace) == '>')
					break;
				if (*i == '\"')
					j = (++i).find('\"');
				else if (*i == '\'')
					j = (++i).find('\'');
				else {
					j = i.find(isDelim);
				}

				v->attrs[name] = Str(i, j);
				i = j.find(isDelim);
			}

			if (!*i) {
				v->l = i;
				break;
			}
			v->l = ++i;

			if (tag == "script") {
				while (true) {
					i.move('<');
					if (!*i || (++i).match("/script"))
						break;
				}
				v->r = i-1;
			} else {
				if (VoidElements.has(tag))
					v->r = i;
				else {
					s << v;
				}
			}

		} else {
			while (s.size() > 1) {
				Node* v = s.pop();
				v->r = i-2;
				if (tag == v->tag)
					break;
			}
			i = j.find('>');
		}
	}

	while (s.size() > 1)
		s.pop()->r = i;

	return s.top();
}
