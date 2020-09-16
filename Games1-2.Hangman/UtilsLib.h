#include <vector>
#include <string>
#include <cctype> // Used in inputValidatorPhrase
#include <iostream>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
T inputValidator();
template <typename T>
T inputValidator(const unsigned&);
template <typename T>
T inputValidatorSpecific(const std::vector<T>&);
template <typename T>
T inputValidatorSpecificValueAndLength(const std::vector<T>&, const unsigned&);

char inputValidatorLetter();
std::string inputValidatorPhrase(); // Read a sentence from user (only letters and white spaces). Returns lower case sentence#pragma once
