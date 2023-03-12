#include <iostream>
#include <stdio.h>
// #include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <cstring>


using namespace std;

char* read_data (key_t key ){
  
    // shmget returns an identifier in shmid

    int shmid = shmget(key,1024,0666|IPC_CREAT);
  
    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);
  
    printf("Previous Messages:\n%s\n",str);
      
    //detach from shared memory 
    // shmdt(str);
    return str;
}
void write_data(key_t key,int processNum){

    int shmid = shmget(key,1024,0666|IPC_CREAT);
    
    char *shared_memory = (char*) shmat(shmid,(void*)0,0);
    string message;
    cout<<"[User "<< processNum <<"] Write message : ";
    getline(cin,message);
    message+=" [ sender: user "+to_string(processNum)+" ]\n";
    int message_size = message.length();
    int memory_size = strlen(shared_memory);
    memcpy(shared_memory+memory_size, message.c_str(), message_size);

    // printf("Data written in memory: %s\n",shared_memory);
      
    //detach from shared memory 
    shmdt(shared_memory);
    //   shmctl(shmid,IPC_RMID,NULL);
}


int main() {

    int id;

    key_t key = ftok("shmfile",65);
  
    read_data(key);

    for (int i = 0; i < 4 ;i++)
    {
        int pid=fork();
        if(pid==0){
            write_data(key,i+1);
            exit(0);
        }
        else{
        wait(nullptr);

        }
        
    }
    
        // wait(nullptr);

    return 0;
}

/* Problem:
When multiple processes access shared memory concurrently, synchronization issues can arise. 
These issues can include race conditions, where the order of execution of processes affects the result, and data inconsistency,
where different processes may see different versions of the shared data.
In the chat program, if two or more users write to shared memory simultaneously, the messages may not be stored in the correct order or may overwrite each other, 
resulting in lost data or garbled messages. 
Additionally, if one process modifies the shared memory while another is reading from it, the reader may see inconsistent or outdated data.

To resolve these issues, synchronization mechanisms such as semaphores, locks, or monitors can be used to coordinate access to shared memory between processes. 
For example, a semaphore could be used to ensure that only one process writes to the shared memory at a time, 
or a lock could be used to prevent simultaneous access to the shared memory. 
In addition, atomic operations or transactional memory can be used to ensure that read and write operations on the shared memory are performed atomically,
without interference from other processes. Careful design and implementation of synchronization mechanisms can ensure that the shared memory is accessed correctly 
and consistently by multiple processes. */