#include "numbers.dat"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    vector<int> p(100001, true);
    p[0] = p[1] = false;
    for(int i = 2; i < 100001; ++i){
        if(p[i])
            if((long long)i * i <= 100000)
                for (int j = i * i; j < 100001; j += i)
                    p[j] = false;
    }
    vector<int> in;
    for (int i = 1; i < argc; ++i)
    {
        int v = std::atoi(argv[i]);
        in.push_back(v);
    }
    int n = in.size();
    if (n % 2 == 1 || n == 0)
        return -1;
    for (int i = 0; i < n; i += 2)
    {
        int ans = 0;
        int a = in[i], b = in[i + 1], j = 0;
        while (j < Size && Data[j] != a)
            ++j;
        while (j < Size && Data[j] != b)
        {
            ans += p[Data[j]];
            ++j;
        }
        if (j == Size)
            cout << 0 << endl;
        else
        {
            ans += p[Data[j]];
            cout << ans << endl;
        }
    }
    return 0;
}
