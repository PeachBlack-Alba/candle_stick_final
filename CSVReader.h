#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>

class CSVReader {
public: 
    CSVReader(const std::string& filename); 
    std::vector<std::vector<std::string>> readCSV();

private: 
    std::string filename; 
};

#endif // CSVREADER_H
