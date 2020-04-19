//Msp test
#include<string>
#include <stdio.h>
#include <windows.h> 
#include <bits/stdc++.h> 
using namespace std; 

using namespace std; 
  
// utility function 
void strToBinary(string s) 
{ 
    int n = s.length(); 
    for (int i = 0; i <= n; i++) 
    { 
        // convert each char to 
        // ASCII value 
        int val = int(s[i]); 
  
        // Convert ASCII value to binary 
        string bin = ""; 
        while (val > 0) 
        { 
            (val % 2)? bin.push_back('1') : 
                       bin.push_back('0'); 
            val /= 2; 
        } 
        reverse(bin.begin(), bin.end()); 
  
        cout << bin << " "; 
    } 
}
void strToBinary2(string s) 
{ 
    int n = s.length(); 
    
    for (int i = 0; i <5; i++) 
    { 
        // convert each char to 
        // ASCII value 
        int val = int(s[i]);
        cout<<" Int "<<val<<" ";
        // Convert ASCII value to binary 
        string bin = ""; 
        while (val > 0) 
        { 
            (val % 2)? bin.push_back('1') : 
                       bin.push_back('0'); 
            val /= 2; 
        } 
        reverse(bin.begin(), bin.end()); 
        
        cout<<"Bin "<<bin <<" "; 
        
    }
    cout<<"\n" ;
}  

int main(){
    HANDLE hComm;
    hComm =CreateFile("\\\\.\\COM13",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    if(hComm ==INVALID_HANDLE_VALUE){
        printf("Error in opening port");

    }
    else{
        printf("opened");
    }
    DCB dcbSerialParams={0};
    dcbSerialParams.DCBlength =sizeof(dcbSerialParams);

    int Status=GetCommState(hComm,&dcbSerialParams);

    printf("\n %d",Status);
    printf("\n Baud Rate %ld ",dcbSerialParams.BaudRate);
    printf("\n Byte Size %ld",dcbSerialParams.ByteSize);
    printf("\n Stop Bits %ld",dcbSerialParams.StopBits);
    printf("\n Parity %ld",dcbSerialParams.Parity);

    dcbSerialParams.BaudRate = CBR_115200;  // Setting BaudRate = 9600 DWord 
    dcbSerialParams.ByteSize = 8;         // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;// Setting StopBits = 1      Byte
    dcbSerialParams.Parity   = NOPARITY;  // Setting Parity = None     Byte
    SetCommState(hComm, &dcbSerialParams);
    printf("\n Baud Rate %ld ",dcbSerialParams.BaudRate);
    printf("\n Byte Size %ld",dcbSerialParams.ByteSize);
    printf("\n Stop Bits %ld",dcbSerialParams.StopBits);
    printf("\n Parity %ld",dcbSerialParams.Parity);

    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout         = 100; // in milliseconds
    timeouts.ReadTotalTimeoutConstant    = 100; // in milliseconds
    timeouts.ReadTotalTimeoutMultiplier  = 100; // in milliseconds
    timeouts.WriteTotalTimeoutConstant   = 100; // in milliseconds
    timeouts.WriteTotalTimeoutMultiplier = 100; // in milliseconds
    SetCommTimeouts(hComm,&timeouts);

    char lpBuffer[6];
    lpBuffer[0]='$';
    lpBuffer[1]='M';
    lpBuffer[2]='<';
    lpBuffer[3]=0;
    lpBuffer[4]=108;
    lpBuffer[5]=(0^108);

    DWORD dNoOFBytestoWrite;         // No of bytes to write into the port
    DWORD dNoOfBytesWritten = 0;     // No of bytes written to the port
    dNoOFBytestoWrite = sizeof(lpBuffer);
    while(true){
    int Status2 = WriteFile(hComm,        // Handle to the Serial port
                        lpBuffer,     // Data to be written to the port
                        dNoOFBytestoWrite,  //No of bytes to write
                        &dNoOfBytesWritten, //Bytes written
                        NULL);
    
    //printf("\n %d",Status2);
    int Status3= SetCommMask(hComm,EV_RXCHAR); 
    //printf("\n %d",Status3);
   
    DWORD dwEventMask; 
    int Status4 = WaitCommEvent(hComm, &dwEventMask, NULL);  // It Gets Stuck here !!!
    //printf("\n %d\n",Status4);

        char TempChar; //Temporary character used for reading
        char SerialBuffer[256];//Buffer for storing Rxed Data
        //char SerialBuffer2[2];
        short int x;
        short int *y=&x;
        char SerialBuffer3[256];
        char SerialBuffer4[256];
        char SerialBuffer5[256];
        char SerialBuffer6[256];
        char SerialBuffer7[256];
        
        int i = 0;


        //ClearCommError(hComm,NULL,NULL);
        int status5=ReadFile(hComm,SerialBuffer,5,&NoBytesRead,NULL);
        
        
        printf("\n%s\nNo of Bytes Read %d\n",SerialBuffer,NoBytesRead);
        strToBinary(SerialBuffer);
        //////////////////////////////////////
        status5=ReadFile(hComm,y,(sizeof(x)),&NoBytesRead,NULL);
        printf("\n%ld\nNo of Bytes Read %d\n",x,NoBytesRead);
        //strToBinary2(SerialBuffer2);
        ///////////////////////////////////
        /*
        status5=ReadFile(hComm,SerialBuffer3,1,&NoBytesRead,NULL);
        printf("\n%s\nNo of Bytes Read %d\n",SerialBuffer3,NoBytesRead);
        strToBinary2(SerialBuffer3);
        */ 
        //////////////////////////////////
        status5=ReadFile(hComm,SerialBuffer4,1,&NoBytesRead,NULL);
        printf("\n%s\nNo of Bytes Read %d\n",SerialBuffer4,NoBytesRead);
        strToBinary2(SerialBuffer4);
        ///////////////////////////////////
        status5=ReadFile(hComm,SerialBuffer5,1,&NoBytesRead,NULL);
        printf("\n%s\nNo of Bytes Read %d\n",SerialBuffer5,NoBytesRead);
        strToBinary2(SerialBuffer5);
        ///////////////////////////////////
        status5=ReadFile(hComm,SerialBuffer6,1,&NoBytesRead,NULL);
        printf("\n%s\nNo of Bytes Read %d\n",SerialBuffer6,NoBytesRead);
        strToBinary2(SerialBuffer6);
        //////////////////////////////////////////
        status5=ReadFile(hComm,SerialBuffer7,1,&NoBytesRead,NULL);
        printf("\n%s\nNo of Bytes Read %d\n",SerialBuffer7,NoBytesRead);
        strToBinary2(SerialBuffer7);
        //////////////////////////////////////////
        PurgeComm(hComm,PURGE_RXCLEAR);
        PurgeComm(hComm,PURGE_TXCLEAR);
        Sleep(10000);
    }
    CloseHandle(hComm);//Closing the Serial Port
    return 0;
}

