#include "tests.h"

#include <set>
#include <cmath>

#include <iostream>

namespace ais31
{

// Тест бесповторности
// Disjointedness test
bool test0(const Block3145728& bits)
{
    static constexpr std::size_t BLOCK_SIZE = 48;
    auto to_uint64 = [&bits](std::size_t index) -> std::uint64_t
    {
        std::size_t from = index * BLOCK_SIZE;
        std::size_t to = from + BLOCK_SIZE;
        std::uint64_t ans = 0;
        for (std::size_t i = from; i < to; ++i)
        {
            ans <<= 1;
            ans += bits[i];
        }
        return ans;
    };

    std::set<std::uint64_t> numbers;
    for (std::size_t i = 0; i < bits.size() / BLOCK_SIZE; ++i)
        numbers.emplace(to_uint64(i));

    return numbers.size() == bits.size() / BLOCK_SIZE;
}

// Тест числа единиц
// Monobit test
bool test1(const Block20000& bits)
{
    int ones = 0;
    for (bool bit : bits)
        ones += bit;

    static constexpr int MAX_DIFF = 346;
    return (std::abs(ones - static_cast<int>(bits.size() / 2)) < MAX_DIFF);
}

// Покер-тест
// Poker test
bool test2(const Block20000& bits)
{
    static constexpr std::size_t BLOCK_SIZE = 4;
    std::array<std::uint64_t, (1 << BLOCK_SIZE)> freqs;
    freqs.fill(0);

    auto to_size_t = [&bits](std::size_t index) -> std::size_t
    {
        std::size_t from = index * BLOCK_SIZE;
        std::size_t to = from + BLOCK_SIZE;
        std::size_t ans = 0;
        for (std::size_t i = from; i < to; ++i)
        {
            ans <<= 1;
            ans += bits[i];
        }
        return ans;
    };

    for (std::size_t i = 0; i < bits.size() / BLOCK_SIZE; ++i)
        ++freqs[to_size_t(i)];

    std::uint64_t squares_sum = 0;
    for (std::uint64_t freq : freqs)
        squares_sum += freq * freq;

    double s = static_cast<double>(squares_sum * BLOCK_SIZE * freqs.size()) / bits.size() - bits.size() / BLOCK_SIZE;
    static constexpr double S_LOW = 1.03, S_HIGH = 57.40;
    return (S_LOW < s && s < S_HIGH);
}

// Тест серий
// Runs test
bool test3(const Block20000& bits)
{
    static constexpr std::size_t MAX_RUN = 6;
    std::array<std::size_t, MAX_RUN> runs[2];
    runs[0].fill(0);
    runs[1].fill(0);

    bool current = bits[0];
    std::size_t count = 1;
    for (std::size_t i = 1; i < bits.size(); ++i)
    {
        if (bits[i] == current)
        {
            ++count;
        }
        else
        {
            if (count < MAX_RUN)
                ++runs[current][count - 1];
            else
                ++runs[current].back();
            current = bits[i];
            count = 1;
        }
    }
    if (count < MAX_RUN)
        ++runs[current][count - 1];
    else
        ++runs[current].back();

    static const std::array<std::size_t, MAX_RUN> RUNS_LOW  = { 2267, 1079, 502, 223,  90,  90 };
    static const std::array<std::size_t, MAX_RUN> RUNS_HIGH = { 2733, 1421, 748, 402, 223, 223 };

    for (std::size_t bit = 0; bit <= 1; ++bit)
        for (std::size_t i = 0; i < MAX_RUN; ++i)
            if (runs[bit][i] < RUNS_LOW[i] || runs[bit][i] > RUNS_HIGH[i])
                return false;
    return true;
}

// Тест на длинную серию
// Longest run test
bool test4(const Block20000& bits)
{
    static constexpr std::size_t MAX_RUN = 34;
    bool current = bits[0];
    std::size_t count = 1;
    for (std::size_t i = 1; i < bits.size(); ++i)
    {
        if (bits[i] == current)
        {
            ++count;
            if (count >= MAX_RUN)
                return false;
        }
        else
        {
            current = bits[i];
            count = 1;
        }
    }
    return true;
}

// Автокорреляционный тест
// Auto-correlation test
bool test5(const Block20000& bits)
{
    static constexpr std::size_t SIZE = 10'000;
    auto job = [&bits](std::size_t t, bool left) -> std::size_t
    {
        std::size_t from = (left ? 0 : SIZE);
        std::size_t s = 0;
        for (std::size_t i = 0; i < SIZE / 2; ++i)
            s += bits[from + i] ^ bits[from + i + t];
        return s;
    };

    static constexpr std::size_t S_LOW = 2326, S_HIGH = 2674;
    int max_diff = 0;
    std::size_t max_diff_t;

    for (std::size_t t = 1; t <= SIZE / 2; ++t)
    {
        std::size_t s = job(t, true);
        if (s <= S_LOW || s >= S_HIGH)
            return false;
        int diff = std::abs(static_cast<int>(s) - static_cast<int>(SIZE) / 4);
        if (diff > max_diff)
        {
            max_diff = diff;
            max_diff_t = t;
        }
    }
    std::size_t s = job(max_diff_t, false);
    if (s <= S_LOW || s >= S_HIGH)
        return false;

    return true;
}

// Тест на равномерность распределения
// Uniform distribution test
bool test6(const Block20000& bits);

// Сравнительный тест для полиномиальных распределений
// Homogeneity test (comparative test for multinomial distributions)
bool test7(const Block20000& bits);

// Энтропийный тест
// Entropy estimation (Coron's test)
bool test8(const Block20000& bits);

} // namespace ais31
