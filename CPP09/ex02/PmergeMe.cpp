#include "PmergeMe.hpp"

#include <climits>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sys/time.h>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
{
    *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other) {
        _vectorInput = other._vectorInput;
        _dequeInput = other._dequeInput;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::parsePositiveInteger(const std::string& text, int& number)
{
    if (text.empty())
        return false;

    long value = 0;
    for (std::size_t index = 0; index < text.size(); ++index) {
        if (!std::isdigit(static_cast<unsigned char>(text[index])))
            return false;
        int digit = text[index] - '0';
        if (value > (static_cast<long>(INT_MAX) - digit) / 10)
            return false;
        value = value * 10 + digit;
    }
    if (value <= 0)
        return false;

    number = static_cast<int>(value);
    return true;
}

bool PmergeMe::loadArguments(int argc, char** argv)
{
    if (argc < 2)
        return false;

    _vectorInput.clear();
    _dequeInput.clear();
    _vectorInput.reserve(static_cast<std::size_t>(argc - 1));

    for (int index = 1; index < argc; ++index) {
        int number = 0;
        if (!parsePositiveInteger(argv[index], number))
            return false;
        _vectorInput.push_back(number);
        _dequeInput.push_back(number);
    }
    return true;
}

void PmergeMe::printSequence(const std::string& label, const std::vector<int>& values)
{
    std::cout << label;
    for (std::size_t index = 0; index < values.size(); ++index)
        std::cout << ' ' << values[index];
    std::cout << std::endl;
}

double PmergeMe::readClockMicroseconds()
{
    timeval moment;
    gettimeofday(&moment, NULL);
    return static_cast<double>(moment.tv_sec) * 1000000.0 + static_cast<double>(moment.tv_usec);
}

std::vector<unsigned int> PmergeMe::jacobsthalOrderVector(unsigned int size)
{
    std::vector<unsigned int> order;
    if (size == 0)
        return order;

    order.reserve(size);
    order.push_back(0);

    unsigned int previous = 1;
    unsigned int current = 3;
    while (previous < size) {
        unsigned int groupEnd = current;
        if (groupEnd > size)
            groupEnd = size;
        for (unsigned int position = groupEnd; position > previous; --position)
            order.push_back(position - 1);
        unsigned int next = current + previous * 2;
        previous = current;
        current = next;
    }
    return order;
}

unsigned int PmergeMe::findVectorStamp(const std::vector<VectorNumber>& chain, unsigned int stamp)
{
    for (unsigned int index = 0; index < chain.size(); ++index) {
        if (chain[index].stamp == stamp)
            return index;
    }
    return static_cast<unsigned int>(chain.size());
}

unsigned int PmergeMe::upperBoundVector(const std::vector<VectorNumber>& chain, int value, unsigned int limit)
{
    unsigned int low = 0;
    unsigned int high = limit;

    while (low < high) {
        unsigned int middle = low + (high - low) / 2;
        if (value < chain[middle].value)
            high = middle;
        else
            low = middle + 1;
    }
    return low;
}

const PmergeMe::VectorNumber* PmergeMe::findVectorSmaller(const std::vector<VectorPair>& pairs, unsigned int largerStamp)
{
    for (std::size_t index = 0; index < pairs.size(); ++index) {
        if (pairs[index].larger.stamp == largerStamp)
            return &pairs[index].smaller;
    }
    return NULL;
}

std::vector<PmergeMe::VectorNumber> PmergeMe::mergeInsertVector(const std::vector<VectorNumber>& values)
{
    if (values.size() < 2)
        return values;

    std::vector<VectorPair> pairs;
    std::vector<VectorNumber> largerNumbers;
    VectorNumber leftover;
    bool hasLeftover = false;

    pairs.reserve(values.size() / 2);
    largerNumbers.reserve(values.size() / 2);

    for (std::size_t index = 0; index + 1 < values.size(); index += 2) {
        VectorPair link;
        if (values[index].value > values[index + 1].value) {
            link.larger = values[index];
            link.smaller = values[index + 1];
        } else {
            link.larger = values[index + 1];
            link.smaller = values[index];
        }
        pairs.push_back(link);
        largerNumbers.push_back(link.larger);
    }

    if (values.size() % 2 != 0) {
        leftover = values[values.size() - 1];
        hasLeftover = true;
    }

    std::vector<VectorNumber> chain = mergeInsertVector(largerNumbers);
    std::vector<VectorPair> orderedInsertions;
    orderedInsertions.reserve(chain.size());

    for (std::size_t index = 0; index < chain.size(); ++index) {
        const VectorNumber* smaller = findVectorSmaller(pairs, chain[index].stamp);
        if (smaller != NULL) {
            VectorPair task;
            task.larger = chain[index];
            task.smaller = *smaller;
            orderedInsertions.push_back(task);
        }
    }

    std::vector<unsigned int> order = jacobsthalOrderVector(static_cast<unsigned int>(orderedInsertions.size()));

    for (std::size_t orderIndex = 0; orderIndex < order.size(); ++orderIndex) {
        unsigned int taskIndex = order[orderIndex];
        if (taskIndex >= orderedInsertions.size())
            continue;

        unsigned int limit = findVectorStamp(chain, orderedInsertions[taskIndex].larger.stamp);
        unsigned int insertAt = upperBoundVector(chain, orderedInsertions[taskIndex].smaller.value, limit);
        chain.insert(chain.begin() + insertAt, orderedInsertions[taskIndex].smaller);
    }

    if (hasLeftover) {
        unsigned int insertAt = upperBoundVector(chain, leftover.value, static_cast<unsigned int>(chain.size()));
        chain.insert(chain.begin() + insertAt, leftover);
    }
    return chain;
}

std::vector<int> PmergeMe::sortWithVector(const std::vector<int>& values)
{
    std::vector<VectorNumber> stampedValues;
    stampedValues.reserve(values.size());

    for (std::size_t index = 0; index < values.size(); ++index) {
        VectorNumber number;
        number.value = values[index];
        number.stamp = static_cast<unsigned int>(index);
        stampedValues.push_back(number);
    }

    std::vector<VectorNumber> sortedStamped = mergeInsertVector(stampedValues);
    std::vector<int> sortedValues;
    sortedValues.reserve(sortedStamped.size());

    for (std::size_t index = 0; index < sortedStamped.size(); ++index)
        sortedValues.push_back(sortedStamped[index].value);
    return sortedValues;
}

std::deque<unsigned int> PmergeMe::jacobsthalOrderDeque(unsigned int size)
{
    std::deque<unsigned int> order;
    if (size == 0)
        return order;

    order.push_back(0);

    unsigned int previous = 1;
    unsigned int current = 3;
    while (previous < size) {
        unsigned int groupEnd = current;
        if (groupEnd > size)
            groupEnd = size;
        for (unsigned int position = groupEnd; position > previous; --position)
            order.push_back(position - 1);
        unsigned int next = current + previous * 2;
        previous = current;
        current = next;
    }
    return order;
}

unsigned int PmergeMe::findDequeStamp(const std::deque<DequeNumber>& chain, unsigned int stamp)
{
    for (unsigned int index = 0; index < chain.size(); ++index) {
        if (chain[index].stamp == stamp)
            return index;
    }
    return static_cast<unsigned int>(chain.size());
}

unsigned int PmergeMe::upperBoundDeque(const std::deque<DequeNumber>& chain, int value, unsigned int limit)
{
    unsigned int low = 0;
    unsigned int high = limit;

    while (low < high) {
        unsigned int middle = low + (high - low) / 2;
        if (value < chain[middle].value)
            high = middle;
        else
            low = middle + 1;
    }
    return low;
}

const PmergeMe::DequeNumber* PmergeMe::findDequeSmaller(const std::deque<DequePair>& pairs, unsigned int largerStamp)
{
    for (std::size_t index = 0; index < pairs.size(); ++index) {
        if (pairs[index].larger.stamp == largerStamp)
            return &pairs[index].smaller;
    }
    return NULL;
}

std::deque<PmergeMe::DequeNumber> PmergeMe::mergeInsertDeque(const std::deque<DequeNumber>& values)
{
    if (values.size() < 2)
        return values;

    std::deque<DequePair> pairs;
    std::deque<DequeNumber> largerNumbers;
    DequeNumber leftover;
    bool hasLeftover = false;

    for (std::size_t index = 0; index + 1 < values.size(); index += 2) {
        DequePair link;
        if (values[index].value > values[index + 1].value) {
            link.larger = values[index];
            link.smaller = values[index + 1];
        } else {
            link.larger = values[index + 1];
            link.smaller = values[index];
        }
        pairs.push_back(link);
        largerNumbers.push_back(link.larger);
    }

    if (values.size() % 2 != 0) {
        leftover = values[values.size() - 1];
        hasLeftover = true;
    }

    std::deque<DequeNumber> chain = mergeInsertDeque(largerNumbers);
    std::deque<DequePair> orderedInsertions;

    for (std::size_t index = 0; index < chain.size(); ++index) {
        const DequeNumber* smaller = findDequeSmaller(pairs, chain[index].stamp);
        if (smaller != NULL) {
            DequePair task;
            task.larger = chain[index];
            task.smaller = *smaller;
            orderedInsertions.push_back(task);
        }
    }

    std::deque<unsigned int> order = jacobsthalOrderDeque(static_cast<unsigned int>(orderedInsertions.size()));

    for (std::size_t orderIndex = 0; orderIndex < order.size(); ++orderIndex) {
        unsigned int taskIndex = order[orderIndex];
        if (taskIndex >= orderedInsertions.size())
            continue;

        unsigned int limit = findDequeStamp(chain, orderedInsertions[taskIndex].larger.stamp);
        unsigned int insertAt = upperBoundDeque(chain, orderedInsertions[taskIndex].smaller.value, limit);
        chain.insert(chain.begin() + insertAt, orderedInsertions[taskIndex].smaller);
    }

    if (hasLeftover) {
        unsigned int insertAt = upperBoundDeque(chain, leftover.value, static_cast<unsigned int>(chain.size()));
        chain.insert(chain.begin() + insertAt, leftover);
    }
    return chain;
}

std::deque<int> PmergeMe::sortWithDeque(const std::deque<int>& values)
{
    std::deque<DequeNumber> stampedValues;

    for (std::size_t index = 0; index < values.size(); ++index) {
        DequeNumber number;
        number.value = values[index];
        number.stamp = static_cast<unsigned int>(index);
        stampedValues.push_back(number);
    }

    std::deque<DequeNumber> sortedStamped = mergeInsertDeque(stampedValues);
    std::deque<int> sortedValues;

    for (std::size_t index = 0; index < sortedStamped.size(); ++index)
        sortedValues.push_back(sortedStamped[index].value);
    return sortedValues;
}

bool PmergeMe::sameSortedValues(const std::vector<int>& vectorResult, const std::deque<int>& dequeResult)
{
    if (vectorResult.size() != dequeResult.size())
        return false;
    for (std::size_t index = 0; index < vectorResult.size(); ++index) {
        if (vectorResult[index] != dequeResult[index])
            return false;
    }
    return true;
}

bool PmergeMe::run(int argc, char** argv)
{
    if (!loadArguments(argc, argv))
        return false;

    printSequence("Before:", _vectorInput);

    double vectorStart = readClockMicroseconds();
    std::vector<int> vectorResult = sortWithVector(_vectorInput);
    double vectorTime = readClockMicroseconds() - vectorStart;

    double dequeStart = readClockMicroseconds();
    std::deque<int> dequeResult = sortWithDeque(_dequeInput);
    double dequeTime = readClockMicroseconds() - dequeStart;

    if (!sameSortedValues(vectorResult, dequeResult))
        return false;

    printSequence("After:", vectorResult);

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << _vectorInput.size()
              << " elements with std::vector : " << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _dequeInput.size()
              << " elements with std::deque : " << dequeTime << " us" << std::endl;
    return true;
}
