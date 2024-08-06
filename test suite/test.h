#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>
#include <cassert>

#define test_(cond) do_test(cond, #cond, __FILE__, __LINE__)
#define fail_(cond) do_fail(str, __FILE__, __LINE__)

#define TRACE(ARG) std::cout << #ARG << std::endl; ARG
#define TRACE_EXPR(EXPR) std::cout << #EXPR " = [" <<  EXPR << "]" << std::endl;

namespace TestSuit
{
    class Test
    {
    private:
        std::ostream* os;
        std::size_t nPass;
        std::size_t nFail;

        void do_test(bool cond, const std::string& lbl, const std::string& fname, std::size_t lineno);
        void do_fail(const std::string& lbl, const std::string& fname, std::size_t lineno);

    public:
        Test(std::ostream* os = &std::cout) : os(os), nPass(0), nFail(0) {}
        Test(const Test& obj) = delete;
        Test(Test&& obj) = delete;
        Test& operator=(const Test& obj) = delete;
        Test& operator=(const Test&& obj) = delete;

        virtual ~Test() {}
        virtual void run() = 0;
        virtual void reset() { nPass = nFail = 0; }

        std::size_t getNumPassed() const { return nPass; }
        std::size_t getNumFailed() const { return nFail; }
        const std::ostream* getStream() const { return os; }
        void setStream(std::ostream* os_) { os = os_; }
        void succeed_() { ++nPass; }
        std::size_t report() const;
    };
} // namespace TestSuit

#endif // TEST_H
