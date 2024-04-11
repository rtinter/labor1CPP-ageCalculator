#include "PersonHandler.h"
#include <chrono>

//helpfunction to read a person from file
auto readPerson(std::ifstream &file) {
    Person person;
    std::getline(file, person.firstName);
    std::getline(file, person.lastName);
    std::getline(file, person.birthday);
    return person;
}

//Anforderung 10
std::vector<Person> readFileTransformToVector(std::string const & filePath) {
    std::vector<Person> persons;

    try {
        std::ifstream file(filePath);
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        while (file.peek() != EOF) {
            Person person { readPerson(file) };
            calculateAge(person);
            persons.push_back(person);
        }
    } catch(const std::exception &e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
    return persons;
}

std::string getFilename(const std::vector<std::string>& vi) {
    const std::filesystem::path dirPath = "../";

    if (vi.size() < 3) {
        std::cout << "using dummyfile data.txt - No filename input" << std::endl;
        const std::filesystem::path dummyFilename = dirPath / "data.txt";

        return dummyFilename;
    } else {
        try {
            const std::filesystem::path inputFilename { dirPath / vi[2] };
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
    std::tm tm { {} };
    //Lesen eines Strings mit ss um ihn zuweisen zu können
    std::istringstream ss(birthday);
    ss >> std::get_time(&tm, "%d.%m.%Y");
    return tm;
}

void calculateAge(Person &person) {
    // Parsen des Geburtstags in std::tm
    std::tm birthdateTm { parseBirthday(person.birthday) };

    // Umwandlung von std::tm in time_t -> Aus Datum wird Timepoint = Zeitpunkt in Sekunden
    auto birthdateTp { std::chrono::system_clock::from_time_t(std::mktime(&birthdateTm)) };

    // Aktuelles Datum
    auto now { std::chrono::system_clock::now() };

    // Differenz in Stunden berechnen
    auto hoursDiff  {std::chrono::duration_cast<std::chrono::hours>(now - birthdateTp).count()};

    // Jahre, Tage und Stunden berechnen
    person.ageInYears = hoursDiff / 8760; // Näherung für ein Jahr in Stunden
    person.ageInDays = hoursDiff / 24;
    person.ageInHours = hoursDiff;
}


//----------------Arrays für printAgeInWords--------------------------------
static std::array<std::string const, 20> const tillTwenty { {
    "null", "ein", "zwei", "drei", "vier", "fünf",
    "sechs", "sieben", "acht", "neun", "zehn",
    "elf", "zwölf", "dreizehn", "vierzehn", "fünfzehn",
    "sechzehn", "siebzehn", "achtzehn", "neunzehn"
}};

static std::array<std::string const, 10> const twentyTillHundred { {
    "", "", "zwanzig", "dreißig", "vierzig", "fünfzig",
    "sechzig", "siebzig", "achtzig", "neunzig"
}};
//---------------------------------------------------------------------------

void printAgeInWords(int const &age) {
    std::string ageText;

    if (age < 20) {
        ageText = tillTwenty[age] ;
    } else if (age < 100) {
        int u { age % 10 }; // einer
        int t { age / 10 }; // zehner

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
            int u { remainder % 10 };
            int t { remainder / 10 };
            if (u > 0) {
                ageText = "einhundertund" + tillTwenty[u] + "und" + twentyTillHundred[t];
            } else {
                ageText = "einhundertund" + twentyTillHundred[t];
            }
        }
    }
    std::cout << "Person ist " << ageText << " Jahr(e) alt!" << std::endl;
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