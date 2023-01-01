#include "my_math.h"

/// math /// 

// Ôóíêöèè äëÿ ðàáîòû ñ áàçîâîé ìàòåìàòèêîé //

uint64_t factorial(uint16_t N) {
	return N > 1 ? N * factorial(N - 1) : 1;
}

uint64_t degree(uint64_t x, uint64_t y) {
	return y ? x * degree(x, y - 1) : 1;
}


std::vector<double_t> aritho(const double_t& a1,
	const double_t& d,
	const uint32_t& size = 2,
	std::vector<double_t> v = {}) {
	v.at(0) = a1; v.resize(size);
	for (auto i = v.begin() + 1; i < v.end(); i++)
		*i = *(i - 1) + d;
	return v;
}

inline double_t aritho_d(const std::vector<double_t>& v) {
	return v.at(1) - v.at(0);
}

inline double_t aritho_sum(std::vector<double_t>& v) {
	return (v.at(0) + v.at(v.size() - 1)) / 2 * v.size();
}

inline double_t aritho_search(const std::vector<double_t>& v,
	const uint32_t& an) {
	return v.size() >= an ? v.at(an - 1)
		: v.at(0) + aritho_d(v) * (an - 1);
}

size_t aritho_search(const double_t& el,
	const std::vector<double_t>& v) {
	if (std::find(v.begin(), v.end(), el) != v.end())
		return std::find(v.begin(), v.end(), el) - v.begin() + 1;

	size_t i = v.size() + 1;
	for (double_t d = aritho_d(v), g = v.at(i - 2) + d;
		g <= el;
		i++, g += d)
		if (g == el)
			return i;
	return NULL;
}

bool is_aritho(const std::vector<double_t>& v) {
	for (auto& el : v)
		if (el + aritho_d(v) != *(&el + 1)
			&& el != v.at(v.size() - 1))
			return false;
	return true;
} 
// cmath + string
double mround(const double& val, const unsigned int& cof = 1){
	using namespace std;
    string sval = to_string(val);
   
    double templ = val + 0.5/(pow(10, cof - 1));
  
    string str  = to_string(templ);
       
    size_t temp = sval.find('.') + cof -1;
   
    str.erase(str.begin() + temp + 1, str.end());
    return stod(str);
} 
