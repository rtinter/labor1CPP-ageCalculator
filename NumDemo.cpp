#include "NumDemo.h"
#include <cmath>

// Anforderung 1
std::vector<std::string> createVectorFromArgv(int const &argc, char const *argv[]){
    std::vector<std::string> vi;

    //Naiv
    for (int i{0}; i < argc; ++i) {
        vi.emplace_back(argv[i]);
    }

    //ranged based loop
    int i {0};
    std::cout << "Displaying the programmarguments:" << std::endl;
    for (const auto &element: vi) { // Referenztyp
        std::cout << "argv[" << i << "] = " << element << std::endl;
        i++;
    }
    std:: cout << std::endl;
    return vi;
}

//Anforderung 2
double squared(double const &b){
    return pow(b,2);
}

void passByReference(int &a){
    a+=233;
}

void passByPointer (int *ptr){
    (*ptr)+=20;
}