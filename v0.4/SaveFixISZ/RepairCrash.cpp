#include <iostream>
#include <string>

#include "RepairCrash.hpp"


//Reading a File in binary mode, returns the value.
void WriteFile(int seek, char DataName[6], unsigned int Value) {
	FILE *WriteData;
	WriteData = fopen(DataName, "rb+");

	if (!WriteData) {
		std::cout << "File didn't exists!\n";
	}
	else {
		fseek(WriteData, seek, SEEK_SET);
		fwrite(&Value, sizeof(Value), 1, WriteData);
		fclose(WriteData);
	}
}

//Reading a File in binary mode, returns the value.
int ReadFile(int seek, char DataName[6]){
	FILE *ReadData;
	int DataBuf;	//Data Buffer
	ReadData = fopen(DataName, "rb");

	if (!ReadData){
		return 1;
	}
	else {
		fseek(ReadData, seek, SEEK_SET);
		fread(&DataBuf, sizeof(DataBuf), 1, ReadData);
		fclose(ReadData);
		return DataBuf;
	}
}

//Private
//Check if the File Exists, returns true if its exits otherwise false.
bool Data::_FileExists(char FileName[6])
{
	FILE *DataExists;
	DataExists = fopen(FileName,"r");
	if (!DataExists) {
		std::cout << "File didn't exists!\n";
		return false;
	}
	else {
		return true;
	}
}

//Public
void Data::RepairCrash(char FileName[6])
{
	std::cout << "Repairing "<< FileName <<" ...\n";
	
	//Repair Position
	WriteFile(20, FileName, 0x4487B32A);
	WriteFile(24, FileName, 0x427ED37F);
	WriteFile(28, FileName, 0xC4DFFD10);

	//Repair Clothes
	WriteFile(52, FileName, 0x1);
	WriteFile(56, FileName, 0x2);
	WriteFile(60, FileName, 0x3);

	bool FileExists = _FileExists(FileName);
	switch (FileExists)
	{
	case true:
		std::cout << "Succesfully, try to use your Save!\n";
		ErrorString = "Succesfully, try to use your Save!\n";
		break;
		//file didn't exists
	case false:
		std::cout << "File didn't exists!\n";
		ErrorString = FileName;
		ErrorString += " didnt't exists!";
		break;
	}
}



void Data::CheckData(char FileName[6])
{
	//Error types
	bool ClothesCrash = false;
	bool PositionCrash = false;

	int Data;	//Buffer to Read.

	//Error's
	//Position Errors:
	Data = ReadFile(20, FileName);
	if (Data > 0xCC000000) {
		std::cout << "Player Position Z is too High!\n";
		PositionCrash = true;
		ErrorString += "Player Position Z is too High!\n";
	}
	Data = ReadFile(24, FileName);
	if (Data > 0xC5000000) {
		std::cout << "Player Position X is too High!\n";
		PositionCrash = true;
		ErrorString += "Player Position X is too High!\n";
	}
	Data = ReadFile(28, FileName);
	if (Data > 0xC9000000) {
		std::cout << "Player Position Y is too High!\n";
		PositionCrash = true;
		ErrorString += "Player Position Y is too High!\n";
	}

	//Clothes Errors
	Data = ReadFile(52, FileName);
	if (Data > 0x10) {
		std::cout << "Error Clothes out of Range!\n";
		ClothesCrash = true;
	}
	Data = ReadFile(56, FileName);
	if (Data > 0x10) {
		std::cout << "Error Clothes out of Range!\n";
		ClothesCrash = true;
	}
	Data = ReadFile(60, FileName);
	if (Data > 0x10) {
		std::cout << "Error Clothes out of Range!\n";
		ClothesCrash = true;
	}

	if (PositionCrash == false & ClothesCrash == false)
		ErrorString = "No Errors found!\n";
	

	if (ClothesCrash)
		ErrorString += "Clothes out of range!\n";

	bool FileExists = _FileExists(FileName);
	switch (FileExists)
	{
	//file didn't exists
	case false:
		ErrorString = "File didn't exists!";
		break;
	}
}