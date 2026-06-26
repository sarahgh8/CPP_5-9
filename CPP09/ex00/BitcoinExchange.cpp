#include "BitcoinExchange.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

Bitcoin::Bitcoin() {}
Bitcoin::~Bitcoin() {}

std::string Bitcoin::strip(const std::string& text)
{
    std::size_t i = 0;
    while (i < text.size() && std::isspace(static_cast<unsigned char>(text[i])))
        ++i;
    std::size_t j = text.size();
    while (j > i && std::isspace(static_cast<unsigned char>(text[j - 1])))
        --j;
    return text.substr(i, j - i);
}

bool Bitcoin::toDouble(const std::string& text, double& value)
{
    std::string s = strip(text);
    if (s.empty())
        return false;
    std::istringstream ss(s);
    ss >> value;
    return !ss.fail() && ss.eof();
}

bool Bitcoin::checkDate(const std::string& date)
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (std::size_t i = 0; i < date.size(); ++i)
        if (i != 4 && i != 7 && !std::isdigit(static_cast<unsigned char>(date[i])))
            return false;

    int y = std::atoi(date.substr(0, 4).c_str());
    int m = std::atoi(date.substr(5, 2).c_str());
    int d = std::atoi(date.substr(8, 2).c_str());
    if (m < 1 || m > 12 || d < 1)
        return false;

    int md = 31;
    if (m == 2) {
        bool leap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
        md = leap ? 29 : 28;
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        md = 30;
    }
    return d <= md;
}

bool Bitcoin::checkVal(const std::string& text, double& value, std::string& err)
{
    if (!toDouble(text, value))
        return false;
    if (value < 0) {
        err = "Error: not a positive number.";
        return false;
    }
    if (value > 1000) {
        err = "Error: too large a number.";
        return false;
    }
    return true;
}

bool Bitcoin::splitLine(const std::string& line, std::string& date, std::string& value)
{
    std::size_t pos = line.find('|');
    if (pos == std::string::npos)
        return false;
    date = strip(line.substr(0, pos));
    value = strip(line.substr(pos + 1));
    return !date.empty() && !value.empty();
}

bool Bitcoin::loadDB(const std::string& path)
{
    std::ifstream f(path.c_str());
    if (!f.is_open())
        return false;

    std::string line;
    if (!std::getline(f, line))
        return false;

    while (std::getline(f, line)) {
        if (line.empty())
            continue;
        std::size_t pos = line.find(',');
        if (pos == std::string::npos)
            continue;
        std::string date = strip(line.substr(0, pos));
        std::string value = strip(line.substr(pos + 1));
        double rate = 0;
        if (!checkDate(date) || !toDouble(value, rate))
            continue;
        rates[date] = rate;
    }
    return !rates.empty();
}

bool Bitcoin::run(const std::string& path) const
{
    std::ifstream f(path.c_str());
    if (!f.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return false;
    }

    std::string line;
    bool first = true;
    while (std::getline(f, line)) {
        if (line.empty())
            continue;
        if (first) {
            first = false;
            std::string header = strip(line);
            if (header == "date | value" || header == "date|value")
                continue;
        }
        std::string date;
        std::string val;
        if (!splitLine(line, date, val)) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (!checkDate(date)) {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }
        double value = 0;
        std::string err;
        if (!checkVal(val, value, err)) {
            if (!err.empty())
                std::cout << err << std::endl;
            else
                std::cout << "Error: bad input => " << val << std::endl;
            continue;
        }

        std::map<std::string, double>::const_iterator it = rates.lower_bound(date);
        if (it == rates.end() || it->first != date) {
            if (it == rates.begin()) {
                std::cout << "Error: bad input => " << date << std::endl;
                continue;
            }
            if (it == rates.end() || it->first > date)
                --it;
        }
        double result = value * it->second;
        std::cout << date << " => " << val << " = " << result << std::endl;
    }
    return true;
}
