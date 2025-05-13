/**
 * @file mini_dns_resolver.cpp
 * @Eduardo M 
 * @A simple C++ DNS resolver that converts a domain name into an IP address,
 *        and displays its binary and hexadecimal representations.
 * @date 2025
 */

#include <iostream>      // Input/output streams
#include <string>        // String handling
#include <netdb.h>       // gethostbyname, struct hostent
#include <arpa/inet.h>   // inet_ntoa, inet_aton
#include <bitset>        // Binary conversion
#include <iomanip>       // Hex formatting

int main() {
    // Ask user to enter a domain name
    std::string domain;
    std::cout << "Enter a domain name (e.g., example.com): ";
    std::cin >> domain;

    // Use gethostbyname to resolve the domain to an IP address
    hostent* host = gethostbyname(domain.c_str());
    if (host == nullptr) {
        std::cerr << "Error: Unable to resolve domain." << std::endl;
        return 1;
    }

    // Extract the first IP address from the list
    in_addr* addr = reinterpret_cast<in_addr*>(host->h_addr);

    // Convert IP address to string
    std::string ip_str = inet_ntoa(*addr);
    std::cout << "Resolved IP Address: " << ip_str << std::endl;

    // Display IP address in binary format
    std::cout << "Binary Representation: ";
    unsigned char* bytes = reinterpret_cast<unsigned char*>(addr);
    for (int i = 0; i < 4; ++i) {
        std::bitset<8> bits(bytes[i]);
        std::cout << bits;
        if (i != 3) std::cout << ".";
    }

    // Display IP address in hexadecimal format
    std::cout << std::endl << "Hexadecimal Representation: ";
    for (int i = 0; i < 4; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(bytes[i]);
        if (i != 3) std::cout << ":";
    }

    std::cout << std::dec << std::endl;  // Reset output formatting
    return 0;
}
