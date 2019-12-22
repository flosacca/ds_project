#include "extractor.h"
#include "dom.h"

const Set<Str> Items[] = {
	Set<Str>{"导演", "编剧", "主演"},
	Set<Str>{"类型", "上映日期", "片长"},
	Set<Str>{"制片国家/地区", "语言", "又名"}
};

List<Pair> getInfo(const Str& html) {
	List<Pair> info;
	auto doc = DOM::parse(html);

	auto title = DOM::find(doc, [] (DOM::Node* v) {
		return v->tag == "title";
	});

	info << Pair{"title", title->innerHTML().gsub("(豆瓣)", "").strip()};

	auto div_info = DOM::find(doc, [] (DOM::Node* v) {
		return v->attrs.find(Pair{"id", "info"});
	});

	Vec<DOM::Node*> nodes;
	DOM::each(div_info, [&] (DOM::Node* v) {
		nodes << v;
	});

	for (int i = 0; i < nodes.size(); ++i) {
		if (!nodes[i]->attrs.find(Pair{"class", "pl"}))
			continue;

		Str name = nodes[i]->innerHTML().gsub(":", "");
		List<Str> a;

		if (Items[0].has(name)) {
			for (int j = i+1; nodes[j]->tag != "br"; ++j) {
				if (nodes[j]->tag == "a")
					a << nodes[j]->innerHTML();
			}
		} else if (Items[1].has(name)) {
			for (int j = i+1; nodes[j]->tag != "br"; ++j) {
				if (nodes[j]->tag == "span")
					a << nodes[j]->innerHTML();
			}
		} else if (Items[2].has(name)) {
			Str::ConstIt j = nodes[i]->r.find('>')+1;
			j.move(notSpace);
			a << Str(j, j.find('<'));
		}

		if (!a.empty())
			info << Pair{name, Str::join(a.reverse(), " / ")};
	}

	auto span_sum = DOM::find(doc, [] (DOM::Node* v) {
		return v->attrs.find(Pair{"class", "all hidden"});
	});

	if (!span_sum) {
		span_sum = DOM::find(doc, [] (DOM::Node* v) {
			return v->attrs.find(Pair{"property", "v:summary"});
		});
	}

	auto f = [] (const Str& s) {
		return s.gsub("　", "").strip().gsub("<br />", "\n");
	};

	info << Pair{"剧情简介", map<Str>(span_sum->innerHTML().split('\n'), f)};

	DOM::clear(doc);
	return info;
}
