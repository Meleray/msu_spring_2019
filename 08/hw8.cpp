#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

int main(void)
{
	std::mutex m;
	std::condition_variable cv;
	bool notified = false;
	std::thread t([&] {
		for (int i = 0; i < 500000; ++i) {
			std::unique_lock<std::mutex> l(m);
			cv.wait(l, [&notified] { return !notified; });
			cout << "Ping" << endl;
			notified = true;
			l.unlock();
			cv.notify_all();
		}
	});

	for (int i = 0; i < 500000; ++i) {
		std::unique_lock<std::mutex> l(m);
		cv.wait(l, [&notified] { return notified; });
		cout << "Pong" << endl;
		notified = false;
		l.unlock();
		cv.notify_all();
	}
	t.join();
	return 0;
}
