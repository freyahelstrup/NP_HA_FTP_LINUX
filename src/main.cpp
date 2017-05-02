/*
main.cpp
*/
#include <iostream>
#include <fstream>
#include "FTPClient.cpp"

using namespace std;

int main() {
    char ip[] = "192.168.43.11";
    char *ip_pointer = ip; //Casting ip-address to a char-pointer
    FTPClient c, data;
    int dataPort, a1, a2, a3, a4, p1, p2;

    //Establishing connection
    c.Connect(21, ip_pointer);
    c.RecvMsg();
    c.SendMsg("HELLO\r\n", 7);
    c.RecvMsg();

    //Logging in
    c.SendMsg("USER anonymous\r\n", 16);
    c.RecvMsg();
    c.SendMsg("PASS s165232@dtu.dk\r\n", 21);
    c.RecvMsg();

    //Entering Passive Mode
    c.SendMsg("PASV\r\n", 6);
    sscanf(c.RecvMsg(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
    dataPort = (p1 * 256) + p2;

    //Opening data connection to retrieve log.csv
    data.Connect(dataPort, ip_pointer);
    c.SendMsg("RETR log.csv\r\n", 14);
    c.RecvMsg();
    c.RecvMsg();
    data.SaveFile("log.csv");
    data.CloseCon();

    //Open log.csv
    ifstream log;
    log.open("../log.csv", ios::in);

    //Find sensor 4 max value
    int maxvalue = 0;

    if (log.is_open()) {
        string line;
        getline(log, line);
        while (getline(log, line)) {
            string sensor4;

            //Remove first 4 columns
            int i = 0;
            while (i < 4) {
                line = line.substr(line.find(",") + 1, line.size());
                i++;
            }

            //Extract data from 5th column
            sensor4 = line.substr(0, line.find(","));

            //Set max value
            if (maxvalue < atoi(sensor4.c_str())) {
                maxvalue = atoi(sensor4.c_str());
            }
        }

        //Save max value in file sensor4.txt
        ofstream maxvalue_file;
        maxvalue_file.open("/var/www/sensor4.txt");
        maxvalue_file << maxvalue;

        //Close files
        maxvalue_file.close();
        log.close();

    } else {
        printf("ERROR: File has not been opened.");
    }

    cin.get();
    c.CloseCon();
    return 0;
}
