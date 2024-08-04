#include <thread>
#include <chrono>

using namespace std;

void kitchen_cleaner() {
    while (true) {
        printf("Jane cleaned the kitchen.\n");
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    thread jane(kitchen_cleaner);
    jane.detach();
    for (int i=0; i<3; i++) {
        printf("Joe is cooking...\n");
        this_thread::sleep_for(chrono::milliseconds(600));
    }
    printf("Joe is done!\n");
}