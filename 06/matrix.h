#include<vector>

using namespace std;

class row
{
    vector<int> vals;
public:
    row(size_t n)
    {
        vals.resize(n, 0);
    }
    int operator[](int i) const
    {
        if (i < 0|| i >= vals.size())
            throw std::out_of_range("");
        return vals[i];
    }
    int& operator[](int i)
    {
        if (i < 0|| i >= vals.size())
            throw std::out_of_range("");
        return vals[i];
    }
    size_t getSize() const
    {
        return vals.size();
    }
    void operator*=(int k)
    {
        for (int i = 0; i < vals.size(); ++i)
            vals[i] *= k;
    }
    bool operator==(const row & a) const
    {
        if (vals.size() != a.vals.size())
            return 0;
        for (int i = 0; i < vals.size(); ++i)
        {
            if (vals[i] != a.vals[i])
                return 0;
        }
        return 1;
    }
};

class Matrix
{
    vector<row> a;
public:
    Matrix(size_t n, size_t m)
    {
        a.resize(n, row(m));
    }
    const row operator[](int i) const
    {
        if (i < 0|| i >= a.size())
            throw std::out_of_range("");
        return a[i];
    }
    row operator[](int i)
    {
        if (i < 0|| i >= a.size())
            throw std::out_of_range("");
        return a[i];
    }
    size_t getRows() const
    {
        return a.size();
    }
    size_t getColumns() const
    {
        return a[0].getSize();
    }
    void operator*=(int k)
    {
        for (int i = 0; i < a.size(); ++i)
            a[i] *= k;
    }
    bool operator==(const Matrix & b) const
    {
        if (a.size() != b.a.size())
            return 0;
        for (int i = 0; i < a.size(); ++i)
        {
            if (!(a[i] == b.a[i]))
                return 0;
        }
        return 1;
    }
};
