#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>

using namespace std;

class ThreadPool {

public:
    explicit ThreadPool(size_t numberOfThreads = thread::hardware_concurrency()) {

        for (size_t i = 0; i < numberOfThreads; ++i) {
            threadVector.emplace_back([this] {
                while (true) {
                    function<void()> task;

                    {
                        unique_lock<mutex> lock(queueMutex);

                        conditionVariable.wait(lock, [this] {
                            return !tasksToQueue.empty() || end;
                        });

                        if (end && tasksToQueue.empty())
                            return;

                        task = std::move(tasksToQueue.front());
                        tasksToQueue.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool()
    {
        {
            unique_lock<mutex> lock(queueMutex);
            end = true;
        }

        conditionVariable.notify_all();

        for (auto& thread : threadVector) {
            thread.join();
        }
    }

    void enqueue(function<void()> task)
    {
        {
            unique_lock<mutex> lock(queueMutex);
            tasksToQueue.emplace(std::move(task));
        }

        conditionVariable.notify_one();
    }

private:
    vector<thread> threadVector;
    queue<function<void()> > tasksToQueue;
    mutex queueMutex;
    condition_variable conditionVariable;
    bool end = false;
};

void vegetable_chopper(int vegetable_id) {
    printf("Thread %d chopped vegetable %d.\n", this_thread::get_id(), vegetable_id);
}

int main() {
    ThreadPool pool(4);
    for (int i=0; i<100; i++) {
        pool.enqueue([i](){ vegetable_chopper(i);});
    }
}