#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE solution_test
#include <boost/test/included/unit_test.hpp>

#include "solution.hpp"

BOOST_AUTO_TEST_CASE(solution_test) {
    Solution slt;
    std::vector<int> dataID{4,7,5,11,15};
    int IDSol = slt.IdenticalDistribution(dataID.size(), dataID);
    BOOST_CHECK(IDSol == 4);
}
