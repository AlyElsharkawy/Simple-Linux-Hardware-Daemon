#pragma once
#include <string>

using namespace std;

string CreateLogFile();
void SendEmail(const string& inputFileName, const string& senderEmail, const string& serverURL, const string& senderPassword, const string& receiverEmail);
int readPreviousOutputFile(string fileName, const int& defaultTime); //This will load the previous remaining time before the daemon was closed

