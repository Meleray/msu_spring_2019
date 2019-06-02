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

void Count(ifstream & in, bool &ready, bool &outend, uint64_t &counter)
{
	for (uint64_t curr = 0; curr <= MaxN; ++curr)
    	{
		unique_lock<mutex> lock(m);
		while (!outend)
            		processed.wait(lock);
		counter = 0;
		uint64_t x;
		for (; in.read((char *) &x, sizeof(uint64_t));)
        	{
			if (x == curr)
                		++counter;
		}
		in.clear();
		in.seekg(0, ios::beg);
		lock.unlock();
        	ready = true;
		outend = false;
		processed.notify_one();
	}
}

void Out(ofstream & out, bool &ready, bool &outend, uint64_t &counter)
{
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
}


int main()
{
	uint64_t counter = 0;
	bool outend = false;
	bool ready = false;
	ifstream in("input.bin", std::ios::binary | std::ios::in);
	ofstream out("output.txt");
	thread t1(Count, std::ref(in), std::ref(ready), std::ref(outend), std::ref(counter));
	thread t2(Out, std::ref(out), std::ref(ready), std::ref(outend), std::ref(counter));
	t1.join();
	t2.join();
	return 0;
}
