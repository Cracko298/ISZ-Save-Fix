#include "RepairCrash.hpp"
#include "FileDialog.hpp"

#include <fstream>
#include <string>


bool inRange(unsigned low, unsigned high, unsigned x)
{
	return (low < x && x < high);
}

namespace Plugin
{
	void WriteAndReadFromPlugin(const int &PluginFileSeek, const int &MinimumValue, const int &MaximumValue, const int &NewValue, const char SelectedData[6])
	{ 
			std::string EndInfo;
			int ReadedData = ReadFile(PluginFileSeek, SelectedData);

			std::cout << "Readed: " << std::hex << ReadedData << std::endl;

		if (!inRange(MinimumValue, MaximumValue, ReadedData))
		{
			WriteFile(PluginFileSeek, SelectedData, NewValue);
			EndInfo = "Plugin ended, changed in Seek " + std::to_string(PluginFileSeek) + " the Value: " + std::to_string(NewValue) + ".";
		}
		else
		{
			EndInfo = "Plugin ended and changed nothing. (No Crashes found!)";
		}
		MessageBox(nullptr, EndInfo.c_str(), "Plugin", MB_ICONINFORMATION);
}





	bool Read(const std::string &path, const char SelectedData[6])
	{
		std::string PluginCreatorName;
		std::string PluginNote;
		int PluginFileSeek = 0;
		int MinimumValue = 0;
		int MaximumValue = 0;
		int NewValue = 0;

		std::cout << "***Plugin Loader v0.1***\n\n";

		std::ifstream in(path);

		if (!in.is_open())
		{
			std::cout << "Cannot Open the Plugin file.";
			return false;
		}

		std::string param;
		std::string value;


		while (!in.eof())
		{
			in >> param;
			in >> value;

			if (param == "CREATOR")
			{
				PluginCreatorName = value;
			}
			else if (param == "SEEK")
				sscanf(value.c_str(), "%x", &PluginFileSeek);
			else if (param == "CRASH_VALUE_MIN")
				sscanf(value.c_str(), "%d", &MinimumValue);
			else if (param == "CRASH_VALUE_MAX")
				sscanf(value.c_str(), "%d", &MaximumValue);
			else if (param == "NEW_VALUE")
				sscanf(value.c_str(), "%d", &NewValue);
			else if (param == "NOTE")
				std::getline(in, PluginNote);


		}

		std::cout << "Seek:" <<PluginFileSeek << std::endl;
		std::cout << "CRASH_VALUE_MIN:" << MinimumValue << std::endl;
		std::cout << "CRASH_VALUE_MAX:" << MaximumValue << std::endl;
		std::cout << "NEW_VALUE:" << NewValue << std::endl;
		std::cout << "NOTE:" << PluginNote << std::endl;

		MessageBox(nullptr, PluginCreatorName.c_str(), "Plugin Creator", MB_ICONINFORMATION);
		MessageBox(nullptr, PluginNote.c_str(), "Note", MB_ICONINFORMATION);
		// Log the loaded configuration


		Plugin::WriteAndReadFromPlugin(PluginFileSeek, MinimumValue, MaximumValue, NewValue, SelectedData);

		in.close();

		return true;

	}

	void Load(const char SelectedData[6])
	{
		// MessageBox(nullptr, "Unknown Plugins can corrupt your save File!", "Warning", MB_ICONWARNING);
		char path[1024];
		path[0] = 0;
		OPENFILENAME LoadDL = {};
		LoadDL.lStructSize = sizeof(OPENFILENAME);
		LoadDL.lpstrFilter = "ZPlugin-Files (.Zplg)\0*.Zplg;\0All Files\0*.*";
		LoadDL.lpstrCustomFilter = 0;
		LoadDL.nMaxCustFilter = 0;
		LoadDL.nFilterIndex = 0;
		LoadDL.lpstrFile = path;
		LoadDL.nMaxFile = 256;
		LoadDL.nMaxFileTitle = 1024;
		LoadDL.lpstrTitle = "Select a Plugin to load";
		LoadDL.Flags = OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
	
		if (GetOpenFileName(&LoadDL) != 0)
			Read(path, SelectedData);
	}


};
