#ifndef TESTS_H
#define TESTS_H

#include "block.h"

namespace ais31
{

using Block3145728 = my::Block<(1 << 16) * 48>;
using Block20000 = my::Block<20'000>;
using Block10000 = my::Block<10'000>;

// Тест бесповторности
// Disjointedness test
bool test0(const Block3145728& bits);

// Тест числа единиц
// Monobit test
bool test1(const Block20000& bits);

// Покер-тест
// Poker test
bool test2(const Block20000& bits);

// Тест серий
// Runs test
bool test3(const Block20000& bits);

// Тест на длинную серию
// Longest run test
bool test4(const Block20000& bits);

// Автокорреляционный тест
// Auto-correlation test
bool test5(const Block20000& bits);

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

#endif // TESTS_H
