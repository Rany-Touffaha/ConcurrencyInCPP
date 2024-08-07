#include <thread>
#include <condition_variable>

using namespace std;

int soup_servings = 10;
mutex slow_cooker_lid;
condition_variable soup_taken;

void hungry_person(int id) {
    int put_lid_back = 0;
    while (soup_servings > 0) {
        unique_lock<mutex> lid_lock(slow_cooker_lid);
        while ((id != soup_servings % 5) && (soup_servings > 0)) {
            put_lid_back++;
            soup_taken.wait(lid_lock);
        }
        if (soup_servings > 0) {
            soup_servings--;
            lid_lock.unlock();
            soup_taken.notify_all();
        }

    }
    printf("Person %d put the lid back %u times.\n", id, put_lid_back);
}

int main() {
    thread hungry_threads[5];
    for (int i=0; i<5; i++) {
        hungry_threads[i] = std::thread(hungry_person, i);
    }

    for (auto& ht : hungry_threads) {
        ht.join();
    }
}