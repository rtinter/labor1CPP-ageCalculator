#include "NumDemo.h"
#include "PersonHandler.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char const *argv[]) {

    // Anforderung 1
    std::vector<std::string> vi { createVectorFromArgv(argc, argv)};

    // Anforderung 2
    double stringToDouble { stod(vi[1]) };
    std::cout << "converted string = " << vi[1] << " -> double = " << stringToDouble << std::endl;

    //Anforderung 4
    double squaredArgument { squared(stringToDouble) };
    std::cout << "squared " << stringToDouble << " -> " << squaredArgument << std::endl;

    //Anforderung 5
    int doubleToInt { static_cast<int>(squaredArgument) };
    std::cout << "converted double variable = " << squaredArgument << " -> to int ->  " << doubleToInt
              << std::endl;

    //Anforderung 6
    passByReference(doubleToInt);
    std::cout << "Passed by Reference and added 233 = " << doubleToInt << std::endl;
    int *pass_ptr { &doubleToInt } ;
    passByPointer(pass_ptr);
    std::cout << "Passed by Pointer and added 20 = " << doubleToInt << std::endl;

    //Anforderung 7
    std::cout << doubleToInt << " depicted in hexadezical -> " << std::hex << doubleToInt << std::endl; // Ausgabeformat hexa
    std::cout << std::dec << std::endl; // Ausgabeformat Dez

    //Anfoderung 9
    // Gibt die zu lesende .txt dateipfad zurück
    std::string file { getFilename(vi) };
    std::cout << "Filepath -> " << file << std::endl;

    //input_Person(file);
    //input_Person(file);

    //Anforderung 8
    std::vector<Person> persons { readFileTransformToVector(file)};

    printPersonsInFile(persons);

    return 0;

}
