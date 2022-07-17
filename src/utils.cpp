#include "../includes/utils.h"

using namespace std;

vector<string> vSplitStringFromCin()
{
    vector<string> vSplit;
    // get all lines from cin and push to vector per line
    string sLine;
    while (getline(cin, sLine))
    {
        vSplit.push_back(sLine);
    }

    return vSplit;
}

vector<string> vSplitString(const std::string &ksInput, char cDelimiter)
{
    vector<string> vSplit;
    // split string by delimiter and push to vector
    string sToken;
    stringstream ss(ksInput);
    while (getline(ss, sToken, cDelimiter))
    {
        vSplit.push_back(sToken);
    }

    return vSplit;
}

bool bCheckFloatOrIntegerInString(const string &ksInput)
{
    // check if string contains only numbers and a decimal point
    for (int i = 0; i < ksInput.length(); i++)
    {
        if (!(ksInput[i] >= '0' && ksInput[i] <= '9') && ksInput[i] != '.')
        {
            return false;
        }
        if (ksInput[i] == '.')
        {
            // check if decimal point is not the last character
            if (i == ksInput.length() - 1)
            {
                return false;
            }
            // check if decimal point is not the first character
            if (i == 0)
            {
                return false;
            }

        }
    }
    return true;
}

bool bCheckIntegerInString(const string &ksInput)
{
    for (const char &c : ksInput)
    {
        if (!(c >= '0' && c <= '9'))
        {
            return false;
        }
    }

    return true;
}

BigFloat round_down(BigFloat in, int precision){
   return floor(in*pow(10,precision))/pow(10,precision);              
}

void RoundDownAndPrintSALE(const BigFloat &fSALE, int iDecimalPlaces)
{
   
    std::cout << std::fixed 
              << std::setprecision(iDecimalPlaces) 
              << round_down(fSALE,iDecimalPlaces)
              << "\n";


}

