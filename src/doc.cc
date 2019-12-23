#include "doc.h"
#include "file.h"
#include "extractor.h"

Splitter splitter() {
	return Splitter({
		"dic/main.txt",
		"dic/stop.txt",
		"dic/pre.txt",
		"dic/punc.txt"
	});
}

Doc::Doc(): sp(splitter()) {
	findFiles("input").each([&] (auto& name) {
		int id = name.slice(0, name.rindex('.')).to_i();
		auto info = getInfo(read("input/" + name));

		Str sum = info["summary"];
		titles[id] = info["title"];
		tags[titles[id]] = {id, map<Set<Str>>(info["tags"].split(','))};

		Dic<Str, int> count;
		sp.split(sum).each([&] (auto& w) {
			++count[w];
		});

		count.each([&] (auto& k, auto& v) {
			occurs[k] << Pair<int>{v, id};
		});
	});
}

OrderedList<Array<int, 3>> Doc::search(const Str& words) const {
	Dic<int, Pair<int>> dic;
	sp.split(words).each([&] (auto& word) {
		occurs.find(word)->each([&] (auto& pair) {
			++dic[pair[1]][0];
			dic[pair[1]][1] += pair[0];
		});
	});

	OrderedList<Array<int, 3>> ol;
	dic.each([&] (auto& id, auto& pair) {
		ol << Array<int, 3>{pair[0], pair[1], id};
	});
	return ol;
}

Vec<int> Doc::recommend(const Str& title, int count) const {
	Vec<int> vec;
	if (auto q = tags.find(title)) {
		Dic<int, Vec<int>> dic;
		tags.each([&] (auto& k, auto& p) {
			if (k != title)
				dic[(q->second & p.second).size()] << p.first;
		});

		dic.reverse_each([&] (auto&, auto& a) {
			vec.push(a.begin(), a.begin() + min(a.size(), count-vec.size()));
		});
	}
	return vec;
}
