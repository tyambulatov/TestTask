#include "calculator.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <unordered_map>

using namespace std;

void Calculator::AddVar(const string& varId)
{
    // Check if varId was declared -> error
    if (CheckIsDeclaredVariable(varId) || CheckIsDeclaredFunction(varId))
    {
        throw invalid_argument("Identificator: \"" + varId + "\" is already declared");
    }
    variableToValue[varId] = NAN;
    variableSortedNames.insert(varId);
}

void Calculator::Let(const string& id1, const double& id2)
{
    // Check if variable id1 was declared as a function-> error
    if (CheckIsDeclaredFunction(id1))
    {
        throw invalid_argument("Identificator 1: \"" + id1 + "\" is already declared");
    }

    variableToValue[id1] = id2;

    variableSortedNames.insert(id1);

    UpdateCurrentFunctionValues();
}

void Calculator::Let(const string& id1, const string& id2)
{
    // Check if variable id1 was declared as a function-> error
    if (CheckIsDeclaredFunction(id1))
    {
        throw invalid_argument("Identificator 1: \"" + id1 + "\" is already declared");
    }

    // Check if id2 was not declared -> error
    if (!CheckIsDeclaredVariable(id2) && !CheckIsDeclaredFunction(id2))
    {
        throw invalid_argument("Identificator 2: \"" + id2 + "\" have not been declared");
    }

    variableToValue[id1] = GetIdValue(id2);

    variableSortedNames.insert(id1);

    UpdateCurrentFunctionValues();
}

void Calculator::Print(const string& id, ostream& os) const
{
    double ans;
    if (CheckIsDeclaredVariable(id))
    {
        ans = variableToValue.at(id);
    }
    else if (CheckIsDeclaredFunction(id))
    {
        ans = functionCurrentValue.at(id);
    }
    else
    {
        throw invalid_argument("Identificator: \"" + id + "\" have not been declared");
    }

    os << fixed << setprecision(2) << ans << '\n';
}

void Calculator::PrintVars(ostream& os) const
{
    for (const string& varId : variableSortedNames)
    {
        os << varId << ":"
           << fixed << setprecision(2)
           << variableToValue.at(varId) << '\n';
    }
}

void Calculator::PrintFunctions(ostream& os) const
{
    for (const string& functionId : functionSortedIdentifications)
    {
        os << functionId << ":"
           << fixed << setprecision(2)
           << functionCurrentValue.at(functionId) << '\n';
    }
}

double Calculator::GetIdValue(const string& id)
{
    if (CheckIsDeclaredVariable(id))
    {
        return variableToValue.at(id);
    }

    return functionCurrentValue.at(id);
}

void Calculator::UpdateCurrentFunctionValues()
{
    for (const string& functionId : functionDeclarationOrder)
    {
        AddLastFunctionValue(functionId);
    }
}

void Calculator::AddReferenceToFunction(const string& functionId, const string& id)
{
    functionToReference.insert(make_pair(functionId, make_shared<FunctionReferenceId>(id)));
}

void Calculator::AddReferenceToOperation(const string& functionId, const string& id2, const string& id3, const char& operation)
{
    functionToReference.insert(make_pair(functionId, make_shared<FunctionReferenceOperation>(id2, id3, operation)));
}

void Calculator::AddLastFunctionValue(const string& functionId)
{
    // We apply fully virtual method ComputeTmpValue to derived class of FunctionReference
    functionCurrentValue[functionId] = functionToReference.at(functionId)->ComputeTmpValue(variableToValue, functionCurrentValue);
}

bool Calculator::CheckIsDeclaredVariable(const string& id) const
{
    return (variableToValue.count(id) == 1) ? true : false;
}

bool Calculator::CheckIsDeclaredFunction(const string& id) const
{
    return (functionCurrentValue.count(id) == 1) ? true : false;
}
