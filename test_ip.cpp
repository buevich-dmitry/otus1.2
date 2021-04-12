#define BOOST_TEST_MODULE test_ip

#include "ip.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_ip)

void TestReadIpAddress(const std::string& ip_str, IpAddress expected_ip) {
    BOOST_CHECK(ReadIpAddress(ip_str) == expected_ip);
}

BOOST_AUTO_TEST_CASE(test_read_ip_read) {
    TestReadIpAddress("127.0.0.1", {127, 0, 0, 1});
    TestReadIpAddress("0.0.0.0", {0, 0, 0, 0});
    TestReadIpAddress("1.2.3.4", {1, 2, 3, 4});
    TestReadIpAddress("4.3.2.1", {4, 3, 2, 1});
    TestReadIpAddress("192.168.100.1", {192, 168, 100, 1});
}

BOOST_AUTO_TEST_CASE(test_read_ip_pool) {
    std::stringstream input_stream{
        "113.162.145.156 111 0\n"
        "157.39.22.224   5   6\n"
        "79.180.73.190   2   1\n"
        "179.210.145.4   22  0\n"
        "219.102.120.135 486 0\n"
    };
    const std::vector<IpAddress> expected_result = {
        {113, 162, 145, 156},
        {157, 39, 22, 224},
        {79, 180, 73, 190},
        {179, 210, 145, 4},
        {219, 102, 120, 135},
    };
    BOOST_CHECK(ReadIpPool(input_stream) == expected_result);
}

void TestFilterIpPool(
        const std::vector<IpAddress>& ip_pool,
        const IpPredicate& predicate,
        const std::vector<IpAddress>& expected_ip_pool) {
    BOOST_CHECK(FilterIpPool(ip_pool, predicate) == expected_ip_pool);
}

BOOST_AUTO_TEST_CASE(test_filter_ip_pool) {
    const std::vector<IpAddress> ip_pool = {
        {113, 162, 145, 156},
        {157, 39, 22, 180},
        {79, 180, 73, 190},
        {179, 210, 145, 4},
        {219, 102, 120, 135},
    };

    TestFilterIpPool(ip_pool, MakePositionPredicate({{0, 113}}), {ip_pool[0]});
    TestFilterIpPool(ip_pool, MakePositionPredicate({{2, 145}}), {ip_pool[0], ip_pool[3]});
    TestFilterIpPool(ip_pool, MakePositionPredicate({{3, 200}}), {});
    TestFilterIpPool(ip_pool, MakePositionPredicate({{0, 113}, {2, 145}}), {ip_pool[0]});
    TestFilterIpPool(ip_pool, MakePositionPredicate({{0, 113}, {2, 200}}), {});

    TestFilterIpPool(ip_pool, MakeAnyPredicate(180), {ip_pool[1], ip_pool[2]});
    TestFilterIpPool(ip_pool, MakeAnyPredicate(200), {});
}

}
