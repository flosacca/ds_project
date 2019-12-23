#include "ds.h"
#include <QFileInfo>
#include <QDir>

int fileSize(const Str& path) {
	return QFileInfo(path.data()).size();
}

List<Str> findFiles(const Str& path) {
	List<Str> r;
	for (auto&& s: QDir(path.data()).entryList()) 
		if (s != "." && s != "..") {
			r << s.toStdString().data();
		}
	return r.reverse();
}
