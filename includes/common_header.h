#ifndef STD_HEADER_H
#define STD_HEADER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include <cfenv>
#include <unordered_map>
#include "../boost_1_79_0/boost/multiprecision/cpp_dec_float.hpp"
using BigFloat = boost::multiprecision::cpp_dec_float_50;
enum FirstLineIndexForCoinUSD
{
    idx_BTCUSD = 0,
    idx_ETHUSD,
    idx_DOGEUSD,
    END
};


#endif