#include <thread>
#include <mutex>

using namespace std;

int sushi_count = 5000;

void philosopher(mutex &chopsticks) {
    while (sushi_count > 0) {
        scoped_lock lock(chopsticks);
        if (sushi_count) {
            sushi_count--;
        }
        if (sushi_count == 10) {
            printf("This philosopher can't eat anymore!\n");
            break;
        }
    }
}

int main() {
    mutex chopsticks;
    thread joe(philosopher, ref(chopsticks));
    thread jane(philosopher, ref(chopsticks));
    joe.join();
    jane.join();
    printf("The philosophers are done eating.\n");
}