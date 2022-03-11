#include "parseId.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

void TestRightChar()
{
    ASSERT_EQUAL(rightChar('='), false);
    ASSERT_EQUAL(rightChar('+'), false);
    ASSERT_EQUAL(rightChar('-'), false);
    ASSERT_EQUAL(rightChar('*'), false);
    ASSERT_EQUAL(rightChar('/'), false);

    ASSERT_EQUAL(rightChar('_'), true);
    ASSERT_EQUAL(rightChar('1'), true);
    ASSERT_EQUAL(rightChar('a'), true);
}

void TestParseId()
{
    // id as they should be
    {
        string line = "a";
        istringstream inputStream(line);
        ASSERT_EQUAL(ParseId(inputStream), "a");
    }
    {
        string line = "_";
        istringstream inputStream(line);
        ASSERT_EQUAL(ParseId(inputStream), "_");
    }
    {
        string line = "a1";
        istringstream inputStream(line);
        ASSERT_EQUAL(ParseId(inputStream), "a1");
    }
    {
        string line = "_1";
        istringstream inputStream(line);
        ASSERT_EQUAL(ParseId(inputStream), "_1");
    }
    // whitespace before id
    {
        string line = " a";
        istringstream inputStream(line);
        ASSERT_EQUAL(ParseId(inputStream), "a");
    }
    // until stop symboles, if one works the rest of symbols work  as well
    {
        string line = "a+";
        istringstream inputStream(line);
        ASSERT_EQUAL(ParseId(inputStream), "a");
    }
}

void TestNextElementIsNumber()
{
    {
        string line = "a";
        istringstream inputStream(line);
        ASSERT_EQUAL(NextElementIsNumber(inputStream), false);
    }
    {
        string line = "_";
        istringstream inputStream(line);
        ASSERT_EQUAL(NextElementIsNumber(inputStream), false);
    }
    {
        string line = "1";
        istringstream inputStream(line);
        ASSERT_EQUAL(NextElementIsNumber(inputStream), true);
    }
    {
        string line = "0";
        istringstream inputStream(line);
        ASSERT_EQUAL(NextElementIsNumber(inputStream), true);
    }
    {
        string line = "-";
        istringstream inputStream(line);
        ASSERT_EQUAL(NextElementIsNumber(inputStream), true);
    }
}
