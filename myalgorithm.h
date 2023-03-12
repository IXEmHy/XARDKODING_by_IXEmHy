#pragma once
// P.S. Êîììåíòàðèè ïîêà ÷òî áóäóò íà ðóññêîì -_- //
#ifndef ON
#define ON

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include "SimpleTimer.h"
#include "my_math.h"

typedef SimpleTimer timer;

#define PI 3.141592653589793
#define RADIAN 180/PI
#define DEGREE PI/180

namespace thread = std::this_thread;
namespace chrono = std::chrono;


/// convert str in number or nymber vice versa  ///
template<typename T>
T convert(const std::string& s)                                   // Êîíâåðòàöèÿ ñòðîêè â ÷èñëî (Êîä íå ìîé)
{
	std::istringstream iss(s, std::istringstream::in);
	T res{};
	iss >> res;
	return res;
}

template<typename T>
std::string convert(T val)                                        // Êîíâåðòàöèÿ ÷èñëà â ñòðîêó (Êîä íå ìîé)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

/// swap number ///
template<typename T>
void swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

std::string decimal_to_binary(const uint64_t& val)                // Ïåðåâîä ÷èñëà èç äåñÿòè÷íîé â äâîè÷íóþ ñèñòåìó ñ÷èñëåíèÿ
{
	auto temp = val;
	std::string res;

	do {
		res += temp % 2 + '0';
		temp /= 2;
	} while (temp > 0);

	std::reverse(res.begin(), res.end());

	return res;
}

const uint64_t binary_to_decimal(const std::string& str)          // Ïåðåâîä ÷èñëà èç äâîè÷íîé ñèñòåìû ñ÷èñëåíèÿ â äåñÿòè÷íóþ
{
	if (str.size() > 64)
		return 0;
	uint64_t res = 0;
	for (size_t i = 0; i < str.size(); i++)
		res = res * 2 + str.at(i) - '0';
	return res;
}

///  matrix  ///
/// class Matrix ///
//  êëàññ Ìàòðèöà  //
//     TODO       //
template<class T>
class Matrix {                                                    //  class Matrix  //                                                              
	T** matrix;                                                   // Ñàìà ìàòðèöà
	uint32_t m, n;                                                // Ñòðîêè è êîëîííû 
public:
	Matrix(const uint32_t& m = 1,                                 // Êîíñòðóêòîð íå ïîë óìîë÷àíèþ êëàññà Matrix. 
		const uint32_t& n = 1,                                    // Ïðèíèìàåò êîë-âî ñòðîê, êîëîíí, è òî, ÷åì çàïîëíèòü ìàòðèöó
		const T& aggr = {}) : m(m), n(n)                          
	{
		matrix = new T*[m];
		for (uint32_t i = 0; i < m; i++) {
			matrix[i] = new T[n];
			for (uint32_t g = 0; g < n; g++)
				matrix[i][g] = aggr;
		}
	}

	~Matrix()                                                     // Äåñòðóêòîð êëàññà Matrix
	{
		for (uint32_t i = 0; i < m; i++)
			delete[] matrix[i];
		delete[]matrix;
	}

	auto operator[](const uint32_t& m) const { return matrix[m]; }// ïåðåãðóæåííûé îïåðàòîð îáðàùåíèå ê ýåëåìåíòó ìàññèâà ïî èíäåêñó

	T getM() { return m; }                                        // Ãåòòåð äëÿ m
	T getN() { return n; }                                        // Ãåòòåð äëÿ m
	T getSize() { return m * n; }                                 // Ãåòòåð äëÿ ðàçìåðà âñåãî ìàññèâà
	void getMat() const {										  // Ãåòòåð äëÿ âûâåäåíèÿ íà ýêðàí âñåé ìàòðèöû
		for (uint32_t i = 0; i < m; i++) {
			for (uint32_t g = 0; g < n; g++)
				std::cout << matrix[i][g] << tab;
			std::cout << '\n';
		}
		std::cout.flush();
	}

	void arrgs(const T& top_half,                                 // Ìåòîä äëÿ çàïîëíåíèÿ ìàòðèöû óêàçàííûìè çíà÷åíèÿìè äëÿ:
		const T& bottom_half,                                     // âåðõíåé ïîëîâèíû, íèæíåé ïîëîâèíû, äèàãîíàëè
		const T& diagonal) {    
		for (uint32_t i = 0; i < m; ++i)
			for (uint32_t g = 0; g < n; ++g)
				(*this)[i][g] = i < g ? top_half 
				: i > g ? bottom_half : diagonal;
	}

