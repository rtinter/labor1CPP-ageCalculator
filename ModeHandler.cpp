#include "ModeHandler.h"
#include <iostream>

int modeHandler() {
    int mode = -1;
    int input = -1;

    while(true) {
        std::cout << "Type [0] for the number manipulation demo" << std::endl
                  << "Type [1] for the light db and age calculator "<< std::endl
                  << "Type [2] to exit" << std::endl
                  << "Select an option: ";
        std::cin >> mode;

        if(mode == 1){
            while(true) {
                std::cout << "Type [0] to provide a new person" << std::endl
                          << "Type [1] to read the file "<< std::endl
                          << "Type [2] to go back to the previous menu" << std::endl;
                std::cin >> input;

                if(input == 0) {
                    // Hier kannst du die Logik für das Hinzufügen einer neuen Person implementieren
                    std::cout << "New person added." << std::endl;
                } else if(input == 1) {
                    // Hier kannst du die Logik für das Lesen der Datei implementieren
                    std::cout << "Reading file..." << std::endl;
                } else if(input == 2) {
                    break; // Gehe zurück zum vorherigen Menü
                } else {
                    std::cout << "Invalid input. Please try again." << std::endl;
                }
            }
        } else if(mode == 2) {
            break; // Beenden
        } else if(mode == 0) {
            // Hier kannst du die Logik für die Zahlmanipulationsdemo implementieren
            std::cout << "Number manipulation demo selected." << std::endl;
            break; // Beenden, da wir keine weitere Menüebene haben
        } else {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
    return mode;
}
