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


void sendMsg(string username){
    char buffer[100]{"\n"};

        cout<<"\n[ "<<username<<" ] Enter two integers: ";
        cin>>buffer;
        int n=mkfifo("pipe",0666);
        int wr_open = open("pipe",O_WRONLY);

        write(wr_open,buffer,100);
        buffer[0]='\0';
        close(wr_open);
}

void recieveMsg(){
    char buffer[100];
    int rd_open= open("pipe",O_RDONLY);

    read(rd_open,buffer,100);

    cout<<"\n"<<buffer;

    close(rd_open);
}


int main(){


    while (1)
    {   
        recieveMsg();
        sendMsg("User1");
        
    }
    


    return 0;
}