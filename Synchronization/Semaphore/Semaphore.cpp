#include <thread>
#include <chrono>
#include <condition_variable>

using namespace std;

class Semaphore {
public:
    explicit Semaphore(unsigned long init_count) {
        count_ = init_count;
    }

    void acquire() {
        unique_lock<mutex> lck(m_);
        while (!count_) {
            cv_.wait(lck);
        }
        count_--;
    }

    void release() {
        unique_lock<mutex> lck(m_);
        count_++;
        lck.unlock();
        cv_.notify_one();
    }

private:
    mutex m_;
    condition_variable cv_;
    unsigned long count_;
};

Semaphore charger(4);

void cell_phone(int id) {
    charger.acquire();
    printf("Phone %d is charging...\n", id);
    srand(id);
    this_thread::sleep_for(chrono::milliseconds(rand() % 2000 + 1000));
    printf("Phone %d is DONE charging!\n", id);
    charger.release();
}

int main() {
    thread phones[10];
    for (int i=0; i<10; i++) {
        phones[i] = thread(cell_phone, i);
    }

    for (auto& p : phones) {
        p.join();
    }
}