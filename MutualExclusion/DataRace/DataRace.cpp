#include <thread>

using namespace std;

unsigned int garlic_count = 0;

void shopper() {
    for (int i=0; i<10000000; i++) {
        garlic_count++;
    }
}

int main() {
    thread joe(shopper);
    thread jane(shopper);
    joe.join();
    jane.join();
    printf("We should buy %u garlic.\n", garlic_count);
}