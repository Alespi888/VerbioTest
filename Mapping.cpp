#include "Mapping.h"

Mapping::Mapping()
{
	mappValues_();
}

void Mapping::mappValues_() {
	value_["zero"] = 0;
	value_["one"] = 1;
	value_["two"] = 2;
	value_["three"] = 3;
	value_["four"] = 4;
	value_["five"] = 5;
	value_["six"] = 6;
	value_["seven"] = 7;
	value_["eight"] = 8;
	value_["nine"] = 9;
	value_["ten"] = 10;
	value_["eleven"] = 11;
	value_["twelve"] = 12;
	value_["thirteen"] = 13;
	value_["fourteen"] = 14;
	value_["fifteen"] = 15;
	value_["sixteen"] = 16;
	value_["seventeen"] = 17;
	value_["eighteen"] = 18;
	value_["nineteen"] = 19;
	value_["twenty"] = 20;
	value_["thirty"] = 30;
	value_["forty"] = 40;
	value_["fifty"] = 50;
	value_["sixty"] = 60;
	value_["seventy"] = 70;
	value_["eighty"] = 80;
	value_["ninety"] = 90;
	value_["hundred"] = 100;
	value_["thousand"] = 1000;
	value_["million"] = 1000000;
	value_["billion"] = 1000000000;
}

void Mapping::mappSpecialCases_() {
	specialCase_["and"] = 0;
	specialCase_["-"] = 1;
	specialCase_[" "] = 2;
	specialCase_[","] = 3;
}