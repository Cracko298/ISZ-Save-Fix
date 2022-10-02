#include "FileDialog.hpp"

namespace FileDialog
{
	std::string Open()
	{
		std::string path(MAX_PATH, '\0');
		OPENFILENAME ofn = { sizeof(OPENFILENAME) };
		ofn.lpstrFilter =	"Zplg\0*.Zplg*\0All files\0*.*\0";
		ofn.lpstrFile = &path[0];
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_FILEMUSTEXIST;
		if (GetOpenFileName(&ofn))
		{
			//string::size() is still MAX_PATH
			//strlen is the actual string size (not including the null-terminator)
			//update size:
			path.resize(strlen(path.c_str()));
		}
		return path;
	}

		void Save()
		{
		}
};