#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <string>

using namespace std;

const int num = 500000;
std::mutex m;
std::condition_variable cv;
bool notified = false;

void write(const string & a)
{
    bool tmp = (a == "ping");
    for (int i = 0; i < num; ++i)
    {
        std::unique_lock<std::mutex> l(m);
        while (tmp ? notified : !notified)
            cv.wait(l);
        cout << a << endl;
        notified = tmp;
        cv.notify_all();
    }
}

int main()
{
    std::thread t(write, "ping");
    write("pong");
    t.join();
    return 0;
}
