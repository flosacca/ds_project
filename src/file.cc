#include "file.h"
#include <windows.h>
#include <stdio.h>

u64 fileSize(const Str& name) {
	WIN32_FILE_ATTRIBUTE_DATA info;
	if (GetFileAttributesEx(name.data(), GetFileExInfoStandard, &info))
		return (u64)info.nFileSizeHigh << 32 | info.nFileSizeLow;
	return 0;
}

List<Str> findFiles(const Str& pattern) {
	List<Str> a;

	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(pattern.data(), &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		while (true) {
			Str s = data.cFileName;
			if (s != "." && s != "..")
				a << s;
			if (!FindNextFile(hFind, &data))
				break;
		}
		FindClose(hFind);
	}

	return a.reverse();
}

Str read(const Str& name) {
	if (FILE* f = fopen(name.data(), "r")) {
		Str s(f, fileSize(name));
		fclose(f);
		return s;
	}
	return "";
}

void write(const Str& name, const Str& s) {
	FILE* f = fopen(name.data(), "w");
	fwrite(s.data(), 1, s.size(), f);
	fclose(f);
}
