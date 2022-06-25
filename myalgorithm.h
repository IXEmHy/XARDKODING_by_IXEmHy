#pragma once
// P.S. ����������� ���� ��� ����� �� ������� -_- //
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
T convert(const std::string& s)                                   // ����������� ������ � ����� (��� �� ���)
{
	std::istringstream iss(s, std::istringstream::in);
	T res{};
	iss >> res;
	return res;
}

template<typename T>
std::string convert(T val)                                        // ����������� ����� � ������ (��� �� ���)
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

std::string decimal_to_binary(const uint64_t& val)                // ������� ����� �� ���������� � �������� ������� ���������
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

const uint64_t binary_to_decimal(const std::string& str)          // ������� ����� �� �������� ������� ��������� � ����������
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
//  ����� �������  //
//     TODO       //
template<class T>
class Matrix {                                                    //  class Matrix  //                                                              
	T** matrix;                                                   // ���� �������
	uint32_t m, n;                                                // ������ � ������� 
public:
	Matrix(const uint32_t& m = 1,                                 // ����������� �� ��� ��������� ������ Matrix. 
		const uint32_t& n = 1,                                    // ��������� ���-�� �����, ������, � ��, ��� ��������� �������
		const T& aggr = {}) : m(m), n(n)                          
	{
		matrix = new T*[m];
		for (uint32_t i = 0; i < m; i++) {
			matrix[i] = new T[n];
			for (uint32_t g = 0; g < n; g++)
				matrix[i][g] = aggr;
		}
	}

	~Matrix()                                                     // ���������� ������ Matrix
	{
		for (uint32_t i = 0; i < m; i++)
			delete[] matrix[i];
		delete[]matrix;
	}

	auto operator[](const uint32_t& m) const { return matrix[m]; }// ������������� �������� ��������� � ��������� ������� �� �������

	T getM() { return m; }                                        // ������ ��� m
	T getN() { return n; }                                        // ������ ��� m
	T getSize() { return m * n; }                                 // ������ ��� ������� ����� �������
	void getMat() const {										  // ������ ��� ��������� �� ����� ���� �������
		for (uint32_t i = 0; i < m; i++) {
			for (uint32_t g = 0; g < n; g++)
				std::cout << matrix[i][g] << tab;
			std::cout << '\n';
		}
		std::cout.flush();
	}

	void arrgs(const T& top_half,                                 // ����� ��� ���������� ������� ���������� ���������� ���:
		const T& bottom_half,                                     // ������� ��������, ������ ��������, ���������
		const T& diagonal) {    
		for (uint32_t i = 0; i < m; ++i)
			for (uint32_t g = 0; g < n; ++g)
				(*this)[i][g] = i < g ? top_half 
				: i > g ? bottom_half : diagonal;
	}

	const std::string search(T& el) const {                       // ����� ��� ������ �������� � �������
		for (uint32_t i = 0; i < m; i++)
			for (uint32_t g = 0; g < n; g++)
				if ((*this)[i][g] == el)           
					return (std::to_string(i) += ' ')
					+= std::to_string(g);
		return "-1";
	}

