#include <thread>
#include <mutex>

using namespace std;

int sushi_count = 5000;

void philosopher(mutex &first_chopstick, mutex &second_chopstick) {
    while (sushi_count > 0) {
        scoped_lock lock(first_chopstick, second_chopstick);
        if (sushi_count) {
            sushi_count--;
        }
        second_chopstick.unlock();
        first_chopstick.unlock();
    }
}

int main() {
    mutex chopstick_a, chopstick_b;
    thread joe(philosopher, ref(chopstick_a), ref(chopstick_b));
    thread jane(philosopher, ref(chopstick_b), ref(chopstick_a));
    joe.join();
    jane.join();
    printf("The philosophers are done eating.\n");
}