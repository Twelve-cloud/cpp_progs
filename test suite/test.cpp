#include "test.h"
#include <iostream>
#include <typeinfo>

using namespace TestSuit;

void Test::do_test(bool cond, const std::string &lbl, const std::string &fname, std::size_t lineno)
{
    if (!cond)
        do_fail(lbl, fname, lineno);
    else
        succeed_();
}

void Test::do_fail(const std::string &lbl, const std::string &fname, std::size_t lineno)
{
    ++nFail;
    if (os)
    {
        *os << typeid(*this).name() << "failure: (" << lbl << "). " << fname << " (line " << lineno <<")" << std::endl;
    }
}

size_t Test::report() const
{
    if (os)
    {
        *os << "Test \"" << typeid(*this).name() << "\":\n\tPassed: " << nPass << "\tFailed: " << nFail << std::endl;
    }
    return nFail;
}
