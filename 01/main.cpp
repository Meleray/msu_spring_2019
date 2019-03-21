#include "numbers.dat"
#include <iostream>
#include <vector>

const int MAX_N = 100001;

void Eratosphen(std::vector<bool> & p)
{
    p[0] = p[1] = false;
    for(int i = 2; i < MAX_N; ++i){
        if(p[i])
            if((long long)i * i < MAX_N)
                for (int j = i * i; j < MAX_N; j += i)
                    p[j] = false;
    }
}

using namespace std;

int main(int argc, char* argv[])
{
    vector<bool> p(MAX_N, true);
    Eratosphen(p);
    int n = argc - 1;
    if (n % 2 == 1 || n == 0)
        return -1;
    for (int i = 0; i < n; i += 2)
    {
        int ans = 0;
        int a = std::atoi(argv[i + 1]), b = std::atoi(argv[i + 2]), j = 0;
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
