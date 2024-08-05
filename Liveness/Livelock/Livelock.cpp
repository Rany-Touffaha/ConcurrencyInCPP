#include <thread>
#include <mutex>

using namespace std;

int sushi_count = 5000;

void philosopher(mutex &first_chopstick, mutex &second_chopstick) {
    while (sushi_count > 0) {
        first_chopstick.lock();
        if (!second_chopstick.try_lock()) {
            first_chopstick.unlock();
            this_thread::yield();
        } else {
            if (sushi_count) {
                sushi_count--;
            }
            second_chopstick.unlock();
            first_chopstick.unlock();
        }
    }
}

int main() {
    mutex chopstick_a, chopstick_b;
    thread joe(philosopher, ref(chopstick_a), ref(chopstick_b));
    thread jane(philosopher, ref(chopstick_b), ref(chopstick_a));
    thread john(philosopher, ref(chopstick_a), ref(chopstick_b));
    thread james(philosopher, ref(chopstick_b), ref(chopstick_a));
    joe.join();
    jane.join();
    john.join();
    james.join();
    printf("The philosophers are done eating.\n");
}