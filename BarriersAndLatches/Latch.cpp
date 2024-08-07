#include <thread>
#include <mutex>
#include <latch>

using namespace std;

unsigned int bags_of_chips = 1;
mutex pencil;
latch fist_bump(10);

void cpu_work(unsigned long workUnits) {
    unsigned long x = 0;
    for (unsigned long i = 0; i < workUnits * 1000000; i++) {
        x++;
    }
}

void joe_shopper() {
    cpu_work(1);
    fist_bump.arrive_and_wait();
    scoped_lock<mutex> lock(pencil);
    bags_of_chips *= 2;
    printf("Joe DOUBLED the bags of chips.\n");
}

void jane_shopper() {
    cpu_work(1);
    {
        scoped_lock<mutex> lock(pencil);
        bags_of_chips += 3;
    }
    printf("Jane ADDED 3 bags of chips.\n");
    fist_bump.count_down();
}

int main() {
    thread shoppers[10];
    for (int i=0; i<10; i+=2) {
        shoppers[i] = thread(joe_shopper);
        shoppers[i+1] = thread(jane_shopper);
    }

    for (auto& s : shoppers) {
        s.join();
    }

    printf("We need to buy %u bags of chips.\n", bags_of_chips);
}