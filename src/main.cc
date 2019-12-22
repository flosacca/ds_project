#include "ds.h"
#include "file.h"
#include "config.h"
#include "extractor.h"

int main(int argc, char** argv) {
	if (argc > 1) {
		write("main.log", Str::join(splitter().split(read(argv[1])), "\n"));
		return 0;
	}

	Splitter sp = splitter();

	findFiles("input/*.html").each([&] (auto&& name) {
		auto info = getInfo(read("input/" + name));

		Pair sum = info.top();
		Str text = map<Str>(info.pop().reverse(), [] (auto&& p) {
			return p[0] + "：" + p[1] + "\n";
		});
		text = text.gsub("title：", "");
		text << sum[0] + "：\n" + sum[1] + "\n";

		Str base = name.slice(0, name.rindex('.'));
		write("output/" + base + ".info", text);
		write("output/" + base + ".txt", Str::join(sp.split(sum[1]), "\n"));
	});
}
