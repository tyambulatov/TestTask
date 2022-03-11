#include "parseId.h"

#include <iomanip>
#include <iostream>
#include <set>

using namespace std;

bool rightChar(const char& symbol)
{
    set<char> stopSymbols = {'=', '+', '-', '*', '/'};
    size_t numOfBannedSymbols = stopSymbols.size();

    stopSymbols.insert(symbol);

    return (stopSymbols.size() > numOfBannedSymbols) ? true : false;
}

string ParseId(istream& inputStream)
{
    // skipping the whitespace before id if it is present
    char probableWhitespace = inputStream.peek();
    if (probableWhitespace == ' ')
    {
        inputStream.ignore(1);
    }

    string varId = {};
    while (rightChar(inputStream.peek()) && !inputStream.eof())
    {
        varId += inputStream.get();
    }

    return varId;
}

bool NextElementIsNumber(istream& inputStream)
{
    return (isdigit(inputStream.peek()) || inputStream.peek() == '-') ? true : false;
}