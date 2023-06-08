#include <iostream>
#include <sys/wait.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <atomic>
#include <fcntl.h>
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <string>
#include <cmath>

#define p 8
#define r 8
#define c 8
#define neu 8

using namespace std;

struct Payload
{
    atomic<int> numOfNeurons = neu;
    atomic<int> pages = p, rows = r, cols = c, currentLayer = 0, currentNeuron = 0;
    double weights[p][r][c]{};
    double answer[p][neu]{};
    double error[p][neu]{};
};

double matrix[8][8]={0};

void printMatrix(){
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout<<matrix[i][j];
        }
            cout<<endl;
        
    }
    
}
void filereading(int currentLayer,Payload &data) 
{

    ifstream infile("config.txt");
    
    if (!infile.is_open()) 
    {
        cout << "Error: Unable to open file" << endl;
        return;
    }

    string line;
    // Skip the first line
	
   
    getline(infile, line);

    for ( int i=0 ;i<8;i++)
    {
        for (int j=0;j< 8;j++)
        {
            matrix[i][j] = 0;
        }
    }

    
    bool check_reading = false;	
	
    if(currentLayer==0 ){

        for (int i = 0;  !check_reading ; i++)
        {   
            for ( int j=0;line[j] !='\0';j++)
            {
                if (line[j] ==  'I' && line[j+4] == 't')
                {
                    check_reading = true;
                    break;
                }
            
            }   
        getline(infile, line);
        }


    }
     else if(currentLayer==p-1)
    {
        for (int i = 0;  !check_reading ; i++)
        {   
            for ( int j=0;line[j] !='\0';j++)
            {
                if (line[j] ==  'I' && line[j+6] == 'd')
                {
                    check_reading = true;
                    break;
                }
            
            }   
            getline(infile, line);
        }  
    }
    else if(currentLayer==p-2)
    {
        for (int i = 0;  !check_reading ; i++)
        {   
            for ( int j=0;line[j] !='\0';j++)
            {
                if (line[j] ==  'O' && line[j+5] == 't')
                {
                    check_reading = true;
                    break;
                }
            
            }   
            getline(infile, line);
        }  
    }
    else if(currentLayer<p-2)
    {
        for (int i = 0;  !check_reading ; i++)
        {   
            for ( int j=0;line[j] !='\0';j++)
            {
                if (line[j] ==  currentLayer+48 && line[j+2] == 'w')
                {
                    check_reading = true;
                    break;
                }
            
            }   
            getline(infile, line);
        }  
    }
    
    // Skip the lines for previous layers
    
// Read the weights for the current layer
    int row=r;
    if(currentLayer==0){
        row=2;
    }
    if(currentLayer==p-1){
        row=1;
    }
    
    for (int i = 0; i < row; i++)
    {
        int j = 0;
        string value_str = "";
        for (int k = 0; k < line.length(); k++) 
        {
            char cy = line[k];
            if (cy == ',') 
            {
                
                {
                    matrix[i][j++] = stod(value_str);
                } 
                
                value_str = "";
            }
            else 
            {
                value_str += cy;
            }
        }
        
        
            {
                matrix[i][j] = stod(value_str);
            }
        getline(infile, line);
        }

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                data.weights[currentLayer][i][j]=matrix[i][j];
            }
            
        }
        

    infile.close();
}

void fillWights(Payload &load){

    
    for (int i = 0; i < load.pages; i++)
    {
        for (int j = 0; j < load.rows; j++)
        {
            for (int k = 0; k < load.cols; k++)
            {
                load.weights[i][j][k] = 0.1;
            }
        }
    }

    
}

void printWeights(Payload &load){

    
    for (int i = 0; i < load.pages; i++)
    {
        for (int j = 0; j < load.rows; j++)
        {
            for (int k = 0; k < load.cols; k++)
            {
                cout<<load.weights[i][j][k] << ' ';
            }
                cout<<endl;

        }

                cout<<endl;
                cout<<endl;

    }

    
}

void printAnswers(Payload &load){

    cout<<endl;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < load.numOfNeurons; j++)
        {
            
                cout<<load.answer[i][j] << ' ';

          


        }    
                cout<<endl;
    }
}

void printErrors(Payload &load){

    cout<<endl;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < load.numOfNeurons; j++)
        {
            
                cout<<load.error[i][j] << ' ';

          


        }    
                cout<<endl;
    }
}


