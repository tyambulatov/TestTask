#pragma once

#include <cmath>
#include <unordered_map>

using namespace std;

class FunctionReference
{
public:
    FunctionReference(const string& id1) : id1_(id1) {}

    virtual double ComputeTmpValue(const unordered_map<string, double>& variableToValue,
                                   const unordered_map<string, double>& functionCurrentValue) const = 0;

protected:
    const string id1_;

    double getValue(const string& id1,
                    const unordered_map<string, double>& variableToValue,
                    const unordered_map<string, double>& functionCurrentValue) const;
};

class FunctionReferenceId : public FunctionReference
{
public:
    FunctionReferenceId(const string& id1)
        : FunctionReference(id1) {}

    double ComputeTmpValue(const unordered_map<string, double>& variableToValue,
                           const unordered_map<string, double>& functionCurrentValue) const override;
};

class FunctionReferenceOperation : public FunctionReference
{
public:
    FunctionReferenceOperation(const string& id1,
                               const string& id2,
                               const char& operation) : FunctionReference(id1),
                                                        id2_(id2),
                                                        operation_(operation) {}

    double ComputeTmpValue(const unordered_map<string, double>& variableToValue,
                           const unordered_map<string, double>& functionCurrentValue) const override;

protected:
    const string id2_;
    const char operation_;
};

void TestFunctionReferenceConstructor();
void TestComputeTmpValue();
void TestGetValue();
