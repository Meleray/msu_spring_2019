#include<iostream>
#include<vector>
#include<cmath>
#include<cctype>
#include<string>
#include<algorithm>



using namespace std;

string a;
int n, curr = 0;

long long eval0()
{
    if (curr < 0)
    {
        cout << "error" << endl;
        exit(1);
    }
    if (isdigit(a[curr]))
    {
        int en = curr;
        while (curr >= 0 && isdigit(a[curr]))
            --curr;
        if (curr >= 0 && a[curr] == '-' && (curr == 0 || !isdigit(a[curr - 1])))
            --curr;
        return stod(a.substr(curr + 1, en - curr));
    }
    else
    {
        cout << "error" << endl;
        exit(1);
    }
}

long long eval1()
{
    long long right = eval0();
    if (curr < 0)
        return right;
    if (a[curr] == '*' || a[curr] == '/')
    {
        --curr;
        if (a[curr + 1] == '*')
            return eval1() * right;
        else
        {
            if (right == 0)
            {
                cout << "error" << endl;
                exit(1);
            }
            return eval1() / right;
        }
    }
    else
    {
        if (a[curr] != '+' && a[curr] != '-')
        {
            cout << "error" << endl;
            exit(1);
        }
        else
            return right;
    }
}

long long eval2()
{
    long long right = eval1();
    if (curr < 0)
        return right;
    if (a[curr] == '+' || a[curr] == '-')
    {
        --curr;
        if (a[curr + 1] == '+')
            return eval2() + right;
        else
            return eval2() - right;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "error" << endl;
        exit(1);
    }
    a = argv[1];
    //getline(cin, a);
    a.erase(remove(a.begin(), a.end(), ' '), a.end());
    n = a.size();
    curr = n - 1;
    cout << eval2() << endl;
    return 0;
}
