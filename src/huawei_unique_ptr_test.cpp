#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE unique_ptr_test
#include <boost/test/included/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include "huawei_unique_ptr.hpp"

BOOST_AUTO_TEST_CASE(test_unique_ptr) {
    huawei::unique_ptr<int> huaweiIntUP (new int);
    int * manualIntP;
    *huaweiIntUP = 4;
    BOOST_CHECK(*huaweiIntUP == 4);
    int* huaweiIntVal = huaweiIntUP.get();
    *huaweiIntVal = 5;
    BOOST_CHECK(*huaweiIntUP == 5);
    manualIntP = huaweiIntUP.release();
    BOOST_CHECK(*manualIntP == 5);
}
