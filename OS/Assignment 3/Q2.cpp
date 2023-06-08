#include<iostream>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include<vector>


using namespace std;

//Global Variables
pthread_mutex_t lock;
int cars_on_bridge = 0;
int buses_on_bridge = 0;

//ArriveAtBridge Function

void ArriveAtBridge(int direction, int vehicleType)
{
    //Lock the Critical Section
    pthread_mutex_lock(&lock);

    //Enter the Critical Section
    if (vehicleType == 0) //If Car
    {
        if (cars_on_bridge >= 4 || (buses_on_bridge > 0 && cars_on_bridge >= 2)) {
            cout << " More than 4 vehicles on the bridge, CAR waiting..." << endl;

            while (buses_on_bridge > 0 && cars_on_bridge >= 2) {
                pthread_mutex_unlock(&lock);
                usleep(1000);
                pthread_mutex_lock(&lock);
            }
            while (cars_on_bridge >= 4) {
                pthread_mutex_unlock(&lock);
                usleep(1000);
                pthread_mutex_lock(&lock);
            }


        }

        if (buses_on_bridge <= 1) //No Buses
        {
            if (cars_on_bridge < 4) //Less than 4 Cars
            {
                cars_on_bridge++;
                cout << "-> Car has entered the bridge in direction: " << direction << endl;

            }
            else
            {
                cout << "Car is waiting to enter the bridge in direction: " << direction << endl;
                pthread_mutex_unlock(&lock);
                // return;
            }
        }
        else //Buses present
        {
            cout << "Car is waiting to enter the bridge in direction: " << direction << endl;
            pthread_mutex_unlock(&lock);
            // return;
        }
    }
    else if (vehicleType == 1) //If Bus
    {
        if ((buses_on_bridge > 0 || cars_on_bridge >= 2)) {
            cout << " More than 4 vehicles on the bridge, BUS waiting..." << endl;
            while (buses_on_bridge > 0 || cars_on_bridge >= 2) {
                pthread_mutex_unlock(&lock);
                usleep(10);
                pthread_mutex_lock(&lock);
            }

        }
        if (buses_on_bridge < 1) //No Buses
        {
            if (cars_on_bridge <= 2) //No Cars
            {
                buses_on_bridge++;
                cout << "=> Bus has entered the bridge in direction: " << direction << endl;
            }
            else
            {
                cout << "Bus is waiting to enter the bridge in direction: " << direction << endl;
                pthread_mutex_unlock(&lock);
                return;
            }
        }
        else //Buses present
        {
            cout << "Bus is waiting to enter the bridge in direction: " << direction << endl;
            pthread_mutex_unlock(&lock);
            return;
        }
    }

    //Unlock the Critical Section
    pthread_mutex_unlock(&lock);
}

//ExitTheBridge Function
void ExitTheBridge(int direction, int vehicleType)
{
    //Lock the Critical Section
    pthread_mutex_lock(&lock);

    //Enter the Critical Section
    if (vehicleType == 0) //If Car
    {
        cars_on_bridge--;
        cout << "<- Car has exited the bridge in direction: " << direction << endl;
    }
    else if (vehicleType == 1) //If Bus
    {
        buses_on_bridge--;
        cout << "<= Bus has exited the bridge in direction: " << direction << endl;
    }

    //Unlock the Critical Section
    pthread_mutex_unlock(&lock);
}

//Vehicle Thread Function
void* vehicle(void* arg)
{
    int direction = *(int*)arg;

    //Generate a Random Number
    int vehicleType = rand() % 2;

    //Call ArriveAtBridge Function
    ArriveAtBridge(direction, vehicleType);

    //Sleep
    sleep(1);

    //Call ExitTheBridge Function
    ExitTheBridge(direction, vehicleType);

    //Exit Thread

    pthread_exit(NULL);
}

//Main Function
int main()
{
    srand(time(NULL));

    //Initialize the Lock
    pthread_mutex_init(&lock, NULL);

    //Create a Vector of Threads
    vector<pthread_t> threads;

    //Create 20 Threads
    for (int i = 0; i < 20; i++)
    {
        pthread_t tid;
        int direction = rand() % 2;
        pthread_create(&tid, NULL, vehicle, &direction);
        threads.push_back(tid);
    }

    //Join the Threads
    for (int i = 0; i < 20; i++)
    {
        pthread_join(threads[i], NULL);
    }

    //Destroy the Lock
    pthread_mutex_destroy(&lock);

    return 0;
}



// int main()
// {
//     int minutes;
//     cout << "Enter the number of minutes to run the program: ";
//     cin >> minutes;

//     time_t start, end;
//     time(&start);
//     time(&end);

//     vector<pthread_t> thradsList;

//     while (difftime(end, start) <= minutes * 1)
//     {
//         //Generate a Random Direction
//         int direction = rand() % 2;

//         //Create a Vehicle Thread
//         pthread_t vThread;
//         thradsList.push_back(vThread);
//         pthread_create(&vThread, NULL, vehicle, &direction);

//         //Update the time
//         time(&end);
//     }

//     for (int i = 0; i < thradsList.size(); i++)
//     {
//         pthread_join(thradsList[i], NULL);
//     }

//     return 0;
// }
