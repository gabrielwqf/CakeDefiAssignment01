#ifndef INPUT_CHECK
#define INPUT_CHECK

#include "common_header.h"

struct sCases
{
    sCases(std::string sFloatEthSale, int NoOfSaleDecimalPlaces, std::string purchaseCurr, std::string purchaseAmount):
        fETHSALE(sFloatEthSale),
        iSaledecimalplaces(NoOfSaleDecimalPlaces),
        sPurchaseCurrency(purchaseCurr),
        fPurchaseAmt(purchaseAmount)
    {}

    BigFloat fETHSALE;
    int iSaledecimalplaces;
    std::string sPurchaseCurrency;
    BigFloat fPurchaseAmt;
};

bool bCheckInput(const std::vector<std::string>& sInput);
sCases SGetCasesFromLine(const std::string& ksCase);

#endif