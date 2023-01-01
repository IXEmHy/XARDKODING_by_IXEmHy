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
}
#endif
