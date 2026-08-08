#include "RPN.hpp"

#include <cctype>
#include <sstream>

RpnEvaluator::RpnEvaluator() {}

RpnEvaluator::RpnEvaluator(const RpnEvaluator& other)
{
    (void)other;
}

RpnEvaluator& RpnEvaluator::operator=(const RpnEvaluator& other)
{
    (void)other;
    return *this;
}

RpnEvaluator::~RpnEvaluator() {}

bool RpnEvaluator::isDigitToken(const std::string& token)
{
    return token.size() == 1 && std::isdigit(static_cast<unsigned char>(token[0]));
}

bool RpnEvaluator::isOperatorToken(const std::string& token)
{
    return token.size() == 1
        && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/');
}

bool RpnEvaluator::applyOperator(const std::string& token, std::stack<int>& numberTrail)
{
    if (numberTrail.size() < 2)
        return false;

    int rightValue = numberTrail.top();
    numberTrail.pop();
    int leftValue = numberTrail.top();
    numberTrail.pop();

    if (token[0] == '+')
        numberTrail.push(leftValue + rightValue);
    else if (token[0] == '-')
        numberTrail.push(leftValue - rightValue);
    else if (token[0] == '*')
        numberTrail.push(leftValue * rightValue);
    else {
        if (rightValue == 0)
            return false;
        numberTrail.push(leftValue / rightValue);
    }
    return true;
}

bool RpnEvaluator::compute(const std::string& expression, int& answer) const
{
    std::istringstream tokenStream(expression);
    std::stack<int> numberTrail;
    std::string token;

    while (tokenStream >> token) {
        if (isDigitToken(token)) {
            numberTrail.push(token[0] - '0');
        } else if (isOperatorToken(token)) {
            if (!applyOperator(token, numberTrail))
                return false;
        } else {
            return false;
        }
    }

    if (numberTrail.size() != 1)
        return false;

    answer = numberTrail.top();
    return true;
}
