#include <cstdio>
#include <future>

using namespace std;

unsigned long long recursive_sum(unsigned int lo , unsigned int hi, unsigned int depth=0) {
    if (depth > 3) {
        unsigned long long sum = 0;
        for (auto i=lo; i<hi; i++) {
            sum += i;
        }
        return sum;
    } else {
        auto mid = (hi + lo) / 2;
        auto left = async(launch::async, recursive_sum, lo, mid, depth+1);
        auto right = recursive_sum(mid, hi, depth+1);
        return left.get() + right;
    }
}

int main() {
    unsigned long long total = recursive_sum(0, 1000000000);
    printf("Total: %lld\n", total);
}