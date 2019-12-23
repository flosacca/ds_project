#include "ds.h"
#include <windows.h>

int fileSize(const Str& path) {
	WIN32_FILE_ATTRIBUTE_DATA info;
	if (GetFileAttributesEx(path.data(), GetFileExInfoStandard, &info))
		return info.nFileSizeLow;
	return 0;
}

List<Str> findFiles(const Str& path) {
	List<Str> r;

	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile((path + "/*").data(), &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		while (true) {
			Str s = data.cFileName;
			if (s != "." && s != "..")
				r << s;
			if (!FindNextFile(hFind, &data))
				break;
		}
		FindClose(hFind);
	}

	return r.reverse();
}

