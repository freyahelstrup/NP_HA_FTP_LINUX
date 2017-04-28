/*
main.cpp
*/
#include <iostream>
#include "FTPClient.cpp"

using namespace std;

int main() {
//	char ip[] = "130.226.195.126";
    char ip[] = "192.168.43.11";
    char *ip_pointer = ip; //Casting ip-address to a char-pointer
	FTPClient c, data;
	int dataPort,a1,a2,a3,a4,p1,p2;

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
/*
	//Entering Passive Mode
    c.SendMsg("PASV\r\n", 6);
	sscanf(c.RecvMsg(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
	dataPort = (p1 * 256) + p2;

    //Opening new data connection to attempt to STOR file in server root dir.
	data.Connect(dataPort, ip_pointer);
	c.SendMsg("LIST\r\n", 6);
	c.RecvMsg();

	data.RecvMsg();
	c.RecvMsg();
	
	c.SendMsg("STOR CMakeLists.txt\r\n", 21);
	c.RecvMsg();
	data.CloseCon();


	//Entering Passive Mode again
	c.SendMsg("PASV\r\n", 6);
	sscanf(c.RecvMsg(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
	dataPort = (p1 * 256) + p2;

	//Opening data connection to RETR 1st file
	data.Connect(dataPort, ip_pointer);
	c.SendMsg("RETR hejtroels.txt\r\n", 15); //small file of 12 bytes
	c.RecvMsg();
	c.RecvMsg();
	data.SaveFile("hejtroels.txt");
	data.CloseCon();

	//Entering Passive Mode again
	c.SendMsg("PASV\r\n", 6);
	sscanf(c.RecvMsg(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
	dataPort = (p1 * 256) + p2;

	//Opening new data connection to CWD and LIST
	data.Connect(dataPort, ip_pointer);
	c.SendMsg("CWD /pub/62501/HOWTOs/NAT-HOWTO\r\n", 33);
	c.RecvMsg();
	
	c.SendMsg("LIST\r\n", 6);
	c.RecvMsg();
	data.RecvMsg();
	c.RecvMsg();
	data.CloseCon();
	*/
	//Entering Passive Mode again
	c.SendMsg("PASV\r\n", 6);
	sscanf(c.RecvMsg(), "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n", &a1, &a2, &a3, &a4, &p1, &p2);
	dataPort = (p1 * 256) + p2;

	//Opening data connection to RETR file
	data.Connect(dataPort, ip_pointer);
	c.SendMsg("RETR log.csv\r\n", 14); //small file of 12 bytes
	c.RecvMsg();
	c.RecvMsg();
	data.SaveFile("log.csv");
	data.CloseCon();

	//log.csv open
	ifstream log;
	string line;
	int sensor4max;
	log.open("../log.csv", ios::in);

    if (log.is_open()) {
        getline(log, line);
        while (getline(log, line)) {
            string sensor1, sensor2, sensor3, sensor4, sensor5, sensor6;

            line = line.substr(line.find(",") + 1, line.size());
            sensor1 = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1, line.size());
            sensor2 = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1, line.size());
            sensor3 = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1, line.size());
            sensor4 = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1, line.size());
            sensor5 = line.substr(0, line.find(","));
            line = line.substr(line.find(",") + 1, line.size());
            sensor6 = line.substr(0, line.find(","));

            if (sensor4max < atoi(sensor4.c_str())) {
                sensor4max = atoi(sensor4.c_str());
            }
        }

        cout << sensor4max;

    } else {
        printf("ERROR: File has not been opened.");
    }

	cin.get();
	c.CloseCon();
	return 0;
}