	const std::string half(T& el) const {                         // �����, ��� ����������� � ����� �������� ��������� �������
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

	friend bool operator==(const Matrix<T>& m1,                   // ������������� ��������-���� ��� ��������� ���� ������
		const Matrix<T>& m2) {    
		if (m1.sizes() != m2.sizes())
			return false;
		for (uint32_t i = 0; i < m1.getM(); i++)
			for (uint32_t g = 0; g < m1.getN(); g++)
				if (m1[i][g] != m2[i][g])
					return false;
		return true;
	}

	friend std::ostream& operator<<(std::ostream& os,             // ������������� ��������-���� ��� ������ ���� ��������� �������
		const Matrix<T>& matrix) {   
		for (uint32_t i = 0; i < matrix.m; i++) {
			for (uint32_t g = 0; g < matrix.n; g++)
				std::cout << matrix[i][g] << tab;
			std::cout << '\n';
		}
		std::cout.flush();
		return os;
	}
	friend std::istream& operator>>(std::istream& os,             // ������������� ��������-���� ��� ������ ���� ��������� �������
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
{ return num > 0 ? degree_two(num / 2, res + 1) : res; }          // ������� ��� ����������, � ����� ������� ������, ����� ������ ��� ���������� ��������


template<class T>
class VecEno                                                      // ����� VecEno
{
	size_t       size, _capacity;                                 // ������ � �������� �������
	const size_t MAX_SIZE = 65536 / sizeof(T);                    // ������������ ������ ��� ������� (����������� ����� ������� ������ ������ �������� ����� 65536 ����)
	T*           array;                                           // ��� ������
public:
	class iterator                                                // ����� iterator
	{ 
		T* el;                                                    // ������� �� ������� ��������� ��������
	public: 
		iterator(T* elm) { el = elm; }                            // ����������� �������������� ��� ���������� �� ��� // �� ���������
		iterator(iterator* elm) { el = elm->el; }                 // ����������� �����������
		T& operator*() const { return *el; }                      // �������� �������������
		T* operator-(const size_t& it) { return el - it; }        // �������� �������� ����� ���������� � ������ (�����. ����������)
		T* operator+(const size_t& it) { return el + it; }        // �������� �������� ����� ���������� � ������ (�����. ����������)
		T* operator++() { return ++el; }                          // ���������� ���������
		T* operator++(int) { return el++; }                       // ����������� ���������
		T* operator--() { return --el; }                          // ���������� ���������
		T* operator--(int) { return el--; }                       // ����������� ���������
		 
		bool operator>(const iterator& it) { return el > it.el; } // �������� ��������� ���������� (������)
		bool operator<(const iterator& it) { return el < it.el; } // �������� ��������� ���������� (������)
		bool operator!=(const iterator& it) { return el != it.el; }
	};

	VecEno() : size(1), _capacity(2) { array = new T[_capacity]; }  // ����������� �� ���������

	VecEno(const std::initializer_list<T>& _init)                 // ����������� � �������� uniform-�������������
	: size(_init.size()), _capacity(degree(2, degree_two(size))) {
		array = size >= MAX_SIZE ? new T[MAX_SIZE] : new T[_capacity];
		uint32_t i = 0;
		for (auto it = _init.begin(), end = _init.end(); it != end; it++, i++)
			array[i] = *it;
	}
	VecEno(const VecEno<T>& vec)                                  // ����������� �����������
	: size(vec.size), _capacity(degree(2, degree_two(size))) { 
		array = new T[_capacity];
		for (size_t i = 0; i < size; i++)
			array[i] = vec[i];
	}
	~VecEno() { delete[] array; }                                 // ����������

	const size_t getSize() const { return size; }                 // ������ ��� size
	const size_t getCapacity() const { return _capacity; }        // ������ ��� _capacity
	const size_t getMAX_SIZE() const { return MAX_SIZE; }         // ������ ��� MAX_SIZE
	iterator begin() const { return iterator(array); }            // ������ ��� begin
	iterator end() const { return iterator(array + size); }       // ������ ��� end

	void reverse() {
		for (size_t i = 0; i < size / 2; i++)
			swap((*this)[i], (*this)[size - 1 - i]);
	}

	void setCapacity(const size_t& _capacity) {                   // ������ ��� _capacity
		T* temp_ptr = array;
		size_t tempCap = this->_capacity;
		this->_capacity = _capacity;
		array = new T[_capacity];
		for (size_t i = 0; i < tempCap; i++)
			array[i] = temp_ptr[i];
		delete[] temp_ptr;
	}

	void push_back(const T& el) {                                 // �������� ������� � �����
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


	T& at(const size_t& ind) { return size > ind ? array[ind]     // ��������� � �������� �� ������� (���������)
		: throw "����� �� ������� ������� . . .\n"; } 
	T& operator[](const size_t& ind) { return array[ind]; }       // ��������� � �������� �� �������

	friend std::ostream& operator<<                               // ����� ������� (��� ��������)
		(std::ostream& os, const VecEno<T>& vec) {
		for (auto begin = vec.begin(), end = vec.end(); begin < end; begin++)
			std::cout << *begin << '\t';
		std::cout << std::endl;
		return os;
	}
};



double rad_deg(const double& rad) { return rad * RADIAN; }        // ������� ������ � �������
double deg_rad(const double& deg) { return deg * DEGREE; }        // ������� ������� � �������

// reverse //
template<class T>                                                 // ������ ������� ����������� ����
void reverse(T& arr) {
	for (size_t i = 0, size = sizeof(arr) / sizeof(arr[0]); i < size / 2; i++)
		swap(arr[i], arr[size - 1 - i]);
}

// SORT //
// choice sort //
template<typename T>
void sort(T& arr, bool smallset_to_largest = true) {              // ���������� ������� ����������� ����
	for (size_t i = 0, g = 0, size = sizeof(arr) / sizeof(arr[0]); i != size - 1; i++)
		for (g = i + 1; g < size; g++)
			if (arr[i] != arr[g] && arr[i] > arr[g] == smallset_to_largest)
				swap(arr[i], arr[g]);
}

// min element //
template<typename T>
auto min_max(T& arr, bool _min = true) {                          // ���������� ������� ����������� ����
	auto min_max = arr[0];
	for (size_t i = 1, size = sizeof(arr) / sizeof(arr[0]); i != size; i++)
		if (arr[i] != min_max && min_max > arr[i] == _min)
			min_max = arr[i];
	return min_max;
}

const char* layout(const std::string& st) {
	return st.find('q') != st.npos && st.find('Q') != st.npos ? "qwerty" : "������";
}

std::string translit(const std::string& str, const int& from, const int& to) {
	std::string layout[2]
	{ "����������������������������������������������������������������",
	  "qwertyuiop[]asdfghjkl;'zxcvbnm,.QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>" },
		res = str;

	for (size_t i = 0, find = -1; i < str.size(); i++) {
		find = layout[from].find(str[i]);
		res[i] = find != str.npos ? layout[to][find] : res[i];
	}
	return res;
}
#endif
