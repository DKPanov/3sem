#include <iostream>
#include<random>

using State = int;

class StateT {
public:
    virtual bool contains(State s) const = 0;
    virtual ~StateT() = default;
};

class DiscreteState : public StateT {
private:
    State const s0;
public:
    DiscreteState(State s0) : s0(s0) {}
    bool contains(State s) const override {
        return s == s0;
    }
};

class SegmentState : public StateT{
private:
    State const begin_s0, end_s0;
public:
    SegmentState(State begin_s0, State end_s0) :
        begin_s0(begin_s0), end_s0(end_s0) {}
    bool contains(State s) const override {
        return begin_s0 <= s and end_s0 >= s;
    }
};

class ProbabilityTest {
private:
    State const E_min, E_max;

public:
    ProbabilityTest(State E_min, State E_max) :
        E_min(E_min), E_max(E_max) {}

    float test(
        const StateT& system,
        unsigned test_count,
        unsigned seed) const {
        std::default_random_engine reng(seed);
        std::uniform_int_distribution<int>dstr(E_min, E_max);

        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (system.contains(dstr(reng))) ++good;

        return
            static_cast<float>(good)
            / static_cast<float>(test_count);
    }


};


int main() {
    const DiscreteState d(0);
    const SegmentState s(0, 100);
    ProbabilityTest pt(-1000, 1000);
    std::random_device rd;

    const std::vector<int> test_counts = { 500, 1000, 5000, 10000, 20000, 30000, 50000, 100000, 500000, 1000000 };

    for (size_t i = 0; i < test_counts.size(); i++) {
        std::cout << "Number of tests: " << test_counts[i] << std::endl;
        std::cout << "Probability (DiscreteState): " <<
                     (pt.test(d, test_counts[i], rd() % 100) +
                      pt.test(d, test_counts[i], rd() % 100) +
                      pt.test(d, test_counts[i], rd() % 100) +
                      pt.test(d, test_counts[i], rd() % 100) +
                      pt.test(d, test_counts[i], rd() % 100)) / 5 << std::endl;

        std::cout << "Probability (SegmentState): " <<
                     (pt.test(s, test_counts[i], rd() % 100) +
                      pt.test(s, test_counts[i], rd() % 100) +
                      pt.test(s, test_counts[i], rd() % 100) +
                      pt.test(s, test_counts[i], rd() % 100) +
                      pt.test(s, test_counts[i], rd() % 100)) / 5 << std::endl;

        std::cout << std::endl;
    }

    //зависит ли вероятность взаимодействия частиц с системой от вида
    //множества микросостояний: подряд идущие целые числа или случайно разбросанные?
    const SegmentState s1(1, 5);
    const DiscreteState d1(100);
    const DiscreteState d2(300);
    const DiscreteState d3(-900);
    const DiscreteState d4(-200);
    const DiscreteState d5(750);
    std::cout << pt.test(d1, 1000000, rd() % 100) +
                 pt.test(d2, 1000000, rd() % 100) +
                 pt.test(d3, 1000000, rd() % 100) +
                 pt.test(d4, 1000000, rd() % 100) +
                 pt.test(d5, 1000000, rd() % 100) << std::endl;

    std::cout << pt.test(s1, 1000000, rd() % 100) << std::endl;


    return 0;
}

