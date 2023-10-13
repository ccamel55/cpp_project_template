#include <iostream>
#include <example_class.hpp>

namespace
{
    void some_function()
    {
        std::cout << "5 + 5 = " << example_class::add_int(5, 5) << std::endl;
    }
}

int main()
{
    std::cout << "Hello world!" << std::endl;
    some_function();

    return 0;
}