#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

#include <boost/lexical_cast.hpp>

void SetRealNumbersTo(std::vector<double>& realNumbers);

void GetSumAndCountPositiveNumbers(std::vector<double> const& realNumbers, double& numbersPositiveŅount, double& numbersPositiveSum);

void AddNumberForAllElementsIn(std::vector<double>& realNumbers, double& numbersPositiveŅount);

void AddAveragePositiveNumberForAllElementsIn(std::vector<double>& realNumbers);

void PrintRealNumbers(std::vector<double>& realNumbers);