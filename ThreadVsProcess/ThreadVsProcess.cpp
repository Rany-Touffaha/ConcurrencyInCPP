#include <thread>
#include <chrono>
#include <unistd.h>

using namespace std;

void cpu_waster() {
    printf("CPU Waster Process ID: %d\n", getpid());
    printf("CPU Waster Thread ID %d\n", this_thread::get_id());
    while(true) continue;
}

int main() {
    printf("Main Process ID: %d\n", getpid());
    printf("Main Thread ID: %d\n", this_thread::get_id());
    thread thread1(cpu_waster);
    thread thread2(cpu_waster);

    while(true) {
        this_thread::sleep_for(chrono::seconds(1));
    }

}