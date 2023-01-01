#pragma once
#include <cstdint>
#include <vector> 
#include <string> 
#include <cmath>

/// factorial of a number ///
uint64_t factorial(uint16_t N);                                   // Ôóíêöèÿ äëÿ âû÷åñëåíèÿ ôàêòîðèàëà ÷èñëà
/// degree of a number ///
uint64_t degree(uint64_t x, uint64_t y);                          // Ôóíêöèÿ äëÿ âû÷åñëåíèÿ ñòåïåíè ÷èñëà


// Ñëåäóþùèå ôóíêöèè ïîçâîëÿþò ðàáîòàòü ñ àðèôìåòè÷åñêîé ïðîãðåññèè //

std::vector<double_t> aritho(const double_t& a1,                  // Ôóíêöèÿ ïîçâîëÿåò ñîçäàòü âåêòîð àðèôìåòè÷åñêîé ïðîãðåññèè
	const double_t& d,
	const uint32_t& size,
	std::vector<double_t> v);

inline double_t aritho_d(const std::vector<double_t>& v);         // Ïîçâîëÿåò óçíàòü ðàçíîñòü ìåæäó ýëåìåíòàìè àðèôìåòè÷åñêîé ïðîãðåññèè

inline double_t aritho_sum(std::vector<double_t>& v);             // Ïîçâîëÿåò óçíàòü ñóììó  àðèôìåòè÷åñêîé ïðîãðåññèè

inline double_t aritho_search                                     // Ïîçâîëÿåò íàéòè ýëåìåíò â ñóùåñòâóþùåé  àðèôìåòè÷åñêîé ïðîãðåññèè
(const std::vector<double_t>& v,
	const uint32_t& an);

size_t aritho_search                                              // Ïîçâîëÿåò íàéòè êàêèì ïî ñ÷åòó èäåò ýëåìåíò â ñóùåñòâóþùåé
(const double_t& el,                          
	const std::vector<double_t>& v);                              // è íå ñóùåñòâóþùåé  àðèôìåòè÷åñêîé ïðîãðåññèè

bool is_aritho(const std::vector<double_t>& v);                   // Ïðîâåðÿåò, ÿâëÿåòñÿ ëè ïåðåäàííàÿ àðèôìåòè÷åñêàÿ ïðîãðåññèÿ àðèôìåòè÷åñêîé ïðîãðåññèåé

/// ranks ///
template <typename T>
uint16_t ranks(const T& val)	                                  // Ôóíêöèÿ äëÿ îïðåäåëèíàÿ êîë-âî ðàçðÿäîâ â ÷èñëå
{
	uint32_t res = 0;
	T temp = val;
	do {
		temp /= 10;
		res++;
	} while (temp > 0);

	return res;
} 


// cmath + string
double mround(const double& val, const unsigned int& cof = 1);