void* neurons(void* arg)
{

    Payload *a = (Payload *)arg;
    int layer =a->currentLayer;
    int nextlayer =a->currentLayer+1;

    int neuron =a->currentNeuron;
   
   if (nextlayer<p)
   {
        for (int i = 0; i < a->numOfNeurons; i++)
        {   
            for (int j = 0; j < a->numOfNeurons; j++)
            {
                a->answer[layer][i]+= a->weights[layer][i][j]*a->weights[nextlayer][j][i];
            }
        }
   }
   
   
    

    a->currentNeuron++;
    cout<<" [Layer "<<layer<<"]"<<"[neuron "<<neuron<<"] ";
    
    return NULL;
}

void* reverseNeurons(void* arg)
{
Payload* a = (Payload*)arg;
    int layer = a->currentLayer;
    int prevLayer = layer - 1;
    int neuron = a->currentNeuron;

    if (layer == a->pages - 1)
    {
        for (int i = 0; i < a->numOfNeurons; i++)
        {
            a->error[layer][i] = a->answer[layer][i] * (1 - a->answer[layer][i]) * (a->answer[layer][i] - 0.5);
        }
    }
    else
    {
        for (int i = 0; i < a->numOfNeurons; i++)
        {
            double sum = 0;
            for (int j = 0; j < a->numOfNeurons; j++)
            {
                sum += a->weights[layer][i][j] * a->error[layer + 1][j];
            }
            a->error[layer][i] = a->answer[layer][i] * (1 - a->answer[layer][i]) * sum;
        }
    }

    if (prevLayer >= 0)
    {
        for (int i = 0; i < a->numOfNeurons;i++)
        {
            double sum = 0;
            for (int j = 0; j < a->numOfNeurons; j++)
            {
            sum += a->weights[prevLayer][j][i] * a->answer[prevLayer][j];
            }
        a->answer[layer][i] = 1 / (1 + exp(-sum));
        }
    }
    return NULL;
}

int main()
{
    Payload data;
    sem_t semaphore;
    sem_t threadSemap;
    sem_init(&semaphore, 0, 1); // create a binary semaphore with initial value 1
    sem_init(&threadSemap, 0, 8); // create a counting semaphore with initial value 8

    pid_t pid;
    int fd[2];
    int fd1[2];

    if (pipe(fd) == -1) {
        perror("pipe(fd) failed");
        return 1;
    }

    if (pipe(fd1) == -1) {
        perror("pipe(fd1) failed");
        return 1;
    }

    // data.setAll(7, 8, 8, 8);
    // fillWights(data);
    for (int i = 0; i < 8; i++)
    {/* code */
        filereading(i,data);
    }
    
    // printWeights(data);

    write(fd[1], &data, sizeof(data));

    for (int i = 0; i < 7; i++) {
        sem_wait(&semaphore); // decrement the binary semaphore value
        pid_t pid = fork();

        if (pid == 0) {
            read(fd[0], &data, sizeof(data));
            data.currentNeuron = 0;
            cout << "\nCHILD PROCESS: " << i << endl;
            for (int j = 0; j < 8; j++) {
                sem_wait(&threadSemap); // decrement the counting semaphore value
                neurons(&data);
                sem_post(&threadSemap); // increment the counting semaphore value
            }
            data.currentLayer++;
            write(fd1[1], &data, sizeof(data));
            sem_post(&semaphore); // increment the binary semaphore value
            exit(0);
        } else if (pid < 0) {
            cout << "Failed to create child process." << endl;
            break;
        } else 
        {
            sem_post(&semaphore); // increment the binary semaphore value
            read(fd1[0], &data, sizeof(data));
            printAnswers(data);
            while (data.currentLayer == i) {
                // wait for child to complete processing
            }
            write(fd[1], &data, sizeof(data));

        }
    }


    // data.currentLayer=p-2;
    

     write(fd[1], &data, sizeof(data));

    for (int i = 6; i >= 0; i--) {
        sem_wait(&semaphore); // decrement the binary semaphore value
        pid_t pid = fork();

        if (pid == 0) {
            read(fd[0], &data, sizeof(data));
            data.currentNeuron = 0;
            cout << "\nCHILD PROCESS: " << i << endl;
            for (int j = 0; j < 8; j++) {
                sem_wait(&threadSemap); // decrement the counting semaphore value
                reverseNeurons(&data);
                sem_post(&threadSemap); // increment the counting semaphore value
            }
            data.currentLayer--;
            write(fd1[1], &data, sizeof(data));
            sem_post(&semaphore); // increment the binary semaphore value
            exit(0);
        } else if (pid < 0) {
            cout << "Failed to create child process." << endl;
            break;
        } else 
        {
            sem_post(&semaphore); // increment the binary semaphore value
            read(fd1[0], &data, sizeof(data));
            printAnswers(data);
            
            write(fd[1], &data, sizeof(data));
        }
    }

    

    cout << endl;
    sem_destroy(&semaphore);
    sem_destroy(&threadSemap); // destroy the binary semaphore
    return 0;
}

