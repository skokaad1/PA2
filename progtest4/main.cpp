
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;

class A
{
public:
    A(void) { cout << *this; }
    virtual ~A(void) { }
    virtual void print(ostream& os) const = 0;
    friend ostream& operator << (ostream& os, const A& x)
    {
        x.print(os); return os;
    }
};

class B : public A
{
public:
    B(int x) { m_X = x; }
    virtual void print(ostream& os) const { os << "B:" << m_X; }
private:
    int m_X;
};

int main(void)
{
    B test(91);
    return 0;
}