#pragma once

#include  <random>
#include  <iterator>

/**
 *
 * @brief Selects a random element from a range using a given random number generator.
 * @tparam Iter Iterator type of the range
 * @tparam RandomGenerator Random number generator type
 * @param start Iterator pointing to the beginning of the range
 * @param end Iterator pointing to the end of the range
 * @param g Random number generator
 * @return Iterator pointing to the selected element
 */
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator &g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

/**
 * @brief Selects a random element from a range using a Mersenne Twister engine.
 * @tparam Iter Iterator type of the range
 * @param start Iterator pointing to the beginning of the range
 * @param end Iterator pointing to the end of the range
 * @return Iterator pointing to the selected element
 */
template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}