#ifndef CONFIG_H
#define CONFIG_H

#include "splitter.h"

Splitter splitter() {
	return Splitter{
		"dic/main.txt",
		"dic/stop.txt",
		"dic/pre.txt",
		"dic/punc.txt"
	};
}

#endif
