#include "suit.h"
#include <iostream>
#include <cassert>
#include <cstddef>

using namespace TestSuite;

void Suite::addTest(TestSuit::Test* t) throw(TestSuiteError)
{
    if (t == nullptr)
    {
        throw TestSuiteError("Null test in Suite::addTest");
    }
    else if (os && !t -> getStream())
    {
      t -> setStream(os);
    }
    tests.push_back(t);
    t -> reset();
}

void Suite::addSuite(const Suite& s)
{
        for (size_t i = 0; i < s.tests.size(); ++i)
        {
            assert(tests[i]);
            addTest(s.tests[i]);
        }
}

void Suite::free()
{
    for (size_t i = 0; i < tests.size(); ++i)
    {
        delete tests[i];
        tests[i] = nullptr;
    }
}

void Suite::run()
{
    reset();
    for (size_t i = 0; i < tests.size(); ++i)
    {
        assert(tests[i]);
        tests[i]->run();
    }
}

std::size_t Suite::report() const
{
    if (os)
    {
        std::size_t totFail = 0;
        *os << "Suite \"" << name << "\"\n=======";
        for (std::size_t i = 0; i < name.size(); ++i)
        {
            *os << '=';
        }
        *os << "=" << std::endl;
        for (std::size_t i = 0; i < tests.size(); ++i)
        {
            assert(tests[i]);
            totFail += tests[i]->report();
        }
        *os << "=======";
        for (std::size_t i = 0; i < name.size(); ++i)
        {
            *os << '=';
        }
        *os << "=" << std::endl;
        return totFail;
    }
    else
        return getNumFailed();
}

std::size_t Suite::getNumPassed() const
{
    std::size_t totPass = 0;
    for (size_t i = 0; i < tests.size(); ++i)
    {
        assert(tests[i]);
        totPass += tests[i]->getNumPassed();
    }
    return totPass;
}

std::size_t Suite::getNumFailed() const
{
    std::size_t totFail = 0;
    for (size_t i = 0; i < tests.size(); ++i)
    {
        assert(tests[i]);
        totFail += tests[i]->getNumFailed();
    }
    return totFail;
}

void Suite::reset()
{
    for (size_t i = 0; i < tests.size(); ++i)
    {
        assert(tests[i]);
        tests[i]->reset();
    }
}
