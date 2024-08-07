#include <future>

using namespace std;

int how_many_vegetables(){
    printf("Jane is counting vegetables...\n");
    this_thread::sleep_for(chrono::seconds(3));
    return 130;
}

int main(){
    printf("Joe asks Jane how many vegetables are in the pantry.\n");
    future<int> result = async(launch::async, how_many_vegetables);
    printf("Joe can do other things while he waits for the result... \n");
    printf("Jane responded with %d. \n", result.get());
}