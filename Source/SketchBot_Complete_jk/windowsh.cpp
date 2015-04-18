#include <windows.h>
#include <iostream>

using namespace std;

HANDLE hPort = CreateFile("COM1", GENERIC_WRITE|GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

DCB dcb={0};
//dcbSerial.DCBlength=sizeof(dcb);

//to write a byte to serial port
bool writebyte (char* data)
{
    DWORD byteswritten;
    if (!GetCommState(hPort, &dcb))
    {
        cout<<"Serial port can't be opened. Please see if XBee module is properly connected (On COM1).";
        exit(0);
        return false;
    }


    dcb.BaudRate = CBR_9600;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;

    if (!SetCommState(hPort, &dcb))
    return false;

    bool retVal = WriteFile(hPort, data, 1, &byteswritten, NULL);
    return retVal;
}

//to read a byte from serial port
int readByte()
{
    int Val;
    BYTE byte;
    DWORD dwBytesTransferred;
    DWORD dwCommModemStatus;
    if(!GetCommState(hPort, &dcb))
        return 0;

    SetCommMask(hPort, EV_RXCHAR|EV_ERR);
    WaitCommEvent(hPort, &dwCommModemStatus, 0);
    if (dwCommModemStatus& EV_RXCHAR)
        ReadFile(hPort, &byte, 1, &dwBytesTransferred, 0);
    Val = byte;
    return Val;
}

//to write and then read the response
void sendAndRecieve(char &data)
{
    writebyte(&data);
    //cout<<"Data sent "<<int(data)<<"   ";
    char readData=readByte();
    //cout<<int(readData)<<endl;
}
