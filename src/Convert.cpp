#include "Convert.h"
#include "Visitor.h"
#include <sstream>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>

Convert::Convert() : mapping_()
{
}

//------------------------------------------------------------------

void Convert::executeConversion(std::ifstream& inFile, std::ofstream& outFile)
{
	Visitor visitor;
	while (!inFile.eof())
	{
		endLine_ = false;
		std::string lineContent;
		visitor.onLineStart(inFile, lineContent);
		std::istringstream iss(lineContent);
		if (lineContent.length())
		{
			while (!endLine_)
			{
				callCiclically_(visitor, outFile, iss);
				visitor.onEnd(outFile);
				endLine_ = true;
				hasLastSpecialCharacter_ = false;
				visitor.onLineEnd(outFile);
			}
		}
		else
			visitor.onLineEnd(outFile);

	}
}

//-------------------------------------------------------------------

bool Convert::checkIsNumber_(std::string& word, Visitor& visitor)
{
	if (!word.empty()) {
		auto values = mapping_.getMappedValues();
		std::map<std::string, unsigned long>::iterator itr;
		itr = values.find(word);
		if (itr != values.end()) {
			visitor.onNumber(itr->second);
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------

void Convert::callCiclically_(Visitor& visitor, std::ofstream& outFile, std::istringstream& iss)
{
	std::string word;
	visitor.onStartWord(word, iss);
	hasLastSpecialCharacter_ = false;
	if (!word.empty()) {
		checkSpecialCharacter_(word, visitor);
		if (checkIsNumber_(word, visitor)) {
			isNumber_ = true;
			if (hasLastSpecialCharacter_) {
				visitor.onEnd(outFile);
				hasLastSpecialCharacter_ = false;
			}
			callCiclically_(visitor, outFile, iss);

		}
		else {
			if (isException_(word))
			{
				callCiclically_(visitor, outFile, iss);
			}
			else
			{
				visitor.onWord(word, outFile);
				callCiclically_(visitor, outFile, iss);
			}
		}
	}
}

//-------------------------------------------------------------------

bool Convert::isException_(std::string& word)
{
	if (((word.compare("and") == 0)) && (isNumber_))
		return true;
	else
		return false;
}


//-------------------------------------------------------------------
void Convert::checkSpecialCharacter_(std::string& word, Visitor& visitor)
{
	std::size_t found = word.find_first_not_of("abcdefghijklmnopqrstuvwxyz");
	if (found == 0)
	{
		if (word.length() != 1){
			visitor.onSpecialInitCharacter(word[found]);
		}
		word.erase(0, 1);
		checkSpecialCharacter_(word, visitor);
	}
	if (!word.empty()) {
		if ((found == word.length() - 1) && (found != 0))
		{
			visitor.onSpecialLastCharacter(word[found]);
			hasLastSpecialCharacter_ = true;
			word.pop_back();
			checkSpecialCharacter_(word, visitor);
		}
	}
	if (found == std::string::npos)
	{
		return;
	}
}
