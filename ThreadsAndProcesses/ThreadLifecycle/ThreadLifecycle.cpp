#include <thread>
#include <chrono>

using namespace std;

void chef_jane() {
    printf("Jane started & waiting for sausage to thaw...\n");
    this_thread::sleep_for(chrono::seconds(3));
    printf("Jane is done cutting sausage.\n");
}

int main() {
    printf("Joe requests Jane's help.\n");
    thread jane(chef_jane);
    printf(" Jane is joinable? %s\n", jane.joinable() ? "yes" : "no");

    printf("Joe continues cooking soup.\n");
    this_thread::sleep_for(chrono::seconds(1));
    printf(" Jane is joinable? %s\n", jane.joinable() ? "yes" : "no");

    printf("Joe patiently waits for Jane to finish and join...\n");
    jane.join();
    printf(" Jane is joinable? %s\n", jane.joinable() ? "yes" : "no");

    printf("Joe and Jane are both done!\n");
}