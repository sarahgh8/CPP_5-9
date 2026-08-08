#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RpnEvaluator {
public:
    RpnEvaluator();
    RpnEvaluator(const RpnEvaluator& other);
    RpnEvaluator& operator=(const RpnEvaluator& other);
    ~RpnEvaluator();

    bool compute(const std::string& expression, int& answer) const;

private:
    static bool isDigitToken(const std::string& token);
    static bool isOperatorToken(const std::string& token);
    static bool applyOperator(const std::string& token, std::stack<int>& numberTrail);
};

#endif
