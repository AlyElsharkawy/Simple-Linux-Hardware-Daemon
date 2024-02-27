#include <iostream>
#include <csignal>
#include <fstream>
#include "miscFunctions.h"
#include "essentialFunctions.h"
#include "userVariables.h"

using namespace std;

const int MINUTE_CONST = 60;
const int TIMER_PRECISION = 5; //To make 10
const string previousFileName = "PREVIOUS_OUTPUT.prev";
int remainingSeconds = readPreviousOutputFile("/var/log/SLHD/" + previousFileName, MINUTE_CONST * TIMER_DELAY);

void interuptSignalHandler(int signalNumber)
{
  ofstream outputFile("/var/log/SLHD/" + previousFileName);
  outputFile << ((TIMER_DELAY * MINUTE_CONST) - remainingSeconds);
  outputFile.close();
  exit(signalNumber);
}

int main()
{
  //SLHD stands for simple linux hardware daemon
  signal(SIGINT, interuptSignalHandler);
  signal(SIGTERM, interuptSignalHandler);
  CreateFolder("/var/log/SLHD");
  while(true)
  {
    SleepSeconds(TIMER_PRECISION, remainingSeconds);
    string logFileName = CreateLogFile();
    SendEmail(logFileName, SENDER_EMAIL, "smtps://smtp.gmail.com:465", SENDER_PASSWORD, RECEPIENT_EMAIL);
    cout << "Program loop finished!\n";
    remainingSeconds = TIMER_DELAY * MINUTE_CONST;
  }
}
