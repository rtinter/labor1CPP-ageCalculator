#include "PersonHandler.h"
#include <chrono>

//helpfunction to read a person from file
Person readPerson(std::ifstream &file) {
    Person person;
    std::getline(file, person.firstName);
    std::getline(file, person.lastName);
    std::getline(file, person.birthday);
    return person;
}

std::vector<Person> readFileTransformToVector(std::string const &filename) {
    std::ifstream file(filename);
    std::vector<Person> persons;

    try {
        if (!file) {
            throw std::runtime_error("Error occurred while trying to read: " + filename);
        }

        file.exceptions(std::ifstream::badbit);

        while (!file.eof()) {
            Person person = readPerson(file);
            calculateAge(person);
            persons.push_back(person);
        }
    } catch(const std::exception &e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }


    return persons;
}
//todo Hier wird noch die alte datei überschrieben wenn sie bereits exisiert -> Datenverlust im vorhandenen file
std::string filename(const std::vector<std::string>& vi) {
    const std::filesystem::path dirPath = "../";

    if (vi.size() < 3) {
        std::cout << "using dummyfile data.txt - No filename input" << std::endl;
        const std::filesystem::path dummyFilename = dirPath / "data.txt";

        return dummyFilename;
    } else {
        try {
            const std::filesystem::path inputFilename = dirPath / vi[2];
            std::ofstream file(inputFilename);
            std::cout << "File created: " << inputFilename << std::endl;
            return inputFilename;
        } catch (const std::exception &e) {
            std::cerr << "Error while trying to create the file: " << e.what() << std::endl;
        }
    }
    return "";
}

void input_Person(std::string const &file){
    Person person;
    std::cout << "Firstname: " << std::endl;
    std::cin >> person.firstName;
    std::cout << "Lastname: " << std::endl;
    std::cin >> person.lastName;
    std::cout << "Birthday: " << std::endl;
    std::cin >> person.birthday;
    try {
        std::ofstream inputFile(file, std::ios::app); // hinten anfügen durch ios::app
        if (inputFile.is_open()) {
            // Direktes schreiben IN den stream mit <<
            inputFile << person.firstName << std::endl;
            inputFile << person.lastName << std::endl;
            inputFile << person.birthday << std::endl;
            std::cout << "Person data saved to " << file << std::endl;
        } else {
            // Wirf eine Ausnahme, wenn die Datei nicht geöffnet werden konnte
            throw std::runtime_error("Could not open file");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


// Hilfsfunktion, um ein Datum vom String in ein std::tm zu konvertieren
std::tm parseBirthday(const std::string& birthday) {
    std::tm tm = {};
    std::istringstream ss(birthday);
    ss >> std::get_time(&tm, "%d.%m.%Y");
    return tm;
}

void calculateAge(Person &person) {
    std::tm birthdateTm = parseBirthday(person.birthday);
    auto birthdateTp = std::chrono::system_clock::from_time_t(std::mktime(&birthdateTm));

    auto now = std::chrono::system_clock::now();
    auto ageDuration = now - birthdateTp;

    auto years = std::chrono::duration_cast<std::chrono::hours>(ageDuration).count() / 8760; // Näherung: 365 Tage * 24 Stunden
    auto days = std::chrono::duration_cast<std::chrono::hours>(ageDuration).count() / 24;
    auto hours = std::chrono::duration_cast<std::chrono::hours>(ageDuration).count();

    person.ageInYears = years;
    person.ageInDays = days;
    person.ageInHours = hours;
}


void printAgeInWords(int const &age) {
    std::string ageText;

    std::array<std::string const, 20> const tillTwenty = {
            "null", "ein", "zwei", "drei", "vier", "fünf",
            "sechs", "sieben", "acht", "neun", "zehn",
            "elf", "zwölf", "dreizehn", "vierzehn", "fünfzehn",
            "sechzehn", "siebzehn", "achtzehn", "neunzehn"
    };

    std::array<std::string const, 10> const twentyTillHundred = {
            "", "", "zwanzig", "dreißig", "vierzig", "fünfzig",
            "sechzig", "siebzig", "achtzig", "neunzig"
    };

    if (age < 20) {
        ageText = tillTwenty[age];
    } else if (age < 100) {
        int u = age % 10; // einer
        int t = age / 10; // zehner

        if (u > 0) {
            ageText = tillTwenty[u] + "und" + twentyTillHundred[t];
        } else {
            ageText = twentyTillHundred[t];
        }
    } else if (age == 100) {
        ageText = "einhundert";
    } else if (age < 200) {
        int remainder = age - 100;
        if (remainder < 20) {
            ageText = "einhundertund" + tillTwenty[remainder];
        } else {
            int u = remainder % 10;
            int t = remainder / 10;
            if (u > 0) {
                ageText = "einhundertund" + tillTwenty[u] + "und" + twentyTillHundred[t];
            } else {
                ageText = "einhundertund" + twentyTillHundred[t];
            }
        }
    } else if (age == 200) {
        ageText = "zweihundert";
    }

    std::cout << "Person ist " << ageText << " Jahre alt!" << std::endl;
}

void printPersonsInFile(std::vector<Person> const &persons) {
    for (const auto &person : persons) {
        if (!person.firstName.empty() && !person.lastName.empty() && !person.birthday.empty()) {
            std::cout << person.firstName << " " << person.lastName << " " << person.birthday;
            std::cout << " " << person.ageInYears << " Jahre Alt, das sind"
                          << " " << person.ageInDays << " Tage und "
                          << " " << person.ageInHours << " Stunden! ";
            printAgeInWords(person.ageInYears);
  
            std::cout << std::endl;
        }
    }
}