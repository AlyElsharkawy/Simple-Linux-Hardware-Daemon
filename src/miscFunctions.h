#pragma once
#include <string>

using namespace std;

void SleepSeconds(const int& precision, int& remainingSeconds);
void SleepMilliSeconds(const int& precision, int& remainingMiliseconds);
void CreateFolder(const string& fileName);
string getCurrentDate();
string getHomeDirectory();
