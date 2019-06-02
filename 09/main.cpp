#include<iostream>
#include<fstream>
#include<ostream>
#include<mutex>
#include<thread>
#include<condition_variable>
#include<limits>

using namespace std;

mutex m;
condition_variable processed;
const uint64_t MaxN = numeric_limits<uint64_t>::max();

void Count(string &name, bool &ready, bool &outend, uint64_t &counter)
{
	for (uint64_t curr = 0; curr <= MaxN; ++curr)
    	{
		unique_lock<mutex> lock(m);
		while (!outend)
            		processed.wait(lock);
		counter = 0;
		ifstream in(name, std::ios::binary | std::ios::in);
		uint64_t x;
		for (; in.read((char *) &x, sizeof(uint64_t));)
        	{
			if (x == curr)
                		++counter;
		}
		in.close();
		lock.unlock();
        	ready = true;
		outend = false;
		processed.notify_one();
	}
}

void Out(string &name, , bool &ready, bool &outend, uint64_t &counter)
{
	ofstream out(name);
	for (uint64_t curr = 0; curr <= MaxN; ++curr)
    	{
		unique_lock<mutex> lock(m);
		outend = true;
		processed.notify_one();
		while (!ready)
            		processed.wait(lock);
        	uint64_t tmp = counter;
		for (uint64_t i = 0; i < tmp; ++i)
			out << curr << ' ';
		ready = false;
		lock.unlock();
	}
	out.close();
}


int main()
{
	uint64_t counter = 0;
	bool outend = false;
	bool ready = false;
	string a = "input.bin";
	string b = "output.txt";
	thread t1(Count, std::ref(a), std::ref(ready), std::ref(outend), std::ref(counter));
	thread t2(Out, std::ref(b), std::ref(ready), std::ref(outend), std::ref(counter));
	t1.join();
	t2.join();
	return 0;
}
