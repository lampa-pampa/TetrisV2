#include "rng_mock.h"
#include <vector>

using std::vector;

RNGMock::RNGMock(vector<int> numbers)
:
    numbers(numbers),
    current_index(0)
{}

int RNGMock::random(int range)
{
    int number = this->numbers[this->current_index];
    this->current_index = (this->current_index + 1) % this->numbers.size();
	return number;
}