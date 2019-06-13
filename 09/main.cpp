#include <thread>
#include <mutex>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const uint64_t batch_size = 100000;

void Merge_end(ifstream & in, ofstream & out, uint64_t & curr)
{
    while (!in.eof())
    {
        out.write((char*)(&curr), sizeof(curr));
        in.read((char*)(&curr), sizeof(curr));
    }
}

void Merge(string name_1, string name_2, string name_res)
{
    ifstream in1(name_1, ios::binary);
    ifstream in2(name_2, ios::binary);
    ofstream out(name_res, ios::binary);
    uint64_t a, b;
    in1.read((char*)(&a), sizeof(a));
    in2.read((char*)(&b), sizeof(b));
    while(!in1.eof() && !in2.eof())
    {
        if (a > b)
        {
            out.write((char*)(&b), sizeof(b));
            in2.read((char*)(&b), sizeof(b));
        }
        else
        {
            out.write((char*)(&a), sizeof(a));
            in1.read((char*)(&a), sizeof(a));
        }
    }
    if (in1.eof())
        Merge_end(in2, out, b);
    else
        Merge_end(in1, out, a);
    in1.close();
    in2.close();
    out.close();
}

void Sort(ifstream &in, string type, mutex &m)
{
    uint64_t counter = 0;
    while (!in.eof())
    {
        m.lock();
        uint64_t curr;
        vector<uint64_t> a;
        for (int i = 0; i < batch_size; ++i)
        {
            in.read((char*)(&curr), sizeof(curr));
            if(in.eof())
                break;
            a.push_back(curr);
        }
        if (a.size() == 0)
            break;
        m.unlock();
        sort(a.begin(), a.end());
        ofstream out(type + to_string(counter), ios::binary);
        out.write((char*)(&a[0]), a.size() * sizeof(uint64_t));
        ++counter;
        std::this_thread::yield();
    }
    --counter;
    while (counter > 0)
    {
        m.lock();
        string n1 = type + to_string(counter);
        string n2 = type + to_string(counter - 1);
        string res = type + "tmp";
        Merge(n1, n2, res);
        m.unlock();
        remove(n1.c_str());
        remove(n2.c_str());
        rename(res.c_str(), n2.c_str());
        --counter;
        std::this_thread::yield();
    }
}

int main()
{
    mutex m;
    ifstream in("input.bin", ios::binary);
    string type1 = "t1";
    string type2 = "t2";
    thread t1(Sort, ref(in), type1, ref(m));
    thread t2(Sort, ref(in), type2, ref(m));
    t1.join();
    t2.join();
    string a = "t10";//имя файла, в который будут "слиты" все файлы, на которые первый поток разобъёт исходный файл
    string b = "t20";//аналогично и для второго потока
    string ans = "output.bin";
    Merge(a, b, ans);
    remove(a.c_str());
    remove(b.c_str());
    in.close();
    return 0;
}
