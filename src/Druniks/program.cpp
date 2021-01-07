#include <iostream>
#include <windows.h>
#include "serial.h"

#pragma comment(lib, "winmm.lib")

void PlayWavFile(const char* filename, bool complete);

int main()
{
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial("\\\\.\\COM5");    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength = 255;
	int readResult = 0;

	while (SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData, dataLength);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
		incomingData[readResult] = 0;

		printf("%s", incomingData);

		//Sleep(500);
	}
	return 0;
}

void PlayWavFile(const char* filename, bool complete)
{
	/*
	SND_SYNC will not return until the sound completes.
	SND_ASYNC will return immediately and play the sound in the background.
	*/

	PlaySound((LPCWSTR)filename, NULL, SND_FILENAME | (complete ? SND_SYNC : SND_ASYNC));
	//mciSendString((LPCWSTR)filename, NULL, 0, NULL);
}