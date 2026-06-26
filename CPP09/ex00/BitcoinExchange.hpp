#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class Bitcoin {
public:
    Bitcoin();
    ~Bitcoin();

    bool loadDB(const std::string& path);
    bool run(const std::string& path) const;

private:
    std::map<std::string, double> rates;

    static std::string strip(const std::string& text);
    static bool toDouble(const std::string& text, double& value);
    static bool checkDate(const std::string& date);
    static bool checkVal(const std::string& text, double& value, std::string& err);
    static bool splitLine(const std::string& line, std::string& date, std::string& value);
};

#endif
