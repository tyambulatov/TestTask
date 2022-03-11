#include "calculator.h"
#include "functionreference.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

void TestFunctionReferenceConstructor()
{
    // construction of FunctionReferenceId
    {
        Calculator calculator;
        calculator.Let("x", 1.0);
        calculator.Function("func", "x");

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n");
    }

    // construction of FunctionReferenceOperation
    {
        Calculator calculator;
        calculator.Let("x", 1.0);
        calculator.Function("func", "x", "x", '+');

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "2.00\n");
    }
}

void TestComputeTmpValue()
{
    // option 1: for FunctionReferenceId
    // id1_ is variable
    {
        Calculator calculator;
        calculator.Let("x", 1.0);
        calculator.Function("func", "x");

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n");
    }

    // id1_ is function
    {
        Calculator calculator;
        calculator.Let("x", 1.0);
        calculator.Function("func", "x");
        calculator.Function("func1", "func");

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n");
    }

    // option 2: for FunctionReferenceOperation

    // id1_ is NAN
    {
        Calculator calculator;
        calculator.AddVar("lhs");
        calculator.Let("rhs", 1.0);
        calculator.Function("func1", "lhs", "rhs", '/');

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "nan\n");
    }

    // id2_ is NAN
    {
        Calculator calculator;
        calculator.Let("lhs", 1.0);
        calculator.AddVar("rhs");
        calculator.Function("func1", "lhs", "rhs", '/');

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "nan\n");
    }

    // id1_ is NAN and id2_ is NAN
    {
        Calculator calculator;
        calculator.AddVar("lhs");
        calculator.AddVar("rhs");
        calculator.Function("func1", "lhs", "rhs", '/');

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "nan\n");
    }

    // id1_ = 0.0 and id2_ = 1.0
    {
        Calculator calculator;
        calculator.Let("lhs", 0.0);
        calculator.Let("rhs", 1.0);
        calculator.Function("func1", "lhs", "rhs", '/');

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "0.00\n");
    }

    // id1_ = 0.0 and id2_ = 0.0
    {
        Calculator calculator;
        calculator.Let("lhs", 0.0);
        calculator.Let("rhs", 0.0);
        calculator.Function("func1", "lhs", "rhs", '/');

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "nan\n");
    }

    // id1_ = 1.0 and id2_ = 0.0
    {
        Calculator calculator;
        calculator.Let("lhs", 1.0);
        calculator.Let("rhs", 0.0);
        calculator.Function("func1", "lhs", "rhs", '/');

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "inf\n");
    }

    // id1_ = -1.0 and id2_ = 0.0
    {
        Calculator calculator;
        calculator.Let("lhs", -1.0);
        calculator.Let("rhs", 0.0);
        calculator.Function("func1", "lhs", "rhs", '/');

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "-inf\n");
    }
}

void TestGetValue()
{
    // id1 is variable
    {
        Calculator calculator;
        calculator.Let("x", 1.0);
        calculator.Function("func", "x");

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n");
    }

    // id1 is function
    {
        Calculator calculator;
        calculator.Let("x", 1.0);
        calculator.Function("func", "x");
        calculator.Function("func1", "func");

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n");
    }
}