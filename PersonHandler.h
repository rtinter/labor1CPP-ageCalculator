#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <array>


using Person = struct{
    std::string firstName;
    std::string lastName;
    std::string birthday;
    int ageInYears;
    int ageInDays;
    int ageInHours;
};

std::string filename(std::vector<std::string> const &vi);

Person readPerson(std::ifstream &file);

std::vector<Person> readFileTransformToVector(std::string const &filePath);

void input_Person(const std::string &filename);

std::tm parseBirthday(const std::string &birthday);

void calculateAge(Person &person);

void printAgeInWords(int const &age);

void printPersonsInFile(std::vector<Person> const &persons);