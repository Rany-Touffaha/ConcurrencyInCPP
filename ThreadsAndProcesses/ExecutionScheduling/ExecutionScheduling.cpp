#include <thread>
#include <chrono>

using namespace std;

bool chopping = true;

void vegetable_chopper(const char* name) {
    unsigned int vegetable_count = 0;
    while (chopping) {
        vegetable_count++;
    }
    printf("%s chopped %u vegetables.\n", name, vegetable_count);
}

int main() {
    thread jane(vegetable_chopper, "Jane");
    thread joe(vegetable_chopper, "Joe");

    printf("Joe and Jane are chopping vegetables...\n");
    this_thread::sleep_for(chrono::seconds(1));
    chopping = false;
    joe.join();
    jane.join();
}