#include <iostream>
#include <fstream>
#include <windows.h>
#include "serial.h"

#pragma comment(lib, "winmm.lib")

#define STR2LPCWSTR(s) std::wstring(s.begin(), s.end()).c_str()

void playWavFile(const std::string& filename, bool complete);

int main()
{
	playWavFile("..\\..\\data\\samples\\StarWars3.wav", true);
}

//int main()
//{
//	printf("Welcome to the serial test app!\n\n");
//
//	Serial* SP = new Serial("\\\\.\\COM5");    // adjust as needed
//
//	if (SP->IsConnected())
//		printf("We're connected");
//
//	char incomingData[256] = "";			// don't forget to pre-allocate memory
//	//printf("%s\n",incomingData);
//	int dataLength = 255;
//	int readResult = 0;
//
//	while (SP->IsConnected())
//	{
//		readResult = SP->ReadData(incomingData, dataLength);
//		// printf("Bytes read: (0 means no data available) %i\n",readResult);
//		incomingData[readResult] = 0;
//
//		printf("%s", incomingData);
//
//		//Sleep(500);
//	}
//	return 0;
//}

inline bool testFileExists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

void playWavFile(const std::string& filename, bool complete)
{
	/*
	SND_SYNC will not return until the sound completes.
	SND_ASYNC will return immediately and play the sound in the background.
	*/

	if (testFileExists(filename))
	{
		std::cout << "File exists" << std::endl;
	}
	else
	{
		std::cout << "File doesn't exist" << std::endl;
	}

	PlaySound(STR2LPCWSTR(filename), NULL, SND_FILENAME | (complete ? SND_SYNC : SND_ASYNC));
	system("pause");
	//mciSendString((LPCWSTR)filename, NULL, 0, NULL);
}

