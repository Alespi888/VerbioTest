#ifndef MAPPING_H
#define MAPPING_H

#include <string>
#include <map>

class Mapping {
public:
	Mapping();
	std::map<std::string, unsigned long> getMappedValues() { return value_; }
	std::map<std::string, unsigned long> getSpecialCases() { return specialCase_; }

private:
	void mappValues_();
	void mappSpecialCases_();
	std::map<std::string, unsigned long> value_;
	std::map<std::string, unsigned long> specialCase_;
};

#endif // MAPPING_H
