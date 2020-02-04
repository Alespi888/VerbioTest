#include "Visitor.h"
#include <algorithm>
#include <iterator>

// -----------------------------------------------------------------------------

void Visitor::onLineStart(std::ifstream &inFile, std::string &lineContent)
{
  	std::getline(inFile, lineContent);
}

// -----------------------------------------------------------------------------

void Visitor::onStartWord(std::string &word, std::istringstream &iss)
{
	iss >> word;
	unmodifiedWord_ = word;
	getLowerCaseWord_(word);
}

// -----------------------------------------------------------------------------

void Visitor::onSpecialInitCharacter(char specialCharacter)
{
	vectorInitChar_.push_back(specialCharacter);
}

// -----------------------------------------------------------------------------

void Visitor::onSpecialLastCharacter(char specialCharacter)
{
	vectorFinalChar_.push_back(specialCharacter);
}


// -----------------------------------------------------------------------------

void Visitor::onNumber(unsigned long number)
{
	isNumber_ = true;
	vectorNumbers_.push_back(number);
}

// -----------------------------------------------------------------------------

void Visitor::onLineEnd(std::ofstream& outFile)
{
	outFile << std::endl;
}

// -----------------------------------------------------------------------------

void Visitor::onWord(std::string &word, std::ofstream& outFile)
{
	lastWord_ = word;
	if (!isNumber_) {
		printResults_(outFile);
	}
}

// -----------------------------------------------------------------------------

void Visitor::onEnd(std::ofstream& outFile)
{
	if (isNumber_)
	printResults_(outFile);
}
//-------------------------------------------------------------------

void Visitor::getLowerCaseWord_(std::string& word)
{
	std::for_each(word.begin(), word.end(), [](char& c) {
		c = tolower(c);});
}

//-------------------------------------------------------------------

void Visitor::printResults_(std::ofstream& outFile)
{
	printInitialCharacters_(outFile);
	if (isNumber_) {
		printNumber_(outFile);
		printFinalCharacters_(outFile);
		printLastWord_(outFile);
		isNumber_ = false;
		vectorInitChar_.clear();
		vectorNumbers_.clear();
		vectorFinalChar_.clear();
	}
	else
	{
		outFile << unmodifiedWord_ << " ";
		lastWord_.clear();
		unmodifiedWord_.clear();
	}

}

//-------------------------------------------------------------------

void Visitor::printNumber_(std::ofstream& outFile)
{
	unsigned long n = 0;
	unsigned long g = 0;
	unsigned long x = 0;
	for (std::vector<unsigned long>::iterator it = vectorNumbers_.begin(); it != vectorNumbers_.end(); it++)
	{
		x = *it;
		if ((x < 100) && (x != 0))
			g += x;
		else if ((x == 100) && (g != 0))
			g *= 100;
		else
		{
			if (x >= 100)
			{
				if (g > 0)
					n += g * x;
				else
					n = x;
				g = 0;
			}
		}
	}
	outFile << (n + g);
}

//-------------------------------------------------------------------

void Visitor::printInitialCharacters_(std::ofstream& outFile) {
	if (!vectorInitChar_.empty() ){
		outFile << vectorInitChar_.back();
		vectorInitChar_.pop_back();
	}
}

//-------------------------------------------------------------------

void Visitor::printFinalCharacters_(std::ofstream& outFile) {
	if (!vectorFinalChar_.empty() ){
		outFile << vectorFinalChar_.back();
		vectorFinalChar_.pop_back();
	}
		outFile << " ";
}

//-------------------------------------------------------------------

void Visitor::printLastWord_(std::ofstream& outFile) {
	if (!lastWord_.empty())
		outFile << lastWord_;
}

//-------------------------------------------------------------------
