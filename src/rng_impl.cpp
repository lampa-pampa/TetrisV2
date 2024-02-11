#include "rng_impl.h"
#include <cstdlib>
#include <ctime>

using std::srand;
using std::time;

RNGImpl::RNGImpl()
{
    srand(static_cast<unsigned>(time(NULL)));
}

int RNGImpl::random(int range)
{
	return rand() % range;
}