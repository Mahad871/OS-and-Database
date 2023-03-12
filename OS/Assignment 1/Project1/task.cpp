#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include <fstream>


using namespace std;

int generateRandomNumber() {

    srand(time(nullptr));

    int random_number = rand() % 99 + 10;

    random_number *= 5;
    random_number = 0475 / random_number;
    random_number %= 25;
    random_number += 15;

    return random_number;
}

int** createMatix(int n) {

    int** mtx = new int* [n];


    for (int i = 0; i < n; i++)
    {
        mtx[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            
            mtx[i][j] = rand() % 100 + 0;
            cout << mtx[i][j] << " ";
        }
        cout << endl;
    }

    ofstream outfile("matrix.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outfile << mtx[i][j] << " ";
        }
        outfile << std::endl;
    }
    outfile.close();
    return mtx;
}

int mpmtx(int ** mtx,int n){
       
for (int i = 0; i < n; i++) {
        int pid = fork();
        if (pid == -1) {
            cerr << "Error: Fork failed.\n";
            return 1;
        }
        else if (pid == 0) {
            // Child process
            ofstream result_file("result_" + to_string(i) + ".txt");
            for (int j = 0; j < n; j++) {
                int result = 0;
                for (int k = 0; k < n; k++) {
                    result += mtx[i][k] * mtx[k][j];
                }
                result_file << result << " ";
            }
            result_file.close();
            return 0;
        }

    }

    for (int i = 0; i < n; i++) {
        wait(nullptr);
    }
    return -1;
}


int main() {


    int n = generateRandomNumber();

    cout << "Random number: " << n<<endl;
    
    cout << "\n__________________________________________________________________\n\n\t\tORIGIONAL MATRIX\n__________________________________________________________________\n\n";


    int** mtx = createMatix(n);



    if(mpmtx(mtx,n)==-1){
    
    cout << "\n__________________________________________________________________\n\n\t\tRESULTANT MATRIX\n__________________________________________________________________\n\n";
    
    // cout<<"\nLOOP EXECUTED";
    for (int i = 0; i < n; i++) {
        
        
            
            ifstream result_file("result_" + to_string(i) + ".txt");
                 string line;
                getline(result_file, line) ;
                cout <<"| "<< line << "| \n"; 
    

            
        }
    cout << "\n___________________________________________________________________\n";

    // cout<<"\nLOOP EXECUTION ENED";
    }

    for (int i = 0; i < n; i++) {
        delete[] mtx[i];
    }
    delete[] mtx;

    return 0;
}