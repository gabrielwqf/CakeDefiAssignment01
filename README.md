# DefiChain C++ Exercise - Solution
## Brief intro
- Implemented TDD style with test cases written in Python3
- Live Prices feature implemented. 
- Calculations are compared with Wolfram Alpha Arbitrary Precision calculator.
- Boost::multiprecision used for floating points (up to 50 decimal places)
- Works out of the box
- Can compile in Windows and Linux using Cmake

## Build
- Requirements: OpenSSL in path, 64bit system, CMake,  a C++ compiler that supports C++17 and Internet to download libraries
- Different instructions for Windows and Linux builds
- Tested in Windows 10 with Cmake 3.11 & g++ 8.1.0
- Tested in Ubuntu with Cmake 3.23 & g++ 5.0
#### Windows
- Run build_windows.bat or build_MingW.bat -> output in /test
#### Ubuntu or Kali Linux
- Run build.sh -> output in /test

                
				
## Unit Test
- In /test folder
- Requires Python3
- Run unit_test.bat or unit_test.sh, depending on your OS
- Used for TDD, the program will output test cases to files, then run the command to redirect it and compares the output with the expected one.

## Assumptions Made
- Standard input will always have an input to reduce complicated checks for empty stdin (it will hang if there is no file redirected to it)
- Error checking for input is done, but cannot check for every error
- No more than 50 decimal places needed

## Limitations and further improvements
- Hardcoded values such as "BTC" or "ETH" can be handled in a class that concerns itself with it. New pairings can be extended and handled in that class and its associated enums and strings, in one place. 
- I only realised the above after doing some code refactoring at the end, so i ran out of time to implement this.
- There are no custom classes, but this was by design as it gave no advantages and none of the features such as inheritance or dependency inversion was needed. The only situation I could think of that would need further extensibility and maintenance are for further pairings, which I talked about in the first point.
- I used Wolfram Alpha to calculate floating point to resolve difference in the test cases due to its reputation. 
- I am open to reviews, discussions and criticisms.

## Bonus question
- Rounding down is due to prevent attacks that aims to farm free money when it rounds up. If the transaction fee is lower than the amount of money acquired from rounding up, there is an incentive to exploit this. The attacker could use a script that does this in a loop until the pool is drained or the transaction fee rises to turn it into a loss.