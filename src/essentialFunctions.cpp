#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <iostream>
#include <curl/curl.h>
#include <unistd.h>
#include "essentialFunctions.h"
#include "miscFunctions.h"

using namespace std;

string CreateLogFile()
{
  string fileName = getCurrentDate() + ".log";
  string pathName =  "/var/log/SLHD/" + fileName;
  ofstream logFile(pathName);

  string hddCommand1 = "lsblk >> ";
  string hddCommand2 = "df -h >> ";
  string cpuCommand1 = "top -bn1 | grep 'Cpu(s)' >> ";
  string cpuCommand2 = "lscpu >> ";
  string loadAverageCommand1 = "cat /proc/loadavg >> ";
  string memoryCommand1 = "free >> ";
  string networkCommand1 = "vnstat -i wlp4s0 >> ";
  string networkCommand2 = "vnstat -i eno1 >> ";

  //Note: Closing the files is very important to prevent lines from being outputted incorrectly
  logFile << "HDD SECTION: \n";
  logFile << "Legend: nvmeXnYpZ means that this is a NVMe SSD. X is the controller number, Y is the SSD number, and Z is the partition number\n";
  logFile << "sdXY means sata device number X and partition number Y\n";
  logFile << "ALL DEVICES LISTED BELOW: \n";
  logFile.close();
  system((hddCommand1 + pathName).c_str());
  system((hddCommand2 + pathName).c_str());
  
  logFile.open(pathName, ios::app);
  logFile << "\n\nCPU UTILIZATION SECTION: \n";
  logFile << "LEGEND: \n";
  logFile << "us: Percentage of time spent on user processes\n";
  logFile << "sy: Percentage of time spent on kernel processes\n";
  logFile << "ni: Percentage of time spent on processes with custom nice value\n";
  logFile << "id: Percentage of time spent idiling\n";
  logFile << "hi: Percentage of time spent handling hardware interrupts\n";
  logFile << "si: Percentage of time spent handling software gnerated interrupts\n";
  logFile << "st: Percentage of time taken by hypervisor (only applies inside a virtual machine)\n";
  logFile << "NOTE: These percentages are taken over a 3 second time interval\n";
  logFile.close();
  system((cpuCommand1 + pathName).c_str());

  logFile.open(pathName, ios::app);
  logFile << "\n\nMEMORY SECTION: \n";
  logFile.close();
  system((memoryCommand1 + pathName).c_str());
    
  logFile.open(pathName, ios::app);
  logFile << "\n\nLOAD AVERAGE SECTION: \n";
  logFile << "LEGEND: The first number is the load average measured over 1 minute. The second number is the load average measured over 5 minutes, and the third number is the load average over 15 minutes. The fourth number is the ratio of running processes over all processes. The fifth number is the PID of most recently created process\n";
  logFile.close();
  system((loadAverageCommand1 + pathName).c_str());

  logFile.open(pathName, ios::app);
  logFile << "\n\nNETWORKING SECTION:\n";
  logFile << "LEGEND: wlp4s0 is the first wireless internet interface connected to the computer. eno1 is the first wired internet interface connected to the computer.Also, rx stands for recieved while tx stands for transmitted.\n";
  logFile.close();
  system((networkCommand1 + pathName).c_str());
  system((networkCommand2 + pathName).c_str());
  logFile.open(pathName, ios::app);
  logFile << "\n\n";
  logFile.close();
  return  "/var/log/SLHD/" + fileName;
}

void SendEmail(const string& inputFileName, const string& senderEmail, const string& serverURL,const string& senderPassword, const string& receiverEmail)
{
  CURL* curlObject;
  CURLcode result = CURLE_OK;
  curl_global_init(CURL_GLOBAL_ALL);
  curlObject = curl_easy_init();
  if(curlObject)
  {
    curl_easy_setopt(curlObject, CURLOPT_URL, serverURL.c_str());
    curl_easy_setopt(curlObject, CURLOPT_USERNAME, senderEmail.c_str());
    curl_easy_setopt(curlObject, CURLOPT_PASSWORD, senderPassword.c_str());
    curl_easy_setopt(curlObject, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

    //Make a recepients List so that the email actually goes somewhere
    curl_slist* recepientsList = nullptr;
    recepientsList = curl_slist_append(recepientsList, receiverEmail.c_str());
    curl_easy_setopt(curlObject, CURLOPT_MAIL_RCPT, recepientsList);

    curl_mime* mimeObject;
    curl_mimepart* mimePart;
    // Initialize MIME...which will allow us to customize the email
    mimeObject = curl_mime_init(curlObject);

    // Add the body of the email
    mimePart = curl_mime_addpart(mimeObject);
    string emailBody = "Hello, this is the log file for " + getCurrentDate() + ". Please read it carefully.";
    curl_mime_data(mimePart, emailBody.c_str(), CURL_ZERO_TERMINATED);
    curl_mime_type(mimePart, "text/plain");

    // Add the attachment
    mimePart = curl_mime_addpart(mimeObject);
    curl_mime_filedata(mimePart, inputFileName.c_str());
    curl_mime_type(mimePart, "text/plain");
    curl_mime_encoder(mimePart, "base64"); // Encoding the attachment in base64
    curl_mime_filename(mimePart, "HardwareLogFile.txt");

    // Set the MIME object as the mail body
    curl_easy_setopt(curlObject, CURLOPT_MIMEPOST, mimeObject);
    
    // Perform sending the email
    result = curl_easy_perform(curlObject);
    if(result == CURLE_OK)
      cout << "Email successfully sent.\n";
    else
      cerr << "Failed to send email. Reason: " << curl_easy_strerror(result) << "\n";
    
    curl_slist_free_all(recepientsList);
    curl_mime_free(mimeObject);
    curl_easy_cleanup(curlObject);
    curl_global_cleanup();
    
  }
  else
  {
    cerr << "Failed to initailize curl!";
  }
}


int readPreviousOutputFile(string fileName, const int& defaultTime)
{
  ifstream inputFile(fileName);
  if(!inputFile.is_open())
  {
    cerr << "Failed to open previous time file\n";
    return defaultTime;
  }
  int toReturn;
  inputFile >> toReturn;
  cout << "Previous Time Remaining: " << toReturn << "\n";
  return toReturn;
}