	const std::string search(T& el) const {                       // Ìåòîä äëÿ ïîèñêà ýëåìåíòà â ìàòðèöå
		for (uint32_t i = 0; i < m; i++)
			for (uint32_t g = 0; g < n; g++)
				if ((*this)[i][g] == el)           
					return (std::to_string(i) += ' ')
					+= std::to_string(g);
		return "-1";
	}

	const std::string half(T& el) const {                         // Ìåòîä, äëÿ îïðåäåëåíèÿ â êàêîé ïîëîâèíå íàõîäèòñÿ ýëåìåíò
		if (search(el) == "-1")
			return "Not found . . .\n";

		std::string i = search(el), g = i;
		i.erase(i.find(" ")); g.erase(0, g.find(" ") + 1);

		if (convert<int>(i) < convert<int>(g))
			return "top half\n";
		else if (convert<int>(i) > convert<int>(g))
			return "bottom half\n";
		return "Diagonal\n";
	}

	friend bool operator==(const Matrix<T>& m1,                   // Ïåðåãðóæåííûé îïåðàòîð-äðóã äëÿ ñðàâíåíèÿ äâóõ ìàòðèö
		const Matrix<T>& m2) {    
		if (m1.sizes() != m2.sizes())
			return false;
		for (uint32_t i = 0; i < m1.getM(); i++)
			for (uint32_t g = 0; g < m1.getN(); g++)
				if (m1[i][g] != m2[i][g])
					return false;
		return true;
	}

	friend std::ostream& operator<<(std::ostream& os,             // Ïåðåãðóæåííûé îïåðàòîð-äðóã äëÿ âûâîäà âñåõ ýëåìåíòîâ ìàòðèöû
		const Matrix<T>& matrix) {   
		for (uint32_t i = 0; i < matrix.m; i++) {
			for (uint32_t g = 0; g < matrix.n; g++)
				std::cout << matrix[i][g] << tab;
			std::cout << '\n';
		}
		std::cout.flush();
		return os;
	}
	friend std::istream& operator>>(std::istream& os,             // Ïåðåãðóæåííûé îïåðàòîð-äðóã äëÿ âûâîäà âñåõ ýëåìåíòîâ ìàòðèöû
		const Matrix<T>& matrix) {    
		for (uint32_t i = 0; i < matrix.m; i++) {
			for (uint32_t g = 0; g < matrix.n; g++) {
				std::cout << "Enter element:\n" 
					<< i << " - Vertically\n" 
					<< g << " - Horizontally\n";
				std::cin >> matrix[i][g];
			}
			std::cout << '\n';
		}
		std::cout.flush();
		return os;
	}
};


size_t degree_two(const size_t& num, size_t res = 0)   
{ return num > 0 ? degree_two(num / 2, res + 1) : res; }          // Ôóíêöèÿ äëÿ âû÷åñëåíèÿ, â êàêîé ñòåïåíè äâîéêà, áóäåò áîëüøå ÷åì ïåðåäàííûé àðãóìåíò


template<class T>
class VecEno                                                      // êëàññ VecEno
{
	size_t       size, _capacity;                                 // ðàçìåð è êàïàñèòè âåêòîðà
	const size_t MAX_SIZE = 65536 / sizeof(T);                    // ìàêñèìàëüíûé ðàçìåð äëÿ âåêòîðà (ìàêñèìàëüíî ìîæíî ñîçäàòü îáúåêò ðàçìåð êîòîðîãî áóäåò 65536 áàéò)
	T*           array;                                           // ñàì ìàññèâ
public:
	class iterator                                                // êëàññ iterator
	{ 
		T* el;                                                    // ýëåìåíò íà êîòîðûé óêàçûâàåò èòåðàòîð
	public: 
		iterator(T* elm) { el = elm; }                            // êîíñòðóêòîð èíèöèàëèçàöèåé óæå óêàçàòåëåì èç âíå // íå áåçîïàñíî
		iterator(iterator* elm) { el = elm->el; }                 // êîíñòðóêòîð êîïèðîâàíèÿ
		T& operator*() const { return *el; }                      // îïåðàòîð ðàçûìåíîâàíèÿ
		T* operator-(const size_t& it) { return el - it; }        // îïåðàòîð ðàçíîñòè ìåæäó óêàçàòåëåì è ÷èñëîì (àðèôì. óêàçàòåëåé)
		T* operator+(const size_t& it) { return el + it; }        // îïåðàòîð ñëîæåíèÿ ìåæäó óêàçàòåëåì è ÷èñëîì (àðèôì. óêàçàòåëåé)
		T* operator++() { return ++el; }                          // ïðåôèêñíûé èíêðèìåíò
		T* operator++(int) { return el++; }                       // ïîñòôèêñíûé èíêðèìåíò
		T* operator--() { return --el; }                          // ïðåôèêñíûé äåêðèìåíò
		T* operator--(int) { return el--; }                       // ïîñòôèêñíûé äåêðèìåíò
		 
