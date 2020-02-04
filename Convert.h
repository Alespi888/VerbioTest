#ifndef CONVERT_H
#define CONVERT_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Mapping.h"
#include "Visitor.h"

class Convert {
public:
	Convert();

	void executeConversion(std::ifstream& inFile, std::ofstream& outFile);

private:
	void checkSpecialCharacter_(std::string& word, Visitor& visitor);
	bool checkIsNumber_(std::string& in, Visitor& visitor);
	void callCiclically_(Visitor& visitor, std::ofstream& outFile, std::istringstream& iss);
	bool isException_(std::string& word);
	void checkExtraCharacter_(std::string& word);

	Mapping mapping_;
	bool numberEndWithoutWord_ = false;


	bool hasLastSpecialCharacter_ = false;
	bool isNumber_ = false;
	bool endLine_ = false;
};

#endif // CONVERT_H
