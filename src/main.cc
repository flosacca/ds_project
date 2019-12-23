#include "doc.h"
#include "file.h"

int main() {
	Doc doc;

	open("result1.txt", "w", [&] (auto& f) {
		read("query1.txt").split('\n').each([&] (auto& words) {
			auto ol = doc.search(words);
			int n = ol.size();
			map<List<Array<int, 3>>>(ol).each_with_index([&] (auto& a, int i) {
				fprintf(f, "(%d,%d)%c", a[2], a[1], i < n-1 ? ' ' : '\n');
			});
		});
	});

	open("result2.txt", "w", [&] (auto& f) {
		read("query2.txt").split('\n').each([&] (auto& title) {
			auto vec = doc.recommend(title, 5);
			if (vec.empty()) {
				fputs(f, "Movie not found");
			} else {
				vec.each_with_index([&] (int id, int i) {
					fprintf(f, "(%d,%s)%s", id, doc.title(id).data(), i < vec.size()-1 ? ", " : "\n");
				});
			}
		});
	});
}
