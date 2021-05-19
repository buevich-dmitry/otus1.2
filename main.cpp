#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "ip.h"

int main(int, char const**) {
    try {
        std::vector<IpAddress> ip_pool = ReadIpPool(std::cin);

        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<>());

        PrintIpPool(ip_pool);

        PrintIpPool(FilterIpPool(ip_pool, MakePositionPredicate({{0, 1}})));
        PrintIpPool(FilterIpPool(ip_pool, MakePositionPredicate({{0, 46}, {1, 70}})));
        PrintIpPool(FilterIpPool(ip_pool, MakeAnyPredicate(46)));
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
