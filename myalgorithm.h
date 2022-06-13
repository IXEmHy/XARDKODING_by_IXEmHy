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

typedef SimpleTimer timer;
typedef std::string string;
const string tab = "    ";

#define PI 3.141592653589793
#define RADIAN 180/PI
#define DEGREE PI/180

namespace thread = std::this_thread;
namespace chrono = std::chrono;



///  return begin elements  ///
template <typename T, size_t N>
const T* begin(const T(&str)[N]) { return str; }

///  return end elements  ///
template <typename T, size_t N>
const T* end(const T(&str)[N]) { return str + N; }

/// return size array ///
template <typename T, size_t N>
const T size(const T(&str)[N]) { return N; }


/// ranks ///
template <typename T>
uint16_t ranks(const T& val)	                                  // ������� ��� ����������� ���-�� �������� � �����
{
	uint32_t res = 0;
	T temp = val;
	do {
		temp /= 10;
		res++;
	} while (temp > 0);

	return res;
}


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


/// factorial of a number ///
uint64_t factorial(uint16_t N)                                    // ������� ��� ���������� ���������� �����
{ return N > 1 ? N * factorial(N - 1) : 1; }    


/// degree of a number ///
uint64_t degree(uint64_t x, uint64_t y)                           // ������� ��� ���������� ������� �����
{ return y ? x * degree(x, y - 1) : 1; }    


/// swap number ///
template<typename T>
void swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}


//   string     //
///  operators  ///
std::string operator*(const std::string& str,                     // ������������� �������� �������� *, 
	const uint32_t& num)                                          // ��������� �������������� ������ ��������� ��� - �� ���
{ return num ? str + operator*(str, num - 1) : ""; }                 

std::string operator*(const uint32_t& num,                        // ������������� �������� �������� *, 
	const std::string& str)										  // ��������� �������������� ������ ��������� ���-�� ���
{ return operator*(str, num); }    

std::string& operator/(std::string& str,                          // ������������� �������� �������� /, ��������� ������� ��� ���������(str2) �� ������ (str)
	const std::string& str2) {
	return str.find(str2) != str.npos ? 
		operator/(str.erase(str.find(str2), str2.length()), str2) 
		: str; }    

std::string& operator-(std::string& str,                          // ������������� �������� �������� -, ������� ���������(str2) �� ������ (str)
	const std::string& str2) {
	return str.find(str2) != str.npos ?
		str.erase(str.find(str2), str2.length()) 
		: str; }	 


bool operator==(const std::string& str, const std::string& str2)  // ������������� �������� �������� ==, ��������� �������� ��� ������ ����� �����
{ return str.size() == str2.size() && str.find(str2) != str.npos; }    

bool operator!=(const std::string& str, const std::string& str2)  // ������������� �������� �������� !=, ��������� ��������� �� ����������� ��� ������ ����� �����
{ return str.size() != str2.size() || str.find(str2) == str.npos; }  

// function //
size_t strlen_t(const char* str, size_t len = 0)                  // ������� ��������� ������ ������ ������ (� ���� ������� ������ �� ������ ������������� ����)
{ return str[len] ? strlen_t(str, len + 1) : len; }    


/// math ///
// ������� ��� ������ � ������� ����������� //
// ��������� ������� ��������� �������� � �������������� ���������� //
std::vector<double_t> aritho(const double_t& a1,                  // ������� ��������� ������� ������ �������������� ����������
	const double_t& d, 
	const uint32_t& size, 
	std::vector<double_t> v) {    
	v.at(0) = a1; v.resize(size);
	for (auto i = v.begin() + 1; i < v.end(); i++)
		*i = *(i - 1) + d;
	return v;
}

inline double_t aritho_d(const std::vector<double_t>& v)          // ��������� ������ �������� ����� ���������� �������������� ����������
{ return v.at(1) - v.at(0); }    

inline double_t aritho_sum(std::vector<double_t>& v)              // ��������� ������ �����  �������������� ����������
{ return (v.at(0) + v.at(v.size() - 1)) / 2 * v.size(); }    

inline double_t aritho_search(const std::vector<double_t>& v,     // ��������� ����� ������� � ������������  �������������� ����������
	const uint32_t& an) { 
    return v.size() >= an ? v.at(an - 1) 
		: v.at(0) + aritho_d(v) * (an - 1); }    

size_t aritho_search(const double_t& el,                          // ��������� ����� ����� �� ����� ���� ������� � ������������
	const std::vector<double_t>& v) {                             // � �� ������������  �������������� ����������
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

bool is_aritho(const std::vector<double_t>& v) {                  // ���������, �������� �� ���������� �������������� ���������� �������������� �����������
	for (auto& el : v)
		if (el + aritho_d(v) != *(&el + 1) 
			&& el != v.at(v.size() - 1))
			return false;
	return true;
}



void timer_with_chrono()                                          // ������ (�������-_*)
{
	char sec = 0, min = 0, hour = 0, day = 0;
	while (day < 1)
	{
		timer a;
		std::cout << "Passed time: "
			<< "sec: " << sec << string(" ") * (5 - ranks(sec))
			<< "min: " << min << string(" ") * (5 - ranks(min)) 
			<< "hour: " << hour << '\r';
		thread::sleep_for(chrono::milliseconds(999));

		if (sec == 60) {
			++min;
			if (min == 60) {
				++hour;
				if (hour == 24) {
					++day;
					std::cout << "Timer stoped!\nBye!\n";
				}
				min = 0;
			}
			sec = 0;
		}
		++sec;
	}
}

std::string decimal_to_binary(const uint64_t& val)                // ������� ����� �� ���������� � �������� ������� ���������
{
	auto temp = val;
	std::string res;

	do {
		res += std::to_string(temp % 2);
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

// . . . TODO? . . .   //
//       SORT         //
/* template <typename T>
void mySort(const T arr[], const T * end)
{
	std::sort(arr, end, [](int a, int b)
	{
		return a > b;
	});
	const size_t size = (end - arr) / sizeof(T);
	T temp[size];
	for (int i = 0, g = 10 - 1, c = 0; i < (end - arr) / sizeof(T); i++)
		if (i % 2 == 0) {
			temp[c] = arr[i];
			c++;
		}
		else {
			temp[g] = arr[i];
			g--;
		}
	for (auto i = 0; i < (end - arr) / sizeof(T); i++)
		arr[i] = temp[i];
}
Original version:
int arr[10], temp[10], i = 0, g = 0, c = 0;
	for (auto &el : arr)
		el = rand() % 10 + 1;
	for (auto &el : arr)
		cout << el << endl;
	/*for (i = 0, g = 10 - 1; i < 10; i++)
		if (i % 2 == 0) {
			temp[c] = arr[i];
			c++;
		}
		else {
			temp[g] = arr[i];
			g--;
		}
	cout << endl;
	for (const auto &el : temp)
		cout << el << endl;
*/

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
					<< i << " -  Vertically\n" 
					<< g << " - Horizontally\n";
				std::cin >> matrix[i][g];
			}
			std::cout << '\n';
		}
		std::cout.flush();
		return os;
	}
	//  class Matrix end  //
};


size_t degree_two(const size_t& num, size_t res = 0)   
{ return num ? degree_two(num / 2, res + 1) : res; }              // ������� ��� ����������, � ����� ������� ������, ����� ������ ��� ���������� ��������


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

	VecEno(const std::initializer_list<T>& _init)                   // ����������� � �������� uniform-�������������
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
	const size_t getCapacity() const { return _capacity; }         // ������ ��� _capacity
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
#endif
