#include <vector>
#include <iostream>

double squared(double b);

void passByReference(int &a);

void passByPointer (int *ptr);

std::vector<std::string> createVectorFromArgv(int const &argc, char const *argv[]);