#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor to initialize the filename
CSVReader::CSVReader(const std::string& filename) : filename(filename) {}

// Function to read CSV file and return data as a vector of vector of strings
std::vector<std::vector<std::string>> CSVReader::readCSV() {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> row;
        std::string field;

        while (std::getline(iss, field, ',')) {
            row.push_back(field);
        }

        data.push_back(row);
    }
    
    return data; 
}
