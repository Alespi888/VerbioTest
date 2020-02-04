#include <fstream>
#include <iostream>
#include <string>

#include "Convert.h"

namespace
{
    bool checkFilesAreCorrectlyOpened(std::ifstream const &in, std::ofstream const & out)
    {
        if (in.is_open() && out.is_open())
            return true;
        else if (!(in.is_open()))
            std::cout << "Error opening Input file\n";
        else
            std::cout << "Error opening Output file\n";
        return false;
    }
    void closeFiles(std::ifstream& in, std::ofstream& out)
    {
        if (in.is_open())
            in.close();
        if (out.is_open())
            out.close();  
    }
}

int main()
{
    std::cout  << "Convert words in numbers\n";

    std::ifstream inFile("C:\\Temp\\Input.txt");
    std::ofstream outFile("C:\\Temp\\Output.txt");

    if (!checkFilesAreCorrectlyOpened(inFile, outFile)) {
        closeFiles(inFile, outFile);
        return 0;
    }

    Convert convert;
    convert.executeConversion(inFile, outFile);
    
    closeFiles(inFile, outFile);
    std::cout << "Conversion done\n";
    std::cin.get();
    return 0;
}
