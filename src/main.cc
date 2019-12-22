#include "ds.h"
#include "file.h"
#include "config.h"
#include "extractor.h"

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
		write("output/" + noExt + ".info", map<Str>(info.pop().reverse(), f).gsub("title：", "") + (t[0] + "：\n" + t[1] + "\n"));
		write("output/" + noExt + ".txt", Str::join(sp.split(t[1]), "\n"));
	}
}
