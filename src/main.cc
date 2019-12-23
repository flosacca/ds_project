#include "doc.h"
#include "file.h"

int main() {
	Doc doc;

	open("result1.txt", "w", [&] (auto& f) {
		read("query1.txt").split('\n').each([&] (auto& words) {
			auto ol = doc.search(words);
			int n = ol.size();
			map<List<Array<int, 3>>>(ol).each_with_index([&] (auto& a, int i) {
				fprintf(f, "(%d,%d)", a[2], a[1]);
				if (i < n-1)
					fputs(" ", f);
			});
			fputs("\n", f);
		});
	});

	open("result2.txt", "w", [&] (auto& f) {
		read("query2.txt").split('\n').each([&] (auto& title) {
			auto ids = doc.recommend(title, 5);
			if (ids.empty()) {
				fputs(f, "Movie not found");
			} else {
				ids.each_with_index([&] (int id, int i) {
					fprintf(f, "(%d,%s)", id, doc.title(id).data());
					if (i < ids.size()-1)
						fputs(", ", f);
				});
				fputs("\n", f);
			}
		});
	});
}
