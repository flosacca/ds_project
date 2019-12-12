#include "ds.h"
#include "file.h"
#include "dom.h"
#include "splitter.h"

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

	info << Pair{"title", title->innerHTML().sub("(豆瓣)", "").strip()};

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

		Str name = nodes[i]->innerHTML().sub(":", "");
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
		return s.sub("　", "").strip().sub("<br />", "\n");
	};

	info << Pair{"剧情简介", map<Str>(span_sum->innerHTML().split('\n'), f)};

	DOM::clear(doc);
	return info;
}

Splitter splitter() {
	return Splitter{
		"dic/main.txt",
		"dic/punc.txt",
		"dic/mid.txt",
		"dic/pre.txt"
	};
}

int main(int argc, char** argv) {
	if (argc > 1) {
		write("main.log", Str::join(splitter().split(read(argv[1])), "\n"));
		return 0;
	}

	auto f = [] (const Pair& p)->Str {
		return p[0] + "：" + p[1] + "\n";
	};

	Splitter sp = splitter();

	for (auto&& s: findFiles("input/*.html")) {
		auto info = getInfo(read("input/" + s));
		Pair t = info.top();
		Str noExt = s.slice(0, s.rindex('.'));
		write("output/" + noExt + ".info", map<Str>(info.pop().reverse(), f).sub("title：", "") + (t[0] + "：\n" + t[1] + "\n"));
		write("output/" + noExt + ".txt", Str::join(sp.split(t[1]), "\n"));
	}
}
