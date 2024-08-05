#include <thread>
#include <chrono>
#include <shared_mutex>

using namespace std;

char WEEKDAYS[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int today = 0;
shared_mutex marker;

void calendar_reader(const int id) {
    for (int i=0; i<7; i++) {
        marker.lock_shared();
        printf("Reader-%d sees today is %s\n", id, WEEKDAYS[today]);
        this_thread::sleep_for(chrono::milliseconds(100));
        marker.unlock_shared();
    }
}

void calendar_writer(const int id) {
    for (int i=0; i<7; i++) {
        marker.lock();
        today = (today + 1) % 7;
        printf("Writer-%d updated date to %s\n", id, WEEKDAYS[today]);
        this_thread::sleep_for(chrono::milliseconds(100));
        marker.unlock();
    }
}

int main() {
    array<thread, 10> readers;
    for (unsigned int i=0; i<readers.size(); i++) {
        readers[i] = thread(calendar_reader, i);
    }
    array<std::thread, 2> writers;
    for (unsigned int i=0; i<writers.size(); i++) {
        writers[i] = thread(calendar_writer, i);
    }

    for (auto & reader : readers) {
        reader.join();
    }
    for (auto & writer : writers) {
        writer.join();
    }
}