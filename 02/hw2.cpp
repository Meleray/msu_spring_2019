#include<iostream>
#include<vector>
#include<cmath>
#include<cctype>
#include<string>
#include<algorithm>

using namespace std;

long long parse_double(string & a, int & n, int &curr, int & error_flag)
{
    if (curr < 0)
    {
        error_flag = 1;
        return 1;
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
        error_flag = 1;
        return 1;
    }
}

long long parse_mul_div(string & a, int & n, int &curr, int & error_flag)
{
    long long right = parse_double(a, n, curr, error_flag);
    if (error_flag)
        return 1;
    if (curr < 0)
        return right;
    if (a[curr] == '*' || a[curr] == '/')
    {
        --curr;
        if (a[curr + 1] == '*')
        {
            double d = parse_mul_div(a, n, curr, error_flag);
            if (error_flag)
                return 1;
            return d * right;
        }
        else
        {
            if (right == 0)
            {
                error_flag = 1;
                return 1;
            }
            double d = parse_mul_div(a, n, curr, error_flag);
            if (error_flag)
                return 1;
            return d / right;
        }
    }
    else
    {
        if (a[curr] != '+' && a[curr] != '-')
        {
            error_flag = 1;
            return 1;
        }
        else
            return right;
    }
}

long long parse_plus_minus(string & a, int & n, int & curr, int & error_flag)
{

    long long right = parse_mul_div(a, n, curr, error_flag);
    if (error_flag)
        return 1;
    if (curr < 0)
        return right;
    if (a[curr] == '+' || a[curr] == '-')
    {
        --curr;
        if (a[curr + 1] == '+')
        {
            double d = parse_plus_minus(a, n, curr, error_flag);
            if (error_flag)
                return 1;
            return d + right;
        }
        else
        {
            double d = parse_plus_minus(a, n, curr, error_flag);
            if (error_flag)
                return 1;
            return d - right;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "error" << endl;
        return 1;
    }
    string a = argv[1];
    //getline(cin, a);
    a.erase(remove(a.begin(), a.end(), ' '), a.end());
    int n = a.size();
    int curr = n - 1;
    int error_flag = 0;
    double d = parse_plus_minus(a, n, curr, error_flag);
    if (error_flag)
    {
        cout << "error" << endl;
        return 1;
    }
    cout << d << endl;
    return 0;
}
