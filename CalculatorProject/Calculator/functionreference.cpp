#include "functionreference.h"

#include <cmath>
#include <unordered_map>

using namespace std;

double FunctionReference::getValue(const string& id1,
                                   const unordered_map<string, double>& variableToValue,
                                   const unordered_map<string, double>& functionCurrentValue) const
{
    // if id1 is a variable
    if (variableToValue.count(id1) == 1)
    {
        return variableToValue.at(id1);
    }
    else if (functionCurrentValue.count(id1) == 1)
    {
        // all functions values should be computed by this point
        return functionCurrentValue.at(id1);
    }
    else
    {
        throw invalid_argument("getValue: id does not have a value");
    }
}

double FunctionReferenceId::ComputeTmpValue(const unordered_map<string, double>& variableToValue,
                                            const unordered_map<string, double>& functionCurrentValue) const
{
    return getValue(id1_, variableToValue, functionCurrentValue);
}

double FunctionReferenceOperation::ComputeTmpValue(const unordered_map<string, double>& variableToValue,
                                                   const unordered_map<string, double>& functionCurrentValue) const
{
    double lhs = getValue(id1_, variableToValue, functionCurrentValue);
    double rhs = getValue(id2_, variableToValue, functionCurrentValue);

    if (lhs == NAN || rhs == NAN)
    {
        return NAN;
    }

    switch (operation_)
    {
    case '+':
        return lhs + rhs;
        break;

    case '-':
        return lhs - rhs;
        break;

    case '*':
        return lhs * rhs;
        break;

    case '/':
    {
        // catching the 0/0 situation
        if (lhs == 0.0 && rhs == 0.0)
        {
            return NAN;
        }
        return lhs / rhs;
    }
    break;

    default:
        throw invalid_argument("FunctionReferenceOperation::ComputeTmpValue: Invalid function operation value");
        break;
    }
}