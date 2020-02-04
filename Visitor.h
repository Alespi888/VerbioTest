#ifndef VISITOR_H
#define VISITOR_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Visitor {
public:
	Visitor() : unmodifiedWord_("") {}

    void onLineStart(std::ifstream &inFile, std::string &lineContent);
    void onLineEnd(std::ofstream& outFile);
    void onStartWord(std::string &word, std::istringstream &iss);
    void onWord(std::string &word, std::ofstream& outFile);
    void onSpecialInitCharacter(char specialCharacter);
    void onSpecialLastCharacter(char specialCharacter);
    void onSpecialMiddleCharacter(char specialCharacter);
    void onNumber(unsigned long number);
	void onEnd(std::ofstream& outFile);

private:
	void getLowerCaseWord_(std::string &word);

	void printResults_(std::ofstream& outFile);
	void printInitialCharacters_(std::ofstream& outFile);
	void printNumber_(std::ofstream& outFile);
	void printFinalCharacters_(std::ofstream& outFile);
	void printLastWord_(std::ofstream& outFile);

    std::string unmodifiedWord_;
    std::string lastWord_;

	bool hasSpecialInitCharacter_ = false;
	std::vector<unsigned long> vectorNumbers_;
	std::vector<char> vectorInitChar_;
	std::vector<char> vectorFinalChar_;
	std::vector<char> vectorMiddleChar_;

	bool isNumber_ = false;
};

#endif // VISITOR_H
