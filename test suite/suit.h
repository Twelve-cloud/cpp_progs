#ifndef SUIT_H
#define SUIT_H

#include <vector>
#include <stdexcept>
#include "test.h"

namespace TestSuite
{
    class TestSuiteError : public std::logic_error
    {
    public:
        TestSuiteError(const std::string e) : logic_error(e) {}
    };
    class Suite
    {
    private:
        std::string name;
        std::ostream* os;
        std::vector<TestSuit::Test*> tests;
        void reset();
   public:
        Suite(const std::string& name, std::ostream* os_ = &std::cout) : name(name), os(os_) {}
        Suite(const Suite& obj) = delete;
        Suite(Suite&& obj) = delete;
        Suite& operator=(const Suite& obj) = delete;
        Suite& operator=(const Suite&& obj) = delete;

        std::string getName() const { return name; }
        std::size_t getNumPassed() const;
        std::size_t getNumFailed() const;
        const std::ostream* getStream() const { return os; }

        void setStream(std::ostream* os_) { os = os_; }
        void addTest(TestSuit::Test* t) throw (TestSuiteError);
        void addSuite(const Suite&);
        std::size_t report() const;
        void run();
        void free();
    };
} // namespace TestSuite

#endif // SUIT_H
