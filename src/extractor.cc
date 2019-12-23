#include "ds.h"
#include "dom.h"

const Set<Str> Items[] = {
	Set<Str>{"导演", "编剧", "主演"},
	Set<Str>{"类型", "上映日期", "片长"},
	Set<Str>{"制片国家/地区", "语言", "又名"}
};

Dic<Str, Str> getInfo(const Str& html) {
	Dic<Str, Str> info;

	DOM doc(html);

	Str& title = info["title"];
	title = doc.find([] (auto&& v) { return v->tag == "title"; })->innerHTML();
	title = title.gsub("(豆瓣)", "").strip();

	auto nodes = map<Vec<DOM::Node*>>(*doc.find([] (auto&& v) {
		return v->attrs.has("id", "info");
	}));

	for (int i = 0; i < nodes.size(); ++i) {
		if (!nodes[i]->attrs.has("class", "pl"))
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
			info[name] = Str::join(a.reverse(), " / ");
	}

	auto spanSum = [&] {
		auto p = doc.find([] (auto&& v) {
			return v->attrs.has("class", "all hidden");
		});
		return p ? p : doc.find([] (auto&& v) {
			return v->attrs.has("property", "v:summary");
		});
	} ();

	info["summary"] = map<Str>(spanSum->innerHTML().split('\n'), [] (auto&& s) {
		return s.gsub("　", "").strip().gsub("<br />", "\n");
	});

	auto divTags = doc.find([] (auto&& v) {
		return v->attrs.has("class", "tags-body");
	});

	auto& tags = info["tags"];
	tags = map<Str>(divTags->children, [] (auto&& v) {
		return v->innerHTML() + ",";
	});
	tags.pop();

	return info;
}
