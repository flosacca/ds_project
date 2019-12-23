#include "ds.h"
#include "file.h"
#include "config.h"

int main() {
	Splitter sp = splitter();
	Dic<Str, OrderedList<Pair<int>>> docs;

	findFiles("input/*.html").each([&] (auto&& name) {
		int id = name.slice(0, name.rindex('.')).to_i();
		auto info = getInfo(read("input/" + name));

		Str sum = info["summary"];
		Str title = info["title"];

		Dic<Str, int> count;
		sp.split(sum).each([&] (auto&& w) {
			++count[w];
		});

		count.each([&] (auto&& k, auto&& v) {
			docs[k] << Pair<int>{v, id};
		});
	});

	open("result1.txt", "w", [&] (auto&& f) {
		read("query1.txt").split('\n').each([&] (auto&& line) {
			Dic<int, Pair<int>> dic;
			line.split().each([&] (auto&& lword) {
				sp.split(lword).each([&] (auto&& word) {
					docs[word].each([&] (auto&& p) {
						++dic[p[1]][0];
						dic[p[1]][1] += p[0];
					});
				});
			});

			OrderedList<Array<int, 3>> ol;
			dic.each([&] (auto&& id, auto&& v) {
				ol << Array<int, 3>{v[0], v[1], id};
			});

			int n = ol.size();
			map<List<Array<int, 3>>>(ol).each_with_index([&] (auto&& v, int i) {
				fprintf(f, "(%d,%d)%c", v[2], v[1], i < n-1 ? ' ' : '\n');
			});
		});
	});

	// open("result2.txt", "w", [&] (auto&& f) {
	// 	read("query2.txt").split('\n').each([&] (auto&& title) {
	// 		if (auto p = words.find(title)) {
	// 			Dic<int, Vec<int>> dic;
	// 			words.each([&] (auto&& k, auto&& v) {
	// 				if (k != title)
	// 					dic[(p->second & v.second).size()] << v.first;
	// 			});
	// 		}
	// 	});
	// });

	// FILE* f = fopen("main.log", "w");
	// docs.each([&] (auto&& word, auto&& list) {
	// 	fputs(word + "\n", f);
	// 	map<List<Pair<int>>>(list).each([&] (auto&& p) {
	// 		fprintf(f, "(%d, %d) ", p[0], p[1]);
	// 	});
	// 	fputs("\n", f);
	// });
	// fclose(f);
}