		bool operator>(const iterator& it) { return el > it.el; } // îïåðàòîð ñðàâíåíèÿ óêàçàòåëåé (áîëüøå)
		bool operator<(const iterator& it) { return el < it.el; } // îïåðàòîð ñðàâíåíèÿ óêàçàòåëåé (ìåíüøå)
		bool operator!=(const iterator& it) { return el != it.el; }
	};

	VecEno() : size(1), _capacity(2) { array = new T[_capacity]; }  // êîíñòðóêòîð ïî óìîë÷àíèþ

	VecEno(const std::initializer_list<T>& _init)                 // êîíñòðóêòîð ñ çàäàíèåì uniform-èíèöèàëèçàöèè
	: size(_init.size()), _capacity(degree(2, degree_two(size))) {
		array = size >= MAX_SIZE ? new T[MAX_SIZE] : new T[_capacity];
		uint32_t i = 0;
		for (auto it = _init.begin(), end = _init.end(); it != end; it++, i++)
			array[i] = *it;
	}
	VecEno(const VecEno<T>& vec)                                  // êîíñòðóêòîð êîïèðîâàíèÿ
	: size(vec.size), _capacity(degree(2, degree_two(size))) { 
		array = new T[_capacity];
		for (size_t i = 0; i < size; i++)
			array[i] = vec[i];
	}
	~VecEno() { delete[] array; }                                 // äåñòðóêòîð

	const size_t getSize() const { return size; }                 // ãåòòåð äëÿ size
	const size_t getCapacity() const { return _capacity; }        // ãåòòåð äëÿ _capacity
	const size_t getMAX_SIZE() const { return MAX_SIZE; }         // ãåòòåð äëÿ MAX_SIZE
	iterator begin() const { return iterator(array); }            // ãåòòåð äëÿ begin
	iterator end() const { return iterator(array + size); }       // ãåòòåð äëÿ end

	void reverse() {
		for (size_t i = 0; i < size / 2; i++)
			swap((*this)[i], (*this)[size - 1 - i]);
	}

	void setCapacity(const size_t& _capacity) {                   // ñåòòåð äëÿ _capacity
		T* temp_ptr = array;
		size_t tempCap = this->_capacity;
		this->_capacity = _capacity;
		array = new T[_capacity];
		for (size_t i = 0; i < tempCap; i++)
			array[i] = temp_ptr[i];
		delete[] temp_ptr;
	}

	void push_back(const T& el) {                                 // äîáàâèòü ýëåìåíò â êîíåö
		if (size < _capacity) {
			array[size] = el;
			++size;
		}
		else {
			setCapacity(degree(2, degree_two(size)));
			push_back(el);
		}
	}
	void pop_back() { size--; }


	T& at(const size_t& ind) { return size > ind ? array[ind]     // îáðàòèòñÿ ê ýëåìåíòó ïî èíäåêñó (áåçîïàñíî)
		: throw "Âûõîä çà ïðåäåëû âåêòîðà . . .\n"; } 
	T& operator[](const size_t& ind) { return array[ind]; }       // îáðàòèòñÿ ê ýëåìåíòó ïî èíäåêñó

	friend std::ostream& operator<<                               // âûâîä âåêòîðà (äëÿ óäîáñòâà)
		(std::ostream& os, const VecEno<T>& vec) {
		for (auto begin = vec.begin(), end = vec.end(); begin < end; begin++)
			std::cout << *begin << '\t';
		std::cout << std::endl;
		return os;
	}
};



double rad_deg(const double& rad) { return rad * RADIAN; }        // ïåðåâîä ðàäèàí â ãðóäóñû
double deg_rad(const double& deg) { return deg * DEGREE; }        // ïåðåâîä ãðàäóñû â ðàäèàíû

// reverse //
template<class T>                                                 // ðåâåðñ ìàññèâà âñòðîåííîãî òèïà
void reverse(T& arr) {
	for (size_t i = 0, size = sizeof(arr) / sizeof(arr[0]); i < size / 2; i++)
		swap(arr[i], arr[size - 1 - i]);
}

