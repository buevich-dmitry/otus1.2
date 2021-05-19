#include "ip.h"

#include <array>
#include <string>
#include <vector>
#include <cassert>

using IpAddress = std::array<int, 4>;

std::vector<std::string> Split(const std::string &str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

IpAddress ReadIpAddress(const std::string& str) {
    const std::vector<std::string>& ip_str = Split(str, '.');
    IpAddress ip;
    assert(ip_str.size() == ip.size());
    for (size_t i = 0; i < ip.size(); ++i) {
        std::stringstream ss(ip_str[i]);
        ss >> ip[i];
    }
    return ip;
}

std::vector<IpAddress> ReadIpPool(std::istream& is) {
    std::vector<IpAddress> ip_pool;
    for(std::string line; std::getline(is, line);) {
        std::vector<std::string> v = Split(line, '\t');
        ip_pool.push_back(ReadIpAddress(v.at(0)));
    }
    return ip_pool;
}

IpPredicate MakePositionPredicate(const std::vector<std::pair<size_t, int>>& pos_to_value) {
    return [&pos_to_value](const IpAddress& ip) {
        for (const auto& [position, value] : pos_to_value) {
            assert(position < ip.size());
            if (ip[position] != value) {
                return false;
            }
        }
        return true;
    };
}

IpPredicate MakeAnyPredicate(int value) {
    return [value](const IpAddress& ip) {
        for (int ip_part : ip) {
            if (ip_part == value) {
                return true;
            }
        }
        return false;
    };
}

std::vector<IpAddress> FilterIpPool(
        const std::vector<IpAddress>& ip_pool, const IpPredicate& predicate) {
    std::vector<IpAddress> result;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(result), predicate);
    return result;
}

void PrintIp(const IpAddress& ip) {
    bool first = true;
    for (int ip_part : ip) {
        if (!first) {
            std::cout << ".";
        }
        first = false;
        std::cout << ip_part;
    }
}

void PrintIpPool(const std::vector<IpAddress>& ip_pool) {
    for(const auto& ip : ip_pool) {
        PrintIp(ip);
        std::cout << std::endl;
    }
}
