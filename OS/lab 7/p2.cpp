#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string>
#include <cstring>
#include <fcntl.h>

using namespace std;


void sendMsg(int b){
    
        string buffer=to_string(b);
        
        int n=mkfifo("pipe1",0666);
        int wr_open = open("pipe1",O_WRONLY);

        write(wr_open,buffer.c_str(),100);
        
        close(wr_open);
}

int recieveMsg(){
    char buffer[100];
    int rd_open= open("pipe1",O_RDONLY);

    read(rd_open,buffer,100);

    cout<<"\n"<<buffer;
    int num=stoi(buffer);
    close(rd_open);
    return num;
}

int hcf(int num1,int num2){
    int hcf=1;
    for(int i = 1; i <= num1 || i <= num2; i++)
    {
        if(num1 % i == 0 && num2 % i == 0)
            hcf = i;
    }

    cout<<"\n\nHCF CALCULATED! \n Sending hcf...........\n";
    return hcf;
}

int main(){


    int n1 = recieveMsg();
    int n2 = recieveMsg();
    
    sendMsg(hcf(n1,n2));

    return 0;
}