#include "Vector.h"

namespace
{
	const int8_t SIMBOLS_AFTER_COMMA = 3;
}

void SetRealNumbersTo(std::vector<double>& realNumbers)
{
	std::string lineFromUser;

	std::getline(std::cin, lineFromUser);
	std::istringstream iss(lineFromUser);

	std::string numberString;

	while (iss >> numberString)
	{
		realNumbers.push_back(boost::lexical_cast<double>(numberString));
	}
}

void AddMeanPositiveNumberForAllElementsIn(std::vector<double>& realNumbers)
{
	double numbersPositiveŅount = 0;
	double numbersPositiveSum = 0;
	double arithmeticMeanOfPositiveNumbers = 0;

	std::for_each(realNumbers.begin(), realNumbers.end(),
		[&numbersPositiveŅount, &numbersPositiveSum](double const& number)
		{
			if (number > 0)
			{
				numbersPositiveSum += number;
				numbersPositiveŅount++;
			}
		}
	);

	if (numbersPositiveSum != 0)
	{
		arithmeticMeanOfPositiveNumbers = numbersPositiveSum / numbersPositiveŅount;
	}

	std::for_each(realNumbers.begin(), realNumbers.end(),
		[&arithmeticMeanOfPositiveNumbers](double& number)
		{
			number += arithmeticMeanOfPositiveNumbers;
		}
	);
}

void PrintRealNumbers(std::vector<double>& realNumbers)
{
	std::sort(realNumbers.begin(), realNumbers.end());
	for (auto& number : realNumbers)
	{
		std::cout << std::fixed << std::setprecision(SIMBOLS_AFTER_COMMA) << number << ' ';
	}
}
