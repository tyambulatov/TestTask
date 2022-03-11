#pragma once

#include "functionreference.h"

#include <set>
#include <unordered_map>
#include <vector>

#include <memory>

using namespace std;

class Calculator
{
public:
    void AddVar(const string& varId);

    void Let(const string& id1, const double& id2);

    void Let(const string& id1, const string& id2);

    void Function(const string& id1, const string& id2, const string& id3 = "", const char& operation = '?')
    {
        // Check if id1 was declared -> error
        if (CheckIsDeclaredVariable(id1) || CheckIsDeclaredFunction(id1))
        {
            throw invalid_argument("Identificator 1: \"" + id1 + "\" is already declared");
        }

        // Check if id2 was not declared -> error
        if (!CheckIsDeclaredVariable(id2) && !CheckIsDeclaredFunction(id2))
        {
            throw invalid_argument("Identificator 2: \"" + id2 + "\" have not been declared");
        }

        // Check if it is a first option of function, without operation
        if (id3.size() == 0)
        {
            AddReferenceToFunction(id1, id2);
        }
        else
        {
            // Check if id3 was not declared -> error
            if (!CheckIsDeclaredVariable(id3) && !CheckIsDeclaredFunction(id3))
            {
                throw invalid_argument("Identificator 3: \"" + id3 + "\" have not been declared");
            }

            AddReferenceToOperation(id1, id2, id3, operation);
        }

        functionSortedIdentifications.insert(id1);
        functionDeclarationOrder.push_back(id1);

        // Adding function value to functionCurrentValue
        AddLastFunctionValue(id1);
    }

    void Print(const string& id, ostream& os) const;

    void PrintVars(ostream& os) const;

    void PrintFunctions(ostream& os) const;

private:
    unordered_map<string, double> variableToValue;
    set<string> variableSortedNames;

    set<string> functionSortedIdentifications;
    unordered_map<string, shared_ptr<FunctionReference>> functionToReference;
    vector<string> functionDeclarationOrder;

    unordered_map<string, double> functionCurrentValue;

    double GetIdValue(const string& id);

    void UpdateCurrentFunctionValues();

    void AddReferenceToFunction(const string& functionId, const string& id);

    void AddReferenceToOperation(const string& functionId, const string& id2, const string& id3, const char& operation);

    void AddLastFunctionValue(const string& functionId);

    bool CheckIsDeclaredVariable(const string& id) const;

    bool CheckIsDeclaredFunction(const string& id) const;
};

void TestAddVar();
void TestLet();
void TestFunction();
void TestPrint();
void TestPrintVars();
void TestPrintFunctions();
void TestGetIdValue();
void TestUpdateCurrentFunctionValues();
void TestAddReferenceToFunction();
void TestAddReferenceToOperation();
void TestAddLastFunctionValue();
void TestCheckIsDeclaredVariable();
void TestCheckIsDeclaredFunction();
