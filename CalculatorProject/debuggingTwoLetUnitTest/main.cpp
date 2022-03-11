#include "calculator.h"
#include "functionreference.h"
#include "parseId.h"
#include "test_runner.h"

#include <iomanip>
#include <iostream>

using namespace std;

void TestAll();

int main()
{
    // uncomment for automatic testing
    TestAll();

    // uncomment for for untying 'cout' with 'cin', faster execution
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    // For immediate output
    setbuf(stdout, NULL);

    Calculator calculator;

    for (string line; getline(cin, line, '\n');)
    {
        istringstream inputStream(line);

        string command;
        inputStream >> command;

        try
        {
            if (command == "var")
            {
                const string id = ParseId(inputStream);
                calculator.AddVar(id);
            }
            else if (command == "let")
            {
                string id1 = ParseId(inputStream);

                // skipping '=' sign
                inputStream.ignore(1);

                if (NextElementIsNumber(inputStream))
                {
                    double value;
                    inputStream >> value;

                    calculator.Let(id1, value);
                }
                else
                {
                    const string id2 = ParseId(inputStream);
                    calculator.Let(id1, id2);
                }
            }
            else if (command == "fn")
            {
                string id1 = ParseId(inputStream);

                // skipping '=' sign
                inputStream.ignore(1);

                string id2 = ParseId(inputStream);

                if (inputStream.eof())
                {
                    calculator.Function(id1, id2);
                }
                else
                {
                    const char operation = inputStream.get();
                    const string id3 = ParseId(inputStream);

                    calculator.Function(id1, id2, id3, operation);
                }
            }
            else if (command == "print")
            {
                const string id = ParseId(inputStream);
                calculator.Print(id, cout);
            }
            else if (command == "printvars")
            {
                calculator.PrintVars(cout);
            }
            else if (command == "printfns")
            {
                calculator.PrintFunctions(cout);
            }
            else
            {
                throw invalid_argument("invalid command name: \"" + command + "\"");
            }
        }
        catch (const exception& e)
        {
            cout << e.what() << '\n';
        }
    }
}

void TestAll()
{
    TestRunner tr;
    // Test FunctionReference
    RUN_TEST(tr, TestFunctionReferenceConstructor);
    RUN_TEST(tr, TestComputeTmpValue);
    RUN_TEST(tr, TestGetValue);

    // Test ParseId
    RUN_TEST(tr, TestRightChar);
    RUN_TEST(tr, TestParseId);
    RUN_TEST(tr, TestNextElementIsNumber);

    // Test Calculator
    RUN_TEST(tr, TestAddVar);
    RUN_TEST(tr, TestLet);
    RUN_TEST(tr, TestFunction);
    RUN_TEST(tr, TestPrint);
    RUN_TEST(tr, TestPrintVars);
    RUN_TEST(tr, TestPrintFunctions);
    RUN_TEST(tr, TestGetIdValue);
    RUN_TEST(tr, TestUpdateCurrentFunctionValues);
    RUN_TEST(tr, TestAddReferenceToFunction);
    RUN_TEST(tr, TestAddReferenceToOperation);
    RUN_TEST(tr, TestAddLastFunctionValue);
    RUN_TEST(tr, TestCheckIsDeclaredVariable);
    RUN_TEST(tr, TestCheckIsDeclaredFunction);
}

/*
Example 1:

var x
print x
let x=42
print x
let x=1.234
print x
let y=x
let x=99
printvars

Expected:
nan
42.00
1.23
x:99.00
y:1.23


Example 2: function declaration

var x
var y
fn XPlusY=x+y
print XPlusY
let x=3
let y=4
print XPlusY
let x=10
print XPlusY
let z=3.5
fn XPlusYDivZ=XPlusY/z
printfns

Expected:
nan
7.00
14.00
XPlusY:14.00
XPlusYDivZ:4.00


Example 3: differences between fn and let

let v=42
let variable=v
fn function=v
let v=43
print variable
print function

Expected:
42.00
43.00


Example 4: curcle area

var radius
let pi=3.14159265
fn radiusSquared=radius*radius
fn circleArea=pi*radiusSquared
let radius=10
print circleArea
let circle10Area=circleArea
let radius=20
let circle20Area=circleArea
printfns
printvars

Expected:
314.16
circleArea:1256.64
radiusSquared:400.00
circle10Area:314.16
circle20Area:1256.64
pi:3.14
radius:20.00

Example 5: fibonaci

let v0=0
let v1=1
fn fib0=v0
fn fib1=v1
fn fib2=fib1+fib0
fn fib3=fib2+fib1
fn fib4=fib3+fib2
fn fib5=fib4+fib3
fn fib6=fib5+fib4
printfns
let v0=1
let v1=1
printfns

Expected:
fib0:0.00
fib1:1.00
fib2:1.00
fib3:2.00
fib4:3.00
fib5:5.00
fib6:8.00
fib0:1.00
fib1:1.00
fib2:2.00
fib3:3.00
fib4:5.00
fib5:8.00
fib6:13.00



Tests:
1)
let x=0
let y=1
fn func=x/y
print func
2)
let x
let x=nan
print x
let x=10
print x
let x=nan
print x

let x=0.1
fn f1=x+x
fn f2=x+f1
fn f3=x+f2
fn f4=x+f3
fn f5=x+f4
fn f6=x+f5
fn f7=x+f6
fn f8=x+f7
fn f9=x+f8

Ok
let x=0.1
fn f1=x+x
fn f2=x+f1
fn f3=x+f2
fn f4=x+f3
fn f5=x+f4
fn f6=x+f5
fn f7=x+f6
fn f8=x+f7
fn f9=x+f8
print f9

let x=1.0
fn func=x+x


*/