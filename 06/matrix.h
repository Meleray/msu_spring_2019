#include<vector>

using namespace std;

class Row
{
    vector<int> vals;
public:
    Row(size_t n)
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
    Row& operator*=(int k)
    {
        for (int i = 0; i < vals.size(); ++i)
            vals[i] *= k;
        return *this;
    }
    bool operator==(const Row & a) const
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
    vector<Row> a;
public:
    Matrix(size_t n, size_t m) : a (n, Row(m))
    {

    }
    const Row operator[](int i) const
    {
        if (i < 0|| i >= a.size())
            throw std::out_of_range("");
        return a[i];
    }
    Row operator[](int i)
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
    Matrix& operator*=(int k)
    {
        for (int i = 0; i < a.size(); ++i)
            a[i] *= k;
        return *this;
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
