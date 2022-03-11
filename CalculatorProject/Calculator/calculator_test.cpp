#include "calculator.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

void TestAddVar()
{
    // add var with first symbol letter
    {
        Calculator calculator;
        calculator.AddVar("a");
        stringstream ss;
        calculator.Print("a", ss);
        ASSERT_EQUAL(ss.str(), "nan\n");
    }

    // add var with first symbol '_'
    {
        Calculator calculator;
        calculator.AddVar("_");
        stringstream ss;
        calculator.Print("_", ss);
        ASSERT_EQUAL(ss.str(), "nan\n");
    }

    // try to add initilized var id
    try
    {
        Calculator calculator;
        calculator.AddVar("a");
        calculator.AddVar("a");
    }
    catch (const exception& e)
    {
    }

    // try to add initilized function id
    try
    {
        Calculator calculator;
        calculator.AddVar("a");
        calculator.Function("func", "a");
        calculator.AddVar("func");
    }
    catch (const exception& e)
    {
    }

    // check that var got nan value
    {
        Calculator calculator;
        calculator.AddVar("a");
        stringstream ss;
        calculator.PrintVars(ss);
        ASSERT_EQUAL(ss.str(), "a:nan\n");
    }
}
void TestLet()
{
    // Test variant 1: <id>=<number>
    // Check if id1 was diclared
    try
    {
        Calculator calculator;
        calculator.AddVar("a");
        calculator.Function("funcName", "a");
        calculator.Let("funcName", 1.0);
    }
    catch (const exception& e)
    {
    }

    // Adding to variableToValue
    {
        Calculator calculator;
        calculator.Let("var", 1.0);
        stringstream ss;
        calculator.Print("var", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n");
    }

    // Adding to variableSortedNames
    {
        Calculator calculator;
        calculator.Let("var", 1.0);
        stringstream ss;
        calculator.PrintVars(ss);
        ASSERT_EQUAL(ss.str(), "var:1.00\n");
    }

    // Test variant 2: <id1>=<id2>

    // Test variable id1 has been declared as function id
    try
    {
        Calculator calculator;
        calculator.AddVar("a");
        calculator.Function("funcName", "a");
        calculator.Let("funcName", "a");
    }
    catch (const exception& e)
    {
    }

    // Test if id2 have not been declared
    try
    {
        Calculator calculator;
        calculator.Let("a", "b");
    }
    catch (const exception& e)
    {
    }

    // Test variable id1 got value of variable id2
    {
        Calculator calculator;
        calculator.Let("a", 1.0);
        calculator.Let("b", "a");
        stringstream ss;
        calculator.Print("b", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n")
    }

    // Test that id2 can be function value
    {
        Calculator calculator;
        calculator.Let("a", 1.00);
        calculator.Function("funcName", "a");
        calculator.Let("b", "a");
        stringstream ss;
        calculator.Print("b", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n")
    }

    // The rest of variant 2 method is the same
}
void TestFunction()
{
    // Variant 1 : <id1>=<id2>
    // Test if id1 have been declared as variable
    try
    {
        Calculator calculator;
        calculator.AddVar("a");
        calculator.Function("a", "a");
    }
    catch (const exception& e)
    {
    }

    // Test if id1 have been declared as function
    try
    {
        Calculator calculator;
        calculator.AddVar("a");
        calculator.Function("b", "a");
        calculator.Function("b", "b");
    }
    catch (const exception& e)
    {
    }

    // Test id2 was not declated
    try
    {
        Calculator calculator;
        calculator.Function("a", "b");
    }
    catch (const exception& e)
    {
    }

    // Test id3 was not declated, id2 as var of func
    try
    {
        Calculator calculator;
        calculator.AddVar("b");
        calculator.Function("a", "b", "c", '+');
    }
    catch (const exception& e)
    {
    }

    try
    {
        Calculator calculator;
        calculator.AddVar("b");
        calculator.Function("func", "b");
        calculator.Function("a", "func", "c", '+');
    }
    catch (const exception& e)
    {
    }

    // Test added reference to var
    {
        Calculator calculator;
        calculator.Let("a", 1.0);
        calculator.Function("func", "a");

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n")
    }

    // Test added reference to func
    {
        Calculator calculator;
        calculator.Let("a", 1.0);
        calculator.Function("func1", "a");
        calculator.Function("func2", "func1");

        stringstream ss;
        calculator.Print("func2", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n")
    }

    // Test added to functionSortedIdentifications
    {
        Calculator calculator;
        calculator.Let("a", 1.0);
        calculator.Function("func1", "a");

        stringstream ss;
        calculator.PrintFunctions(ss);
        ASSERT_EQUAL(ss.str(), "func1:1.00\n")
    }

    // variant 2: <id1>=<id2><op><id3>
    // Test added reference id3 to var
    {
        Calculator calculator;
        calculator.Let("a", 1.0);
        calculator.Let("b", 2.0);
        calculator.Function("func", "a", "b", '+');

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "3.00\n")
    }

    // Test added reference id3 to func
    {
        Calculator calculator;
        calculator.Let("a", 1.0);
        calculator.Function("func1", "a");
        calculator.Function("func2", "func1", "func1", '+');

        stringstream ss;
        calculator.Print("func2", ss);
        ASSERT_EQUAL(ss.str(), "2.00\n")
    }
}

void TestPrint()
{
    // Test id have not been declared
    try
    {
        Calculator calculator;

        stringstream ss;
        calculator.Print("func", ss);
    }
    catch (const exception& e)
    {
    }

    // Test print diclared variable
    {
        Calculator calculator;
        calculator.Let("a", 1.0);

        stringstream ss;
        calculator.Print("a", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n")
    }

    // Test print diclared function
    {
        Calculator calculator;
        calculator.Let("a", 1.0);
        calculator.Function("func", "a");

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n")
    }

    // Test presision
    {
        Calculator calculator;
        calculator.Let("a", 1);

        stringstream ss;
        calculator.Print("a", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n")
    }

    {
        Calculator calculator;
        calculator.Let("a", 1.333333333);

        stringstream ss;
        calculator.Print("a", ss);
        ASSERT_EQUAL(ss.str(), "1.33\n")
    }

    {
        Calculator calculator;
        calculator.Let("a", 0);

        stringstream ss;
        calculator.Print("a", ss);
        ASSERT_EQUAL(ss.str(), "0.00\n")
    }
}
void TestPrintVars()
{
    // Test zero variables
    {
        Calculator calculator;

        stringstream ss;
        calculator.PrintVars(ss);
        ASSERT_EQUAL(ss.str(), "")
    }

    // Test unordered variables
    {
        Calculator calculator;
        calculator.Let("d", 4);
        calculator.Let("b", 2);
        calculator.Let("c", 3);
        calculator.Let("a", 1);

        stringstream ss;
        calculator.PrintVars(ss);
        ASSERT_EQUAL(ss.str(), "a:1.00\nb:2.00\nc:3.00\nd:4.00\n")
    }
}
void TestPrintFunctions()
{
    // Test zero functions
    {
        Calculator calculator;

        stringstream ss;
        calculator.PrintFunctions(ss);
        ASSERT_EQUAL(ss.str(), "")
    }

    // Test unordered functions
    {

        Calculator calculator;
        calculator.Let("a", 1.00);
        calculator.Function("fn4", "a", "a", '+');
        calculator.Function("fn3", "a", "a", '+');
        calculator.Function("fn2", "a", "a", '+');
        calculator.Function("fn5", "a", "a", '+');
        calculator.Function("fn1", "a", "a", '+');

        stringstream ss;
        calculator.PrintFunctions(ss);
        ASSERT_EQUAL(ss.str(), "fn1:2.00\nfn2:2.00\nfn3:2.00\nfn4:2.00\nfn5:2.00\n")
    }
}

void TestGetIdValue()
{
    // test value var is 0
    {

        Calculator calculator;
        calculator.Let("a", 0);

        stringstream ss;
        calculator.Print("a", ss);
        ASSERT_EQUAL(ss.str(), "0.00\n")
    }

    // test value var is -1
    {

        Calculator calculator;
        calculator.Let("a", -1);

        stringstream ss;
        calculator.Print("a", ss);
        ASSERT_EQUAL(ss.str(), "-1.00\n")
    }

    // test value var is nan
    {

        Calculator calculator;
        calculator.AddVar("a");

        stringstream ss;
        calculator.Print("a", ss);
        ASSERT_EQUAL(ss.str(), "nan\n")
    }

    // test value var is num
    {

        Calculator calculator;
        calculator.AddVar("a");

        stringstream ss;
        calculator.Print("a", ss);
        ASSERT_EQUAL(ss.str(), "nan\n")
    }

    // test func value is 0
    {
        Calculator calculator;
        calculator.Let("a", 0);
        calculator.Function("func", "a", "a", '*');

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "0.00\n")
    }

    // test func value is negative
    {
        Calculator calculator;
        calculator.Let("a", -1);
        calculator.Function("func", "a", "a", '+');

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "-2.00\n")
    }

    // test func value is nan v1: nan as var
    {
        Calculator calculator;
        calculator.Let("a", 0);
        calculator.AddVar("b");
        calculator.Function("func", "a", "b", '*');

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "nan\n")
    }

    // test func value is nan v2: 0/0
    {
        Calculator calculator;
        calculator.Let("a", 0);
        calculator.Function("func", "a", "a", '/');

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "nan\n")
    }

    // test func value is inf
    {
        Calculator calculator;
        calculator.Let("a", 1);
        calculator.Let("b", 0);
        calculator.Function("func", "a", "b", '/');

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "inf\n")
    }

    // test func value is -inf
    {
        Calculator calculator;
        calculator.Let("a", -1);
        calculator.Let("b", 0);
        calculator.Function("func", "a", "b", '/');

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "-inf\n")
    }
}
void TestUpdateCurrentFunctionValues()
{
    // test on no functions
    {
        Calculator calculator;

        stringstream ss;
        calculator.PrintFunctions(ss);
        ASSERT_EQUAL(ss.str(), "")
    }

    // test updated var two types
    {
        Calculator calculator;
        calculator.Let("a", 1);
        calculator.Let("b", 2);
        calculator.Function("fn1", "a");
        calculator.Function("fn2", "a", "b", '+');

        stringstream ss;
        calculator.PrintFunctions(ss);
        ASSERT_EQUAL(ss.str(), "fn1:1.00\nfn2:3.00\n")

        calculator.Let("a", 4);

        stringstream ss1;
        calculator.PrintFunctions(ss1);
        ASSERT_EQUAL(ss1.str(), "fn1:4.00\nfn2:6.00\n")

        calculator.Let("b", 5);

        stringstream ss2;
        calculator.PrintFunctions(ss2);
        ASSERT_EQUAL(ss2.str(), "fn1:4.00\nfn2:9.00\n")
    }

    // test new function two types
    {
        Calculator calculator;
        calculator.Let("a", 1);
        calculator.Let("b", 2);
        calculator.Function("fn1", "a");
        calculator.Function("fn2", "a", "b", '+');

        stringstream ss;
        calculator.PrintFunctions(ss);
        ASSERT_EQUAL(ss.str(), "fn1:1.00\nfn2:3.00\n")

        calculator.Function("fn3", "a");

        stringstream ss1;
        calculator.PrintFunctions(ss1);
        ASSERT_EQUAL(ss1.str(), "fn1:1.00\nfn2:3.00\nfn3:1.00\n")

        calculator.Function("fn4", "a", "b", '-');

        stringstream ss2;
        calculator.PrintFunctions(ss2);
        ASSERT_EQUAL(ss2.str(), "fn1:1.00\nfn2:3.00\nfn3:1.00\nfn4:-1.00\n")
    }
}

