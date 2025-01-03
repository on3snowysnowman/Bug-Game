
#include <iostream>

#include "NameGenerators.hpp"

int main()
{
    for(int i = 0; i < 10; ++i)
    {
        std::cout << NameGenerators::generate_planet_name() << '\n';
    }

    return 0;
}