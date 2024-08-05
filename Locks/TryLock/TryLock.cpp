#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

unsigned int items_on_notepad = 0;
mutex pencil;

void shopper(const char* name) {
    int items_to_add = 0;
    while (items_on_notepad <= 20) {
        if (items_to_add && pencil.try_lock()) {
            items_on_notepad += items_to_add;
            printf("%s added %u item(s) to notepad.\n", name, items_to_add);
            items_to_add = 0;
            this_thread::sleep_for(chrono::milliseconds(300));
            pencil.unlock();
        } else {
            this_thread::sleep_for(chrono::milliseconds(100));
            items_to_add++;
            printf("%s found something else to buy.\n", name);
        }
    }
}

int main() {
    auto start_time = chrono::steady_clock::now();
    thread joe(shopper, "Joe");
    thread jane(shopper, "Jane");
    joe.join();
    jane.join();
    auto elapsed_time = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start_time).count();
    printf("Elapsed Time: %.2f seconds\n", elapsed_time/1000.0);
}