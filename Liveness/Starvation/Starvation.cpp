#include <thread>
#include <mutex>

using namespace std;

int sushi_count = 5000;

void philosopher(mutex &chopsticks) {
    int sushi_eaten = 0;
    while (sushi_count > 0) {
        scoped_lock lock(chopsticks);
        if (sushi_count) {
            sushi_count--;
            sushi_eaten++;
        }
    }
    printf("Philosopher %d ate %d.\n", this_thread::get_id(), sushi_eaten);
}

int main() {
    mutex chopsticks;
    array<thread, 200> philosophers;
    for (auto & i : philosophers) {
        i = thread(philosopher, ref(chopsticks));
    }
    for (auto & philosopher : philosophers) {
        philosopher.join();
    }
    printf("The philosophers are done eating.\n");
}