// SORT //
// choice sort //
template<typename T>
void sort(T& arr, bool smallset_to_largest = true) {              // ñîðòèðîâêà ìàññèâà âñòðîåííîãî òèïà
	for (size_t i = 0, g = 0, size = sizeof(arr) / sizeof(arr[0]); i != size - 1; i++)
		for (g = i + 1; g < size; g++)
			if (arr[i] != arr[g] && arr[i] > arr[g] == smallset_to_largest)
				swap(arr[i], arr[g]);
}

// min element //
template<typename T>
auto min_max(T& arr, bool _min = true) {                          // ñîðòèðîâêà ìàññèâà âñòðîåííîãî òèïà
	auto min_max = arr[0];
	for (size_t i = 1, size = sizeof(arr) / sizeof(arr[0]); i != size; i++)
		if (arr[i] != min_max && min_max > arr[i] == _min)
			min_max = arr[i];
	return min_max;
}



std::string layout(const std::string& st) {
	for(auto& el : st) { 
        if(!((el >= 'a' && el <= 'z') || (el >= 'A' && el <= 'Z') || el == ' ' || (el >= 0 && el <= 27)))  return "other"; 
    } 
    return "qwerty"; 
}

std::string translit(const std::string& str, const int& from, const int& to) {
	std::string layout[2]
	{ "éöóêåíãøùçõúôûâàïðîëäæýÿ÷ñìèòüáþÉÖÓÊÅÍÃØÙÇÕÚÔÛÂÀÏÐÎËÄÆÝß×ÑÌÈÒÜÁÞ",
	  "qwertyuiop[]asdfghjkl;'zxcvbnm,.QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>" },
		res = str;

	for (size_t i = 0, find = -1; i < str.size(); i++) {
		find = layout[from].find(str[i]);
		res[i] = find != str.npos ? layout[to][find] : res[i];
	}
	return res;
}//  TODO  //
 size_t ind_n(const std::string& val, const int32_t& del = '0') { // function for colculate index last symbol (del) on the right
 	size_t ind = val.size();
 	std::string res = val;
 	for(size_t i{}; 
            	i < res.size() && res.at(res.size()-i-1) == '0'; 
            	++i, --ind) ;
	  return ind;
}
	    
template<class T,
                std::enable_if_t<std::is_integral<std::remove_reference_t<T>>::value, bool> = true> 
std::string convert(T&& value, const uint8_t& m) { // Function for translate integer number into another system number
    if(m != 10) {
        auto temp = abs(value); // abs(value) because value % m, where value is negative number will heve the negative meaning. For example: -10 % 3 == -1. 
        std::vector<std::pair<std::string, uint8_t>> prefix = {{"0b", 2}, {"0o", 8}, {"", 10}, {"0x", 16}}; // Need for buity. 
    	std::string res;
        
	    do {
	    	res += (temp % m < 10 ? 
	    	        temp % m + '0' // if temp % m < 10, add into res temp % m + '0'.Its mean that temp % m < 10 and need to sum with '0' to get the number of this symbol. For examle: 17 % 10 + '0' == '7'
	    	        : temp % m + 55); // Else add into res symbol == temp % m + 55. For example: 15 % 16 + 55 == 'A'
	    	temp /= m;
	    } while (temp > 0);

	    std::reverse(res.begin(), res.end()); // reverse result.For example: 010101 to 101010
	    
	    auto it = std::find_if(_ve(prefix), [&](std::pair<std::string, uint8_t>& p) { return p.second == m; }); // Find in prefix the pair, which has the second element == m. For example: m == 2. It will have the meaning, which == prefix.begin()
	    res.insert(0, (it != prefix.end() ? it->first : "")); // insert prefix. For example: before: 1A after 0x1A (if m == 16)
	    
	    if (value < 0) // if value was negative (-10) add in the begin result symbol "-"
	        res.insert(it != prefix.end() ? 2 : 0, "-"); /*if it != prefix.end(), add "-" in 2 index.
	        Else put it in 0 index.
	        For example: res == "0x10", and value == -16. Result of this call method will be: res == "0x-10".
	                     res == "10", and value == -15. Result of this call method will be: res == "-10". */
	    return res;
    } 
	return std::to_string(value);
}

template<class T,
                std::enable_if_t<std::is_arithmetic<std::remove_reference_t<T>>::value && !std::is_integral<std::remove_reference_t<T>>::value, bool> = true> 
