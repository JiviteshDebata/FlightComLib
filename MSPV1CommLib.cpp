
#include <stdio.h>
#include <windows.h> 

class MSPV1_DEVICE{

    public:
    //TODO
    //Create header reading file that reads and validates header and msp version
    //Create a structure per frame type
    //struct ATTITUDE{

    //}

    //TODO Create a checksum calculator for MSPV1 and MSPV2
    HANDLE device;
    int WriteStatus;
    int ReadStatus;
    MSPV1_DEVICE(char port[],int baudRate){
        
        device =CreateFile(port,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
        if(device ==INVALID_HANDLE_VALUE){
            printf("Error in opening port");
            //TODO Print what error has occured
            exit(0);
        }
        else{
        printf("Port opened on ->%s",port);
        }
        DCB dcbSerialParams={0};
        dcbSerialParams.DCBlength =sizeof(dcbSerialParams);
        switch(baudRate){
            case 9600   :   dcbSerialParams.BaudRate=CBR_9600;
                            break;
            case 14400  :   dcbSerialParams.BaudRate=CBR_14400;
                            break;
            case 19200  :   dcbSerialParams.BaudRate=CBR_19200;
                            break;
            case 38400  :   dcbSerialParams.BaudRate=CBR_38400;
                            break;
            case 57600  :   dcbSerialParams.BaudRate=CBR_57600;
                            break;
            case 115200 :   dcbSerialParams.BaudRate=CBR_115200;
                            break;
            default     :   printf("Invalid BaudRate selected. Choose either 9600,14400,19200,38400,57600,115200");
                            exit(0);
                            break;
        }
        dcbSerialParams.ByteSize = 8;         
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity   = NOPARITY;  
        SetCommState(device, &dcbSerialParams);
        printf("\nPort Parameters are set to->");
        printf("\n Baud Rate %ld ",dcbSerialParams.BaudRate);
        printf("\n Byte Size %ld",dcbSerialParams.ByteSize);
        printf("\n Stop Bits %ld",dcbSerialParams.StopBits);
        printf("\n Parity %ld",dcbSerialParams.Parity);
        
        COMMTIMEOUTS timeouts = { 0 };
        //TODO Check if speed can be increased 
        timeouts.ReadIntervalTimeout         = 100; // in milliseconds
        timeouts.ReadTotalTimeoutConstant    = 100; // in milliseconds
        timeouts.ReadTotalTimeoutMultiplier  = 100; // in milliseconds
        timeouts.WriteTotalTimeoutConstant   = 100; // in milliseconds
        timeouts.WriteTotalTimeoutMultiplier = 100; // in milliseconds
        SetCommTimeouts(device,&timeouts);
    }
    void pollDevice(char cmd){
            char data[6];
            data[0]='$';
            data[1]='M';
            data[2]='<';
            data[3]=0;
            switch(cmd){
                case 102:{data[4]=102;
                        data[5]=(0^102);
                        DWORD dNoOFBytestoWrite;         
                        DWORD dNoOfBytesWritten = 0;     
                        dNoOFBytestoWrite = sizeof(data);
                        WriteStatus = WriteFile(device,        
                                                data,     
                                                dNoOFBytestoWrite,          
                                                &dNoOfBytesWritten, 
                                                NULL);
                        ReadStatus = SetCommMask(device,EV_RXCHAR);
                        DWORD dwEventMask;
                        ReadStatus = WaitCommEvent(device, &dwEventMask, NULL);
                        char Header[3];
                        short int   accx,
                                    accy,
                                    accz,
                                    gyrx,
                                    gyry,
                                    gyrz,
                                    magx,
                                    magy,
                                    magz;
                        char CRC;
                        DWORD  NoBytesRead;
                        ReadStatus=ReadFile(device,Header,5,&NoBytesRead,NULL);
                        ReadStatus=ReadFile(device,&accx,sizeof(accx),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(device,&accy,sizeof(accy),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(device,&accz,sizeof(accz),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(device,&gyrx,sizeof(gyrx),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(device,&gyry,sizeof(gyry),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(device,&gyrz,sizeof(gyrz),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(device,&magx,sizeof(magx),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(device,&magy,sizeof(magy),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(device,&magz,sizeof(magz),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(device,&CRC,sizeof(CRC),&NoBytesRead,NULL);
                        printf(" ACC x : %d ACC y : %d ACC Z :%d GYR x : %d GYR y : %d GYR z: %d MAG x : %d MAG y : %d MAG z : %d\n",accx,accy,accz,gyrx,gyry,gyrz,magx,magy,magz);
                        PurgeComm(device,PURGE_RXCLEAR);
                        PurgeComm(device,PURGE_TXCLEAR);
                }break;
                case 108:{
                        data[4]=108;
                        data[5]=(0^108);
                        DWORD dNoOFBytestoWrite;         
                        DWORD dNoOfBytesWritten = 0;     
                        dNoOFBytestoWrite = sizeof(data);
                        WriteStatus = WriteFile(device,        
                                                data,     
                                                dNoOFBytestoWrite,          
                                                &dNoOfBytesWritten, 
                                                NULL);
                        ReadStatus = SetCommMask(device,EV_RXCHAR);
                        DWORD dwEventMask;
                        ReadStatus = WaitCommEvent(device, &dwEventMask, NULL);
                        char Header[5];
                        short int angx;
                        short int angy;
                        short int heading;
                        char CRC;
                        DWORD NoBytesRead;
                        ReadStatus=ReadFile(device,Header,5,&NoBytesRead,NULL);
                        //printf("\n%s\nNo of Bytes Read %d\n",Header,NoBytesRead);
                        //strToBinary(SerialBuffer);
                        ReadStatus=ReadFile(device,&angx,sizeof(angx),&NoBytesRead,NULL);
                        //angx=angx/10; //1/10th Degree
                        //printf("\n%ld\nNo of Bytes Read %d\n",angx,NoBytesRead);
                        
                        ReadStatus=ReadFile(device,&angy,(sizeof(angy)),&NoBytesRead,NULL);
                        //angy=1/10; //1/10th Degree
                        //printf("\n%ld\nNo of Bytes Read %d\n",angy,NoBytesRead);
                    
                        ReadStatus=ReadFile(device,&heading,(sizeof(heading)),&NoBytesRead,NULL);
                        //printf("\n%ld\nNo of Bytes Read %d\n",heading,NoBytesRead);
                        
                        ReadStatus=ReadFile(device,&CRC,(sizeof(CRC)),&NoBytesRead,NULL);
                        //printf("\n%ld\nNo of Bytes Read %d\n",CRC,NoBytesRead);
                        
                        printf(" Ang x : %d Ang y : %d Heading :%d \n",angx,angy,heading);
                        
                        PurgeComm(device,PURGE_RXCLEAR);
                        PurgeComm(device,PURGE_TXCLEAR);
                        //Sleep(1000);
                }break;
                case 106:{
                        data[4]=106;
                        data[5]=(0^106);
                        DWORD dNoOFBytestoWrite;         
                        DWORD dNoOfBytesWritten = 0;     
                        dNoOFBytestoWrite = sizeof(data);
                        WriteStatus = WriteFile(device,        
                                                data,     
                                                dNoOFBytestoWrite,          
                                                &dNoOfBytesWritten, 
                                                NULL);
                        ReadStatus = SetCommMask(device,EV_RXCHAR);
                        DWORD dwEventMask;
                        ReadStatus = WaitCommEvent(device, &dwEventMask, NULL);
                        char Header[5];
                        unsigned char fix, numSat;
                        unsigned int lat, lon;
                        unsigned short int altitude, speed, groundCourse;
                        char CRC;
                        double latitude, longitude;

                        DWORD NoBytesRead;
                        ReadStatus=ReadFile(device,Header,5,&NoBytesRead,NULL);
                        //printf("\n%s\nNo of Bytes Read %d\n",Header,NoBytesRead);
                        //strToBinary(SerialBuffer);
                        ReadStatus=ReadFile(*device,&fix,sizeof(fix),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(*device,&numSat,(sizeof(numSat)),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(*device,&lat,(sizeof(lat)),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(*device,&lon,(sizeof(lon)),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(*device,&altitude,(sizeof(altitude)),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(*device,&speed,(sizeof(speed)),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(*device,&groundCourse,(sizeof(groundCourse)),&NoBytesRead,NULL);
                        ReadStatus=ReadFile(*device,&CRC,(sizeof(CRC)),&NoBytesRead,NULL);

                        latitude = (double)lat / 10000000.0;
                        longitude = (double)lon / 10000000.0;
                        
                        printf("fix: %d, numSat: %d, lat: %lf, lon: %lf, altitude: %d, speed: %d, groundCourse: %d",fix,numSat,latitude,longitude,altitude,speed,groundCourse);

                        PurgeComm(*device,PURGE_RXCLEAR);
                        PurgeComm(*device,PURGE_TXCLEAR);
                        //Sleep(1000);
                }break;
            }
    }
};
//Test function
int main(int argc,char *argv[]){
    char port[10]="\\\\.\\";
    for(int i=0;argv[1][i]!='\0';i++)
    {
        port[4+i]=argv[1][i];
    }
    MSPV1_DEVICE trial(port,115200);
    int input =atoi(argv[2]);
    printf("%d",input);
    while(true)
    trial.pollDevice(input);
    return 1;
}