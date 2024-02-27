#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <filesystem>
#include <sstream>
#include "miscFunctions.h"

using namespace std;

void SleepSeconds(const int& precision, int& remainingSeconds)
{
  if (remainingSeconds <= 0) 
    return;
  while(remainingSeconds >= 0)
  {
    if (precision > remainingSeconds) 
    {
      this_thread::sleep_for(chrono::seconds(remainingSeconds));
      remainingSeconds = 0;
      return;
    }
    else 
    {
      this_thread::sleep_for(chrono::seconds(precision));
      remainingSeconds -= precision;
    }
  }
}

void SleepMilliSeconds(const int &precision, int& remainingMiliseconds)
{

  if (remainingMiliseconds <= 0) 
    return;
  if (precision > remainingMiliseconds) 
  {
    this_thread::sleep_for(chrono::milliseconds(remainingMiliseconds));
    remainingMiliseconds = 0;
  } 
  else 
  {
    this_thread::sleep_for(chrono::milliseconds(precision));
    remainingMiliseconds -= precision; // Decrement remainingSeconds by the delay.
  }
}

void CreateFolder(const string &fileName)
{
  try
  {
    if(filesystem::create_directory(fileName))
      cout << "Directory " << fileName << " succesfully created\n";
    else 
      cout << "Directory could not be created. It either already exists or the folder name contains illegal characters\n";
  }
  catch(filesystem::filesystem_error& exception)
  {
    cerr << "Error: " << exception.what() << "\n";
  }
}

string getCurrentDate()
{
  //Why are dates so weird in C++?!
  auto chronoTime = chrono::system_clock::now();
  time_t tTime = chrono::system_clock::to_time_t(chronoTime);
  auto cTime = *localtime(&tTime);
  ostringstream stringConvertor;
  stringConvertor <<  put_time(&cTime, "%H:%M_%d-%m-%Y");
  return stringConvertor.str();
}

string getHomeDirectory()
{
  string temp = getenv("HOME");
  return temp + "/";
}



