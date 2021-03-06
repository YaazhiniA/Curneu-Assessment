#include<Windows.h>
#include<iostream>
#include<vector>
#include<string>

using namespace std;

std::string GetProgramPath() {
	using namespace std;
	string pt(_MAX_PATH + 1, '\0');
	GetModuleFileName(NULL, (LPSTR)pt.c_str(), _MAX_PATH);
	return pt;
}
std::string& CutToFolder(std::string& path)
{
	char c;
	int len = path.length();
	while (len && (c = path[len--] != '\\'));
	path[len + 1] = '\0';
	path.resize(len + 1);
	return path;
}

std::string AddFolder(std::string& path, string& fold, bool add_folder = true)
{
	if (add_folder)
		return std::string(path + '\\' + fold);
	else
		return std::string(path + fold);
}
std::string AddFolder(std::string& path, int i)
{
	return AddFolder(path, std::to_string(i));
}

std::string CreateFolder(std::string& path)
{
	if (CreateDirectory(path.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		return path;
	}
	return "\0";
}

void CreateFolderRange(std::string& path, int count)
{
	while (count)
		CreateFolder(AddFolder(path, count--));
}


vector<string>  GetAllFiles(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.zip";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}


std::string BrowseFolder(std::string saved_path)
{
	TCHAR path[MAX_PATH];

	const char * path_param = saved_path.c_str();

	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("Browse for folder...");

	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)path_param;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);


	return "";
}


int main(int argc, char* argv[]) {


	string path;
	if (argc > 1)
	{
		path = argv[1];
		goto doing;
	}
	path = (GetProgramPath());

	int result = MessageBox(NULL, "Use current folder?\n(No) for selecting another one", "question", MB_YESNO);

doing:
	cout << path << endl;
	vector<string> files = GetAllFiles(path);
	for (int i = 0; i < files.size(); i++)
	{
		std::string& _folder = AddFolder(path, CutToName(files[i]));
		std::tring& _file = AddFolder(path, files[i]);
	}

}
