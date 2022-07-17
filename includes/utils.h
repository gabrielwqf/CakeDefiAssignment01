#ifndef UTILS_H
#define UTILS_H

#include "common_header.h"

std::vector<std::string> vSplitStringFromCin();
std::vector<std::string> vSplitString(const std::string& ksInput, char cDelimiter);
bool bCheckFloatOrIntegerInString(const std::string& ksInput);
bool bCheckIntegerInString(const std::string& ksInput);
void RoundDownAndPrintSALE(const BigFloat &fSALE, int iDecimalPlaces);

#endif