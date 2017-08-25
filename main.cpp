#include <iostream>
#include "headers/application.hpp"
#include "headers/displaymanager.hpp"


int main()
{
    DisplayManager dm(std::cout);
    dm << "test";
    dm << "test";

    return 0;
}