std::string convert(T&& value, const uint8_t& m) { // Function for translate floating number into another system number.
	if(m != 10) {
		auto val = int64_t(value);
	    using float_b = std::is_same<std::remove_reference_t<T>, float>; // if T is "float" type
	    typename std::conditional<float_b::value, float, long double>::type res_float_part = abs(value) - abs(val); // if T is "float" type to declare variable type based on float_b value
	    
		size_t cex = float_b::value ? 6 : 15; // rounding precision
		std::string res;
		for(size_t i{}; i < cex && res_float_part != int64_t(res_float_part); ++i) {
			res += std::to_string(int64_t(res_float_part * m)); // 0.6 * 2 == 1.2. int64_t(1.0) convert.to string and add into res
			res_float_part = res_float_part * m - int64_t(res_float_part * m); // 1.2 - 1 == 0.2
		}
      	res.erase(ind_n(res)); // delete all the '0' at the end of res. For example: res == "0.980000", will delete 4 zero, and res wil become == "0.98"
      	
	    std::reverse(_ve(res));
    	res.insert(0, convert(val, m) + (ind_n(res) ? "." : "")); // add "." if ind_n(res) == 0
        
        return res; 
	}
	
	std::string res = std::to_string(value);
	res.erase(ind_n(res), res.size());
    return res; 
}

std::string convert(const uint8_t& n, const std::string& value, const uint8_t& m) { // Function to translete number from one number system into another system number
	int64_t res = 0;
	std::vector<std::pair<std::string, uint8_t>> vec = {{"0b", 2}, {"0o", 8}, {"", 10}, {"0x", 16}};

    std::string val = std::string(value.begin(), std::find(_ve(value), '.')); // erase integer number from value. For example: "14646.97" val became "14646"
	if (std::find_if(_ve(vec), [&](std::pair<std::string, uint8_t>& p) { return p.second == n; }) != vec.end())
	    val.erase(0, 2); // erase prefix 
	    
	if(val.at(0) == '-') val.erase(0, 1); 
	
	for (size_t i = 0; i < val.size(); i++)
	    res = res * n + val.at(i) - (val.at(i) - '0' < 10 ? '0' : 55);
	 
	res = value.at(2) == '-' ? -res : res;
	if(value.find('.') != value.npos) { // if value has '.' it means that value is floating number, and need translate its floating part into m-system number
		std::string float_part = std::string(std::find(_ve(value), '.') + 1, value.back() != 'f' ? value.end() : value.end()-1);
		long double res2{}; 
		
		for(int i{-1}; abs(i) < 16 && abs(i) < float_part.size() + 1; --i) { 
			char temp2 = float_part.at(abs(i) - 1);
			res2 += (temp2 - (temp2 - '0' < 10 ? '0' : 55)) * pow(n, i);
		}
		
		std::string templ = std::to_string(value.back() != 'f' ? res2 : float(res2));
		templ.erase(0, 1); // erase first symbol beacuse it's '0' and it doesn't need
		return convert(stod(std::to_string(res) + templ), m); // convert res + templ into m-system number
	} 
	else
    	return convert(res, m);

}

class NumberSystemClassMoreCondition {
	string val;
	size_t num_sys_our = 10;
public:
    template<class U,
             std::enable_if_t<std::is_arithmetic<U>::value, bool> = true>
	NumberSystemClassMoreCondition(U&& u) {
		val = std::to_string(std::forward<U>(u));
	}

    NumberSystemClassMoreCondition(const std::string& another, size_t num_sys = 10) : val(another), num_sys_our(num_sys) {}
    
    std::string operator()(size_t num_sys) {
    	return std::string(val +
    	" is in a " + std::to_string(num_sys_our) +
    	"-number system.\nAnd it's also " +
    	convert(num_sys_our, val, num_sys) +
    	" in a " + std::to_string(num_sys) + "-number system");
    }
     
    NumberSystemClassMoreCondition& operator=(int64_t num_sys) {
    	val = convert(num_sys_our, val, num_sys);
    	return *this;
    }
    
    void set(const std::string& vall, size_t num_sys) {
    	val = vall;
    	num_sys_our = num_sys;
    	
    }
     
    friend std::ostream& operator<<(std::ostream& os, const NumberSystemClassMoreCondition& obj) {
    	os << obj.val << " in a " << obj.num_sys_our << "-system number";
    	return os;
    }
};

using SystemNumber = NumberSystemClassMoreCondition;
 

double log(double a, double val) {
	return log(val) / log(a);
}
#endif
