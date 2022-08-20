#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
class troubleshootData {
private:
	bool CheckClothes(unsigned char Value[1]) {
		if (Value[0] > 0xF) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CheckPosition(unsigned char Value[8]) {
		for (int i = 0; sizeof(Value); i++) {
			if (Value[i] == 0xFF) {
				return true;
			}
				else
				{
				return false;
				}
			}
	}

	void ErrorText(char ErrorText[100], static int ErrCount){
		switch (ErrCount)
		{
		case 0:
			strcpy(ErrorText, "Error: Clothes!");
			break;
		case 1:
			strcpy(ErrorText, "Error: Position!");
			break;
		case 2:
			strcpy(ErrorText, "Errors: 0");
			break;

		}
		
	}
public:
	bool NextError(char errorText[100], unsigned char ValueClothes[1], unsigned char ValuePosition[8]){
		static int ErrorCount = 0;
		
		if(ErrorCount==0) {
			bool isCorrupted = CheckClothes(ValueClothes);
			switch (isCorrupted)
			{
			case false:
				return true;
				break;

			case true:
				ErrorText(errorText, 0);
				break;
			}
		}
			if (ErrorCount == 1){
				bool isCorrupted = CheckPosition(ValuePosition);
				switch (isCorrupted)
				{
				case false:
					return true;
					break;

				case true:
					ErrorText(errorText, 1);
					break;
				}
			}
			if (ErrorCount==2){
				ErrorText(errorText, 2);
				ErrorCount = -1;
				return true;
			}
			std::cout << ErrorCount;
			ErrorCount++;
	}
};



void troubleshoot(char SelectedSlot[6], char error[100]) {
	troubleshootData Problem;

	unsigned char buffer[1];
	unsigned char Position[8];

	FILE *Data;
	Data = fopen(SelectedSlot, "rb");

	fseek(Data, 52, SEEK_SET);
	fread(buffer, sizeof(buffer), 1, Data);

	bool NextError = Problem.NextError(error, buffer, Position);

	if (NextError) {
		fseek(Data, 24, SEEK_SET);
		fread(Position, sizeof(Position), 1, Data);
		Problem.NextError(error, buffer, Position);
	}


	fclose(Data);
}

void RepairSave(char SelectedSlot[6]) {

}