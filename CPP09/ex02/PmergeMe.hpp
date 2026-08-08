#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <string>
#include <vector>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    bool run(int argc, char** argv);

private:
    struct VectorNumber {
        int value;
        unsigned int stamp;
    };

    struct VectorPair {
        VectorNumber larger;
        VectorNumber smaller;
    };

    struct DequeNumber {
        int value;
        unsigned int stamp;
    };

    struct DequePair {
        DequeNumber larger;
        DequeNumber smaller;
    };

    std::vector<int> _vectorInput;
    std::deque<int> _dequeInput;

    bool loadArguments(int argc, char** argv);

    static bool parsePositiveInteger(const std::string& text, int& number);
    static void printSequence(const std::string& label, const std::vector<int>& values);
    static double readClockMicroseconds();

    static std::vector<int> sortWithVector(const std::vector<int>& values);
    static std::vector<VectorNumber> mergeInsertVector(const std::vector<VectorNumber>& values);
    static std::vector<unsigned int> jacobsthalOrderVector(unsigned int size);
    static unsigned int findVectorStamp(const std::vector<VectorNumber>& chain, unsigned int stamp);
    static unsigned int upperBoundVector(const std::vector<VectorNumber>& chain, int value, unsigned int limit);
    static const VectorNumber* findVectorSmaller(const std::vector<VectorPair>& pairs, unsigned int largerStamp);

    static std::deque<int> sortWithDeque(const std::deque<int>& values);
    static std::deque<DequeNumber> mergeInsertDeque(const std::deque<DequeNumber>& values);
    static std::deque<unsigned int> jacobsthalOrderDeque(unsigned int size);
    static unsigned int findDequeStamp(const std::deque<DequeNumber>& chain, unsigned int stamp);
    static unsigned int upperBoundDeque(const std::deque<DequeNumber>& chain, int value, unsigned int limit);
    static const DequeNumber* findDequeSmaller(const std::deque<DequePair>& pairs, unsigned int largerStamp);

    static bool sameSortedValues(const std::vector<int>& vectorResult, const std::deque<int>& dequeResult);
};

#endif
