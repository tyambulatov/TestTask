#pragma once

#include <iostream>
#include <string>

using namespace std;

bool rightChar(const char& symbol);

string ParseId(istream& inputStream);

bool NextElementIsNumber(istream& inputStream);

void TestRightChar();
void TestParseId();
void TestNextElementIsNumber();
