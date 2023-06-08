#include <atomic>
#include <pthread.h>
#include <iostream>
#include <vector>
#define no_of_threads 20

using namespace std;

class BakeryLock {

private:
    vector<atomic<bool>> choosing;
    vector<atomic<int>> label_;
public:
    BakeryLock(int n) : choosing(n), label_(n) {}

    void Lock(int thread_id) {
        choosing[thread_id].store(true);
        label_[thread_id].store(FindMax() + 1);

        for (int i = 0; i < choosing.size(); ++i) {

            while (label_[i].load() != 0
                && choosing[i].load()
                && (label_[i].load() < label_[thread_id].load()
                    || (label_[i].load() == label_[thread_id].load() && i < thread_id)))
            {
                // busy-wait until it's our turn
            }
        }
    }

    void Unlock(int thread_id) {
        choosing[thread_id].store(false);
    }


    int FindMax() {
        int max_label = label_[0].load();
        for (int i = 1; i < label_.size(); ++i) {
            if (label_[i].load() > max_label) {
                max_label = label_[i].load();
            }
        }
        return max_label;
    }

};

BakeryLock lock(no_of_threads);

void* ThreadFunction(void* arg) {
    int id = *(int*)arg;
    lock.Lock(id);
    // critical section
    cout << "Thread with ID " << id << " In Critical section\n";
    lock.Unlock(id);
    //  cout<<"Thread with ID "<<id<<" Exiting Critical section\n";
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[no_of_threads];
    int thread_ids[no_of_threads];

    for (int i = 0; i < no_of_threads; ++i) {
        thread_ids[i] = i;
    }
    for (int i = 0; i < no_of_threads; ++i) {
        pthread_create(&threads[i], NULL, ThreadFunction, (void*)&thread_ids[i]);
    }
    for (int i = 0; i < no_of_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
