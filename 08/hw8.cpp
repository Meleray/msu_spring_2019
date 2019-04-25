#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

const int num = 500000;
std::mutex m;
std::condition_variable cv;
bool notified = false;

void ping()
{
    for (int i = 0; i < num; ++i)
    {
        std::unique_lock<std::mutex> l(m);
        while (notified)
            cv.wait(l);
        cout << "ping" << endl;
        notified = true;
        l.unlock();
        cv.notify_all();
    }
}

int main()
{
    std::thread t(ping);
    for (int i = 0; i < num; ++i)
    {
	std::unique_lock<std::mutex> l(m);
	while (!notified)
        cv.wait(l);
	cout << "pong" << endl;
	notified = false;
	l.unlock();
	cv.notify_all();
    }
    t.join();
    return 0;
}
