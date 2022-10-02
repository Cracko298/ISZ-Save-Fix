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

		//Checking
		//ReadFile
		FILE *WriteData;
		FILE *ReadData;
		int DataBuf;	//Data Buffer
		ReadData = fopen(SelectedData, "rb");
	

		if (!ReadData) {
			std::cout << "Failed to Open Data!\n";
		}
		else {
			fseek(ReadData, PluginFileSeek, SEEK_SET);
			fread(&DataBuf, sizeof(DataBuf), 1, ReadData);
			fclose(ReadData);
		}

		std::cout << "Reading: " <<std::hex << DataBuf << std::endl;

			if(!inRange(MinimumValue, MaximumValue, DataBuf))
			{
				std::cout << "Writing file...\n";
				WriteData = fopen(SelectedData, "rb+");
				if (!WriteData)
				{
					std::cout << "File didn't exists!\n";
				}
				else
				{
					fseek(WriteData, PluginFileSeek, SEEK_SET);
					fwrite(&NewValue, sizeof(NewValue), 1, WriteData);
					std::cout << "Plugin: Ended. changed in Seek " << std::hex << PluginFileSeek << " the Value: " << NewValue << std::endl;
					EndInfo = "Plugin ended, changed in Seek " + std::to_string(PluginFileSeek) +  " the Value: " + std::to_string(NewValue) +  ".";
						MessageBox(nullptr, EndInfo.c_str(), "Plugin", MB_ICONINFORMATION);
					fclose(WriteData);
				}

			
			}

			else
			{

				EndInfo = "Plugin ended and changed nothing.";
				MessageBox(nullptr, EndInfo.c_str(), "Plugin", MB_ICONINFORMATION);
			}
		//Write File
		
			
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
				{
					sscanf(value.c_str(), "%x", &PluginFileSeek);
				}
				else if (param == "CRASH_VALUE_MIN")
					sscanf(value.c_str(), "%x", &MinimumValue);
				else if (param == "CRASH_VALUE_MAX")
					sscanf(value.c_str(), "%d", &MaximumValue);
				else if (param == "NEW_VALUE")
					sscanf(value.c_str(), "%d", &NewValue);
				else if (param == "NOTE")
					std::getline(in, PluginNote);
			

			}

		


			MessageBox(nullptr,  PluginCreatorName.c_str(), "Plugin Creator", MB_ICONINFORMATION);
			MessageBox(nullptr, PluginNote.c_str(), "Note", MB_ICONINFORMATION);
			// Log the loaded configuration


			Plugin::WriteAndReadFromPlugin(PluginFileSeek, MinimumValue, MaximumValue, NewValue, SelectedData);

			in.close();

			return true;
		
	}

	void Load(const char SelectedData[6])
	{
		// MessageBox(nullptr, "Unknown Plugins can corrupt your save File!", "Warning", MB_ICONWARNING);
		Read(FileDialog::Open(), SelectedData);
	}


};