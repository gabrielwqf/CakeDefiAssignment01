import unittest
import subprocess
import os

CONST_PROGRAM_NAME = "run.exe" if os.name == "nt" else "./run"
CONST_FIRST_LINE_EXPECTED_INPUT = "First line: <BTCUSD rate> <ETHUSD rate> <DOGEUSD rate>"
CONST_SECOND_LINE_EXPECTED_INPUT = "Subsequent lines: <ETHSALE rate> <SALE decimal places> <Purchase currency> <BTC/ETH/DOGE purchase amount>"

def run_program_with_fileinput(program):
    try:
        output = subprocess.check_output(program + "< input.txt", stderr=subprocess.STDOUT, shell=True)
        return output.decode('utf-8')
    except subprocess.CalledProcessError as e:
        return e.output.decode('utf-8')

def run_program(program):
    try:
        output = subprocess.check_output(program, stderr=subprocess.STDOUT, shell=True)
        return output.decode('utf-8')
    except subprocess.CalledProcessError as e:
        return e.output.decode('utf-8')

def make_file(file_contents):
    file = open('input.txt', 'w')
    file.write(file_contents)
    file.close()
    return file

#TEST CASES START HERE
class MultiCurrencyTokenSale(unittest.TestCase):
    def test_first_line_only(self):
        make_file("lorem ipsum\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = CONST_FIRST_LINE_EXPECTED_INPUT + '\n' \
                + CONST_SECOND_LINE_EXPECTED_INPUT + '\n'
        self.assertEqual(actual,expected)

    def test_blank_file(self):
        make_file("")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = CONST_FIRST_LINE_EXPECTED_INPUT + '\n' \
                + CONST_SECOND_LINE_EXPECTED_INPUT + '\n'
        self.assertEqual(actual, expected)
    
    def test_first_line_two_floats_only(self):
        make_file("3825.281112 138.8911\nlorem ipsum\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = CONST_FIRST_LINE_EXPECTED_INPUT + "\n"
        self.assertEqual(actual, expected)

    def test_first_line_no_decimals(self):
        make_file("3825.281112 138.8911 1\nlorem ipsum\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = CONST_SECOND_LINE_EXPECTED_INPUT + "\n"
        self.assertEqual(actual, expected)

    def test_first_line_correct_but_second_line_wrong(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\nlorem ipsum\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = CONST_SECOND_LINE_EXPECTED_INPUT + "\n"
        self.assertEqual(actual, expected)

    
    def test_SALE_decimal_places_not_integer(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n1.5 3.0 ETH 3.5\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "<SALE decimal places> must be an integer.\n"
        self.assertEqual(actual, expected)
    
    def test_ETHSALE_negative(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n-1 3.0 ETH 3.5\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "<ETHSALE rate> should be in non-negative integer or floats.\n"
        self.assertEqual(actual, expected)
    
    def test_purchase_currency_not_correct(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n1.5 3 DFI 3.5\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "<Purchase currency> is BTC, ETH or DOGE only\n"
        self.assertEqual(actual, expected)
        
    def test_purchase_amount_negative(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n1.5 3 ETH -44\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "<BTC/ETH/DOGE purchase amount> must be in non-negative integer or decimal points.\n"
        self.assertEqual(actual, expected)
    
    def test_BTCUSD_negative(self):
        make_file("-3825.281112 138.8911 0.00198422341298374987\n1.5 3 ETH 3.5\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = CONST_FIRST_LINE_EXPECTED_INPUT + " in non-negative float or integer only.\n"
        self.assertEqual(actual, expected)

    def test_case1_1o5_3_ETH_3o5(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n1.5 3 ETH 3.5\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "5.250\n"
        self.assertEqual(actual, expected)

    def test_case2_1o5_3_BTC_3o5(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n1.5 3 BTC 3.5\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "144.593\n"
        self.assertEqual(actual, expected)

    def test_case3_1o5_3_DOGE_3o5(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n1.5 3 DOGE 3.5\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "0.000\n"
        self.assertEqual(actual, expected)

    def test_case4_1o5_3_DOGE_350000(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n1.5 3 DOGE 350000\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "7.500\n"
        self.assertEqual(actual, expected)
    
    def test_case5(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n6540825.876543210987654325 18 ETH 992465.123456789012345678\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "6491541561072.818099748528072316\n"
        self.assertEqual(actual, expected)

    def test_case6(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n6540825.876543210987654325 18 BTC 992465.123456789012345678\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "178787347219043.160674656449440139\n"
        self.assertEqual(actual, expected)

    def test_case7(self):
        make_file("3825.281112 138.8911 0.00198422341298374987\n6540825.876543210987654325 18 DOGE 992465.123456789012345678\n")
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "92739338.602961360930566195\n"
        self.assertEqual(actual, expected)

    def test_case8(self):
        case = ["3825.281112 138.8911 0.00198422341298374987", 
        "1.5 3 ETH 3.5",
        "1.5 3 BTC 3.5",
        "1.5 3 DOGE 3.5",
        "1.5 3 DOGE 350000",
        "1.5 1 ETH 3.5",
        "6540825.876543210987654325 18 ETH 992465.123456789012345678",
        "6540825.876543210987654325 18 DOGE 992465.123456789012345678",
        "6540825.876543210987654325 18 BTC 992465.123456789012345678"]
        make_file("\n".join(case))
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "\n".join(["5.250","144.593","0.000","7.500","5.2",
        "6491541561072.818099748528072316",
        "92739338.602961360930566195",
        "178787347219043.160674656449440139\n"])
        self.assertEqual(actual, expected)

    def test_case9(self):
        case = ["21201.41616144 1349.17168784 0.063659639",
        "5000 5 BTC 2.4",
        "5000 3 ETH 5",
        "22626 22 DOGE 11190",
        "6522.26323 23 BTC 23571095",
        "23521 42 BTC 626234",
        "37232 0 DOGE 1111110101010101"]
        make_file("\n".join(case))
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')
        expected = "\n".join(["188572.73409","25000.000","11946.3386505247167505667037",
        "2415882080290.61286043043553821511090",
        "231467529710.027320755462199797416703549731376047046890",
        "1951957754611022\n"])
        self.assertEqual(actual, expected)
    

    def test_case10(self):
        case = ["CURRENT", "1.5 3 ETH 3.5"]
        make_file("\n".join(case))
        actual = run_program_with_fileinput(CONST_PROGRAM_NAME).replace('\r\n', '\n')[0:16]
        expected = "CURRENT PRICES: "
        self.assertEqual(actual, expected)
    





    

        
