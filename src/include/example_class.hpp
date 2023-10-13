#pragma once

#include <cstdint>
#include <iostream>

class example_class
{
public:
    example_class()
    {
        std::cout << "class constructed" << std::endl;
    }

    ~example_class()
    {
        std::cout << "class destroyed" << std::endl;
    }

public:
    static int32_t add_int(int a, int b)
    {
        return a + b;
    }

};