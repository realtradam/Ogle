#include "random.hpp"
#include <cstdlib>
namespace Random
{
	int get_value(int min, int max)
	{
		return (std::rand()%(abs(max - min) + 1) + min);
	}
}
