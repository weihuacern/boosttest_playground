#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE solution_test
#include <boost/test/included/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include "solution.hpp"

BOOST_AUTO_TEST_CASE(test_AlmostEquivalentStrings) {
    Solution slt;
    // Almost Equivalent Strings
    std::vector<std::string> exp = {"YES", "NO"};
    std::vector<std::string> data1 = {"aabaab", "aaaaabb"};
    std::vector<std::string> data2 = {"bbabbc", "abb"};
    std::vector<std::string> res = slt.AlmostEquivalentStrings(data1, data2);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        res.begin(), res.end(),
        exp.begin(), exp.end());
}

BOOST_AUTO_TEST_CASE(test_IdenticalDistribution) {
    Solution slt;
    // Identical Distribution
    std::vector<int> data{4,7,5,11,15};
    int res = slt.IdenticalDistribution(data.size(), data);
    BOOST_CHECK(res == 4);
}

BOOST_AUTO_TEST_CASE(test_AutoscalePolicy) {
    Solution slt;
    // Autoscale Policy
    int dataIns = 1;
    std::vector<int> dataTicks{5,10,80};
    int res = slt.AutoscalePolicy(dataIns, dataTicks.size(), dataTicks);
    BOOST_CHECK(res == 2);
}

BOOST_AUTO_TEST_CASE(test_FactorOf3And5) {
    Solution slt;
    // Factor of 3 and 5
    int res = slt.FactorOf3And5(200, 405);
    BOOST_CHECK(res == 4);
}

BOOST_AUTO_TEST_CASE(test_AscendingBinarySorting) {
    Solution slt;
    // Ascending Binary Sorting
    std::vector<int> exp = {8, 5, 6, 7};
    std::vector<int> data = {7, 8, 6, 5};
    std::vector<int> res = slt.AscendingBinarySorting(data);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        res.begin(), res.end(),
        exp.begin(), exp.end());
}

BOOST_AUTO_TEST_CASE(test_ConnectingComputers) {
    Solution slt;
    // Connecting Computers
    std::vector<int> dataNodeF{1,1,3};
    std::vector<int> dataNodeT{2,3,2};
    int nEdges = dataNodeF.size();
    int res = slt.ConnectingComputers(4, nEdges, dataNodeF, dataNodeT);
    BOOST_CHECK(res == 1);
}

BOOST_AUTO_TEST_CASE(test_CircularArray) {
    Solution slt;
    // Circular Array
    std::vector<int> data{1,3,2,3};
    int nPath = data.size();
    int res = slt.CircularArray(3, nPath, data);
    BOOST_CHECK(res == 2);
}

BOOST_AUTO_TEST_CASE(test_BucketFill) {
    Solution slt;
    // Bucket Fill
    std::vector<std::string> data{"aabba","aabba","aaacb"};
    int res = slt.BucketFill(data);
    BOOST_CHECK(res == 5);
}

BOOST_AUTO_TEST_CASE(test_Enigma) {
    Solution slt;
    // Enigma
    int res = slt.Enigma(3, 2, 4);
    BOOST_CHECK(res == 6);
}

BOOST_AUTO_TEST_CASE(test_OscillatingString) {
    Solution slt;
    // Oscillating String
    std::string res = slt.OscillatingString("ababyz");
    std::string exp = std::string("abyzba");
    BOOST_TEST(res == exp);
}

/*
BOOST_AUTO_TEST_CASE(test_QuickSort) {
    //Solution slt;
    // Quick Sort
    std::vector<int> res1 = {13, 4, 5, 87, 120};
    std::vector<int> exp1 = {4, 5, 12, 87, 120};
    int n1 = res1.size();
    QuickSort::_quickSort(res1, 0, n1-1);
    //slt.QuickSort(res1);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        res1.begin(), res1.end(),
        exp1.begin(), exp1.end());
}
*/
