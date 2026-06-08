#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>


using IpAddress = std::array<uint8_t, 4>;

IpAddress ParseIp (const std::string& str) {
    IpAddress ip;
    std::istringstream ss(str);
    std::string octet;
    int i = 0;
    while (std::getline(ss, octet, '.')) {
        if (i >= 4) throw std::invalid_argument("Too many octets: " + str);
        ip[i++] = static_cast<uint8_t>(std::stoi(octet));
    }
    if (i != 4) throw std::invalid_argument("Too few octets: " + str);
    return ip;
}

void PrintIp (const IpAddress& ip) {
    std::cout << static_cast<int>(ip[0]) << '.'
              << static_cast<int>(ip[1]) << '.'
              << static_cast<int>(ip[2]) << '.'
              << static_cast<int>(ip[3]) << '\n';
}


int main() {

    std::vector<IpAddress> ips;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        const auto tab = line.find('\t');
        std::string ip_str = (tab != std::string::npos) ? line.substr(0, tab) : line;
        try {
            ips.push_back(ParseIp(ip_str));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Skipping invalid IP: " << e.what() << "\n";
        }
    }


// print sorted list
    std::sort(ips.begin(), ips.end(), std::greater<>());
    for (const auto& ip : ips){
        PrintIp(ip);
    }

// filter object
    auto filter = [&](auto predicate) {
        for (const auto& ip : ips) {
            if (predicate(ip)) {
                PrintIp(ip);
            }
        }

    };
// make filter
    filter([](const IpAddress& ip) { return ip[0] == 1; });
    filter([](const IpAddress& ip) { return ip[0] == 46 && ip[1] == 70; });
    filter([](const IpAddress& ip) {
        return std::any_of(ip.begin(), ip.end(), [](const uint8_t b) { return b == 46; });
    });

    return 0;
}