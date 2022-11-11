#include "notation_reader.h"
#include "move.h"
#include "game_legend.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

NotationReader::NotationReader() {

}

// Reads from File GameLegend.fileAddress_ . Stores to GameLegend.notationLine_
void NotationReader::ReadGameNotationFromFile(GameLegend &gameLegend) {

    std::string line;
    std::string result = "";
    std::string address = gameLegend.GetFileAddress();

    std::ifstream myfile;
    myfile.open(address);
    if (myfile.is_open()) {
        while (std::getline(myfile, line)) {
            result += ' ' + line;
        }
        myfile.close();
    }
    else std::cout << "Error. Input File can not be opened!\n";

    gameLegend.SetNotationLine(result);
}

// Saves notationn to File "output.txt"
void NotationReader::SaveGameNotationToFile(GameLegend gameLegend) {

    std::ofstream myfile;
    myfile.open("output.txt");
    myfile << gameLegend.GetNotationLine();
    myfile.close();
}



