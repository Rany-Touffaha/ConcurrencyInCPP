#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

unsigned int garlic_count = 0;
mutex pencil;

void shopper() {
    for (int i=0; i<5; i++) {
        printf("Shopper %d is thinking... \n", this_thread::get_id());
        this_thread::sleep_for(chrono::milliseconds(500));
        pencil.lock();
        garlic_count++;
        pencil.unlock();
    }
}

int main() {
    thread barron(shopper);
    thread olivia(shopper);
    barron.join();
    olivia.join();
    printf("We should buy %u garlic.\n", garlic_count);
}
