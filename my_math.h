#pragma once
#include <cstdint>
#include <vector>

/// factorial of a number ///
uint64_t factorial(uint16_t N);                                   // Функция для вычесления факториала числа
/// degree of a number ///
uint64_t degree(uint64_t x, uint64_t y);                          // Функция для вычесления степени числа


// Следующие функции позволяют работать с арифметической прогрессии //

std::vector<double_t> aritho(const double_t& a1,                  // Функция позволяет создать вектор арифметической прогрессии
	const double_t& d,
	const uint32_t& size,
	std::vector<double_t> v);

inline double_t aritho_d(const std::vector<double_t>& v);         // Позволяет узнать разность между элементами арифметической прогрессии

inline double_t aritho_sum(std::vector<double_t>& v);             // Позволяет узнать сумму  арифметической прогрессии

inline double_t aritho_search                                     // Позволяет найти элемент в существующей  арифметической прогрессии
(const std::vector<double_t>& v,
	const uint32_t& an);

size_t aritho_search                                              // Позволяет найти каким по счету идет элемент в существующей
(const double_t& el,                          
	const std::vector<double_t>& v);                              // и не существующей  арифметической прогрессии

bool is_aritho(const std::vector<double_t>& v);                   // Проверяет, является ли переданная арифметическая прогрессия арифметической прогрессией

/// ranks ///
template <typename T>
uint16_t ranks(const T& val)	                                  // Функция для определиная кол-во разрядов в числе
{
	uint32_t res = 0;
	T temp = val;
	do {
		temp /= 10;
		res++;
	} while (temp > 0);

	return res;
}