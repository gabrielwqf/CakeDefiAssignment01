#include "../includes/inputcheck.h"
#include "../includes/utils.h"
#include "../includes/start.h"
#include "../includes/APIhandler.h"

using namespace std;

#define CURRENCY_THAT_SALE_IS_USING "ETH"

BigFloat fGetPriceInFirstLine(const string& ksFirstLine, const string ksCurrency);
BigFloat fGetSALEQuantity(BigFloat fCurrencyUsed, BigFloat fETHSALE, const sCases& Case);

int start_program()
{
    //verify input
    vector<string> vInputStrings = vSplitStringFromCin();
    if(!bCheckInput(vInputStrings))
    {
        return -1;
    }
    
    if(vInputStrings[0] == "CURRENT")
    {
        vInputStrings[0] = getLivePriceForFirstLine();
        if(vInputStrings[0] == "")
            return -1;

        cout << "CURRENT PRICES: " << vInputStrings[0] << "\n";
    }

    for(int i = 1; i < vInputStrings.size(); i++)
    {
        const sCases Case = SGetCasesFromLine(vInputStrings[i]);

        BigFloat fCurrencyUsed = fGetPriceInFirstLine(vInputStrings[0],Case.sPurchaseCurrency);
        BigFloat fETHSALE = fGetPriceInFirstLine(vInputStrings[0],CURRENCY_THAT_SALE_IS_USING);

        if(fCurrencyUsed == 0 || fETHSALE == 0)
        {
            cout << "Error: Could not find price for " << Case.sPurchaseCurrency << "\n";
            return -1;
        }
        //round down
        RoundDownAndPrintSALE(fGetSALEQuantity(fCurrencyUsed, fETHSALE, Case), 
                                                Case.iSaledecimalplaces);
    }

    return 0;
}

BigFloat fGetSALEQuantity(BigFloat fCurrencyUsed, BigFloat fETHSALE, const sCases& Case)
{
    BigFloat fConversionToEth = fCurrencyUsed / fETHSALE;
    //get amount of ETH can buy with purchase amount
    BigFloat fAmountOfEthCanBuy = Case.fPurchaseAmt * fConversionToEth;
    //then get the amount of SALE you can purchase
    BigFloat fAmountOfSALECanBuy = fAmountOfEthCanBuy * Case.fETHSALE;
    //round down
    return fAmountOfSALECanBuy;
}

BigFloat fGetPriceInFirstLine(const string& ksFirstLine, const string ksCurrency)
{
    const vector<string> vSplitFirstLine = vSplitString(ksFirstLine, ' ');
    if(ksCurrency == "BTC")
    {
        return BigFloat(vSplitFirstLine[idx_BTCUSD]);
    }
    else if(ksCurrency == "ETH")
    {
        return BigFloat(vSplitFirstLine[idx_ETHUSD]);
    }
    else if(ksCurrency == "DOGE")
    {
        return BigFloat(vSplitFirstLine[idx_DOGEUSD]);
    }

    return 0;
}



