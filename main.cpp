#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <map>
#include <string>
#include <iostream>

std::map<int, int> distr;

inline std::wstring operator/(const std::wstring &d, const std::wstring &f) { return d.back() == L'/' ? d + f : d + L'/' + f; }

void enum_files_recursively(const std::wstring &dir_name)
{
	WIN32_FIND_DATA fd;
	HANDLE h = FindFirstFile((dir_name / L"*.*").c_str(), &fd);
	if (h == INVALID_HANDLE_VALUE) return;

	do
	{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) // skip symbolic links
			continue;

		std::wstring file_name(fd.cFileName);
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (file_name == L"." || file_name == L"..")
				continue;

			enum_files_recursively(dir_name / file_name);
		}
		else
			distr[file_name.length()]++;

	} while (FindNextFile(h, &fd));

	FindClose(h);
}

int main()
{
	enum_files_recursively(L"C:");

	for (const auto &d : distr)
		std::cout << d.first << "," << d.second << "\n";
}
