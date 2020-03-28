#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE vector_test
#include <boost/test/included/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include "huawei_vector.hpp"

BOOST_AUTO_TEST_CASE(test_vector) {
    huawei::vector<int> huaweiIntVec(3, 1);
    std::vector<int> stdIntVec = {1, 1, 1};
    BOOST_CHECK_EQUAL_COLLECTIONS(
        stdIntVec.begin(), stdIntVec.end(),
        huaweiIntVec.begin(), huaweiIntVec.end());
    huaweiIntVec.push_back(2);
    stdIntVec.push_back(2);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        stdIntVec.begin(), stdIntVec.end(),
        huaweiIntVec.begin(), huaweiIntVec.end());

    huawei::vector<char> huaweiChrVec(1, 1);
    std::vector<char> stdChrVec;
    stdChrVec.push_back(1);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        stdChrVec.begin(), stdChrVec.end(),
        huaweiChrVec.begin(), huaweiChrVec.end());
}
