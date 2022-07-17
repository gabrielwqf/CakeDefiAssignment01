#include "../includes/inputcheck.h"
#include "../includes/utils.h"
using namespace std;

#define FIRST_LINE_EXPECTED_INPUT "First line: <BTCUSD rate> <ETHUSD rate> <DOGEUSD rate>"
#define SECOND_LINE_EXPECTED_INPUT "Subsequent lines: <ETHSALE rate> <SALE decimal places> <Purchase currency> <BTC/ETH/DOGE purchase amount>"

enum eInputStandaloneCase
{
    ETHSALE = 0,
    SALEDECIMALPLACES,
    PURCHASE_CURRENCY,
    PURCHASE_AMOUNT
};

bool bFirstLineCheck(const string& ksFirstline);
bool bSubsequentLineCheck(const string& ksSubsequentLine);

bool bCheckInput(const vector<string>& sInput)
{
    if(sInput.size() == 0 || sInput.size() == 1)
    {
        cout << FIRST_LINE_EXPECTED_INPUT << "\n" \
             << SECOND_LINE_EXPECTED_INPUT << "\n";

        return false;
    }

    if(sInput.size() >= 2)
    {
        if(!bFirstLineCheck(sInput[0]))
        {
            return false;
        }

        for(int i = 1; i < sInput.size(); i++)
        {
            if(!bSubsequentLineCheck(sInput[i]))
            {
                return false;
            }
        }
    }

    return true;


}

bool bFirstLineCheck(const string& ksFirstline)
{
    //split firstline by space and check if it contains 3 elements
    const vector<string> vSplitFirstLine = vSplitString(ksFirstline, ' ');

    if(vSplitFirstLine.size() != 3)
    {
        if(vSplitFirstLine.size() == 1 && vSplitFirstLine[0] == "CURRENT")
        {
            return true;
        }

        cout << FIRST_LINE_EXPECTED_INPUT << "\n";
        return false;
    }
    else
    {
        //check if BTCUSD rate, ETHUSD rate, and DOGEUSD rate are floats
        for(int i = 0; i < 3; i++)
        {
            if(!bCheckFloatOrIntegerInString(vSplitFirstLine[i]))
            {
                cout << FIRST_LINE_EXPECTED_INPUT << " in non-negative float or integer only.\n";
                return false;
            }
        }
    }
    return true;
}

bool bSubsequentLineCheck(const string& ksSubsequentLine)
{
    const vector<string> vSplitSecondLine = vSplitString(ksSubsequentLine, ' ');
    if(vSplitSecondLine.size() != 4)
    {
        cout << SECOND_LINE_EXPECTED_INPUT << "\n";
        return false;
    }
    else
    {
        //check if ETHSALE rate is a float or integer only
        if(!bCheckFloatOrIntegerInString(vSplitSecondLine[eInputStandaloneCase::ETHSALE]))
        {
            cout << "<ETHSALE rate> should be in non-negative integer or floats.\n";
            return false;
        }
        //check if SALE decimal places is an integer
        if(!bCheckIntegerInString(vSplitSecondLine[eInputStandaloneCase::SALEDECIMALPLACES]))
        {
            cout << "<SALE decimal places> must be an integer.\n";
            return false;
        }
        //check if Purchase currency is either BTC, ETH, or DOGE
        if(vSplitSecondLine[eInputStandaloneCase::PURCHASE_CURRENCY] != "BTC" 
        && vSplitSecondLine[eInputStandaloneCase::PURCHASE_CURRENCY] != "ETH" 
        && vSplitSecondLine[eInputStandaloneCase::PURCHASE_CURRENCY] != "DOGE")
        {
            cout << "<Purchase currency> is BTC, ETH or DOGE only\n";
            return false;
        }
        //check if BTC/ETH/DOGE purchase amount is a float
        if(!bCheckFloatOrIntegerInString(vSplitSecondLine[eInputStandaloneCase::PURCHASE_AMOUNT]))
        {
            cout << "<BTC/ETH/DOGE purchase amount> must be in non-negative integer or decimal points.\n";
            return false;
        }
    }
    return true;
}

sCases SGetCasesFromLine(const std::string& ksCase)
{
    std::vector<string> sCasesSplit = vSplitString(ksCase, ' ');

    return sCases(
        sCasesSplit[eInputStandaloneCase::ETHSALE],
        stoi(sCasesSplit[eInputStandaloneCase::SALEDECIMALPLACES]),
        sCasesSplit[eInputStandaloneCase::PURCHASE_CURRENCY],
        sCasesSplit[eInputStandaloneCase::PURCHASE_AMOUNT]);
}