void TestAddReferenceToFunction()
{
    // adding reference to var
    {
        Calculator calculator;
        calculator.Let("a", -1);
        calculator.Function("func", "a");

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "-1.00\n")
    }

    // adding reference to func without operation

    {
        Calculator calculator;
        calculator.Let("a", -1);
        calculator.Function("func1", "a");
        calculator.Function("func2", "func1");

        stringstream ss;
        calculator.Print("func2", ss);
        ASSERT_EQUAL(ss.str(), "-1.00\n")
    }
    // adding reference to func with operation

    {
        Calculator calculator;
        calculator.Let("a", -1);
        calculator.Function("func1", "a", "a", '*');
        calculator.Function("func2", "func1");

        stringstream ss;
        calculator.Print("func2", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n")
    }
}

void TestAddReferenceToOperation()
{
    // adding reference to var
    {
        Calculator calculator;
        calculator.Let("a", -1);
        calculator.Function("func", "a", "a", '+');

        stringstream ss;
        calculator.Print("func", ss);
        ASSERT_EQUAL(ss.str(), "-2.00\n")
    }
    // adding reference to func without operation

    {
        Calculator calculator;
        calculator.Let("a", 1);
        calculator.Function("func1", "a");
        calculator.Function("func2", "func1", "a", '+');

        stringstream ss;
        calculator.Print("func2", ss);
        ASSERT_EQUAL(ss.str(), "2.00\n")
    }

    // adding reference to func with operation
    {
        Calculator calculator;
        calculator.Let("a", 1);
        calculator.Function("func1", "a", "a", '+');
        calculator.Function("func2", "a", "a", '*');
        calculator.Function("func3", "func1", "func2", '+');

        stringstream ss;
        calculator.Print("func3", ss);
        ASSERT_EQUAL(ss.str(), "3.00\n")
    }
}
void TestAddLastFunctionValue()
{
    // adding new function type1 value to functionCurrentValue
    {

        Calculator calculator;
        calculator.Let("a", 1);
        calculator.Function("func1", "a");

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "1.00\n")
    }

    // adding new function type2 value to functionCurrentValue
    {
        Calculator calculator;
        calculator.Let("a", 1);
        calculator.Function("func1", "a", "a", '+');

        stringstream ss;
        calculator.Print("func1", ss);
        ASSERT_EQUAL(ss.str(), "2.00\n")
    }
}

void TestCheckIsDeclaredVariable()
{
    // id have not been declared
    try
    {
        Calculator calculator;

        stringstream ss;
        calculator.Print("a", ss);
    }
    catch (const exception& e)
    {
    }

    // id have been declared as variable
    {
        Calculator calculator;
        calculator.AddVar("a");

        stringstream ss;
        calculator.Print("a", ss);
        ASSERT_EQUAL(ss.str(), "nan\n");
    }
}
void TestCheckIsDeclaredFunction()
{
    // share the same tests with
    // id have not been declared
    try
    {
        Calculator calculator;

        stringstream ss;
        calculator.Print("a", ss);
    }
    catch (const exception& e)
    {
    }

    // id have been declared as function
    {
        Calculator calculator;
        calculator.AddVar("a");
        calculator.Function("fn", "a");

        stringstream ss;
        calculator.Print("fn", ss);
        ASSERT_EQUAL(ss.str(), "nan\n");
    }
}
