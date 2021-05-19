#pragma once

#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <functional>
#include <iostream>

using IpAddress = std::array<int, 4>;
using IpPredicate = std::function<bool(IpAddress)>;

IpAddress ReadIpAddress(const std::string& str);
std::vector<IpAddress> ReadIpPool(std::istream& is);

IpPredicate MakePositionPredicate(const std::vector<std::pair<size_t, int>>& pos_to_value);
IpPredicate MakeAnyPredicate(int value);

std::vector<IpAddress> FilterIpPool(
    const std::vector<IpAddress>& ip_pool, const IpPredicate& predicate);

void PrintIp(const IpAddress& ip);
void PrintIpPool(const std::vector<IpAddress>& ip_pool);
