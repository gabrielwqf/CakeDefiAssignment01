#include "../includes/APIhandler.h"
#include <cpr/cpr.h>
#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct api_response{ 
    std::string currency;
    std::string price;
};
//macro for to_json and from_json from the docs
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(api_response, currency, price);

using namespace std;

const string API_URL = "https://api.nomics.com/v1/currencies/ticker";
const string kAPI_KEY = "536befbb1489f496d09eb3dd85c5066a519268e0";
const string API_PARAMETERS = "?key=" + kAPI_KEY + "&ids=BTC,ETH,DOGE&convert=USD";

unordered_map<int, string> StatusCodeAndResponse
{
    {401,"Error: API key is over rate limit\n"},
    {429,"Error: API key is invalid\n"},
    {404,"Error: API key is invalid\n"},
};

unordered_map<string, api_response> vGetDataCoinAPI();
string sCombinePriceFromAPI(const unordered_map<string, api_response>& CoinDatamap);

string getLivePriceForFirstLine()
{
    unordered_map<string, api_response> vData = vGetDataCoinAPI();
    if(vData.size() == 0)
        return "";
    return sCombinePriceFromAPI(vData);
}

unordered_map<string, api_response> vGetDataCoinAPI()
{
    cpr::Response r = cpr::Get(cpr::Url{API_URL + API_PARAMETERS},
                               cpr::Header{{"accept","application/json"}});
    
    auto it = StatusCodeAndResponse.find(r.status_code);

    if(r.status_code != 200 && it != StatusCodeAndResponse.end())
    {
        cout << StatusCodeAndResponse[r.status_code];
        return unordered_map<string, api_response>();
    }
    else if(r.status_code != 200 && it == StatusCodeAndResponse.end())
    {
        cout << "Error: Could not get data from API: " << r.status_code << "\n";
        return unordered_map<string, api_response>();
    }
    
    json array_ofPrices = json::parse(r.text);

    unordered_map<string, api_response>  vAPIResponse;
    
    for(const json& element: array_ofPrices)
    {
        api_response temp = element.get<api_response>();
        vAPIResponse[temp.currency] = temp;
    }
    
    return vAPIResponse;
}

string sCheckStringInMap(const unordered_map<string, api_response>& CoinDatamap, const string& sCurrency)
{
    if(CoinDatamap.find(sCurrency) == CoinDatamap.end())
    {
        cout << "Error: " << sCurrency << " is not found from stored API data\n";
        return "";
    }
    return CoinDatamap.at(sCurrency).price;
}

#define CHECK_EMPTY_STRING_ELSE_ADD_TO_STRING(sStringToAdd, sStringToCheck) \
    if(string str = sCheckStringInMap(CoinDatamap, sStringToCheck); str == "")\
        return "";\
    else \
        sStringToAdd += str + " ";

string sCombinePriceFromAPI(const unordered_map<string, api_response>& CoinDatamap)
{
    string sPrice = "";
    for(int i = 0; i < FirstLineIndexForCoinUSD::END; i++)
    {
        if(i == idx_BTCUSD)
        {
            CHECK_EMPTY_STRING_ELSE_ADD_TO_STRING(sPrice, "BTC");
        }
        else if(i == idx_ETHUSD)
        {
            CHECK_EMPTY_STRING_ELSE_ADD_TO_STRING(sPrice, "ETH");
        }
        else if(i == idx_DOGEUSD)
        {
            CHECK_EMPTY_STRING_ELSE_ADD_TO_STRING(sPrice, "DOGE");
        }
    }

    return sPrice;
}

