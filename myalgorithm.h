#pragma once
// P.S. ����������� ���� ��� ����� �� ������� -_- //

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include "SimpleTimer.h"

typedef SimpleTimer timer;
constexpr auto tab = "    ";
typedef std::string string;
#define RS std::to_string

namespace thread = std::this_thread;
namespace chrono = std::chrono;



///  return begin elements  ///
template <size_t N>
const char* begin(const char(&str)[N]) { return str; }
template <size_t N>
const int64_t* begin(const int64_t(&arr)[N]) { return arr; }
template <size_t N>
const int32_t* begin(const int32_t(&arr)[N]) { return arr; }
template <size_t N>
const int16_t* begin(const int16_t(&arr)[N]) { return arr; }

// ��� ���� ������������� ������� �������� ��������� �� ������ ������ //


///  return end elements  ///
template <size_t N>
const char* end(const char(&str)[N]) { return str + N; }
template <size_t N>
const int64_t* end(const int64_t(&arr)[N]) { return arr + N; }
template<size_t N>
const int32_t* end(const int32_t(&arr)[N]) { return arr + N; }
template<size_t N>
const int16_t* end(const int16_t(&arr)[N]) { return arr + N; }

// ��� ���� ������������� ������� �������� ��������� �� ������� ������ //




/// return size array ///
template <size_t N>
const int64_t size(const char(&str)[N]) { return N; }
template <size_t N>
const int64_t size(const int64_t(&arr)[N]) { return N; }
template <size_t N>
const int64_t size(const int32_t(&arr)[N]) { return N; }
template <size_t N>
const int64_t size(const int16_t(&arr)[N]) { return N; }

// ��� ���� ������������� ������� �������� ������ ������ //


/// ranks ///
template <typename T>
uint16_t ranks(const T& val)	// ������� ��� ����������� ���-�� �������� � �����
{
	uint16_t res = 0;
	T temp = val;
	do {
		temp /= 10;
		res++;
	} while (int64_t(temp) > 0);

	return res;
}


/// convert str in number or nymber vice versa  ///
template<typename T>
T convert(const std::string& s)    // ����������� ������ � ����� (��� �� ���)
{
	std::istringstream iss(s, std::istringstream::in);
	T res{};
	iss >> res;
	return res;
}

template<typename T>
std::string convert(T val)    // ����������� ����� � ������ (��� �� ���)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}


/// factorial of a number ///
uint64_t factorial(uint32_t N) { return N > 1 ? N * factorial(N - 1) : 1; }    // ������� ��� ���������� ���������� �����


/// degree of a number ///
uint64_t degree(uint64_t x, uint64_t y) { return y ? x * degree(x, y - 1) : 1; }    // ������� ��� ���������� ������� �����


/// swap number ///
void swap(int64_t* a, int64_t* b) {
	int64_t temp = *a;
	*a = *b;
	*b = temp;
}
void swap(int64_t& a, int64_t& b) {
	int64_t temp = a;
	a = b;
	b = temp;
}

void swap(int32_t* a, int32_t* b) {
	int32_t temp = *a;
	*a = *b;
	*b = temp;
}
void swap(int32_t& a, int32_t& b) {
	int32_t temp = a;
	a = b;
	b = temp;
}

void swap(int16_t* a, int16_t* b) {
	int16_t temp = *a;
	*a = *b;
	*b = temp;
}
void swap(int16_t& a, int16_t& b) {
	int16_t temp = a;
	a = b;
	b = temp;
}
/// swap to fraction ///
void swap(float_t* a, float_t* b) {
	float_t temp = *a;
	*a = *b;
	*b = temp;
}

void swap(float_t& a, float_t& b) {
	float_t temp = a;
	a = b;
	b = temp;
}

void swap(double_t* a, double_t* b) {
	double_t temp = *a;
	*a = *b;
	*b = temp;
}
void swap(double_t& a, double_t& b) {
	double_t temp = a;
	a = b;
	b = temp;
}

// ���� ������������� ������� ������ swap �����/���������� ����� �����

//   string     //
///  operators  ///
std::string operator*(const std::string& str, const uint32_t& num) { return num ? str + operator*(str, num - 1) : ""; }    // ������������� �������� �������� *, ��������� �������������� ������ ��������� ���-�� ���
std::string operator*(const uint32_t& num, const std::string& str) { return operator*(str, num); }    // ������������� �������� �������� *, ��������� �������������� ������ ��������� ���-�� ���

template <typename T>
std::string operator+(const std::string& str, const T& num) { return str + std::to_string(num); }    // ������������� �������� �������� +, ������������� ����� � �������
template <typename T>
std::string operator+(const T& num, const std::string& str) { return str + std::to_string(num); }    // ������������� �������� �������� +, ������������� ����� � �������


std::string& operator/(std::string& str, const std::string& str2) {
	return str.find(str2) != str.npos ? operator/(str.erase(str.find(str2), str2.length()), str2) : str; }    // ������������� �������� �������� /, ��������� ������� ��� ���������(str2) �� ������ (str)

std::string& operator/=(std::string& str, const std::string& str2) {
	return str.find(str2) != str.npos ? operator/=(str.erase(str.find(str2), str2.length()), str2) : str; }    // ������������� �������� �������� /=, ��������� ������� ��� ���������(str2) �� ������ (str)


std::string& operator-(std::string& str, const std::string& str2) {
	return str.find(str2) != str.npos ? str.erase(str.find(str2), str2.length()) : str; }	 // ������������� �������� �������� -, ������� ���������(str2) �� ������ (str)

bool operator == (const std::string& str, const std::string& str2) { return str.size() == str2.size() && str.find(str2) != str.npos; }    // ������������� �������� �������� ==, ��������� �������� ��� ������ ����� �����
bool operator != (const std::string& str, const std::string& str2) { return str.size() != str2.size() || str.find(str2) == str.npos; }    // ������������� �������� �������� !=, ��������� ��������� �� ����������� ��� ������ ����� �����

// function //
size_t strlen_t(const char* str, size_t len = 0) { return str[len] ? strlen_t(str, len + 1) : len; }    // ������� ��������� ������ ������ ������ (� ���� ������� ������ �� ������ ������������� ����)


/// math ///
// ������� ��� ������ � ������� ����������� //
// ��������� ������� ��������� �������� � �������������� ���������� //
std::vector<double_t> aritho(const double_t& a1, const double_t& d, const uint32_t& size, std::vector<double_t> v) {    // ������� ��������� ������� ������ �������������� ����������
	v.at(0) = a1; v.resize(size);
	for (auto i = v.begin() + 1; i < v.end(); i++)
		*i = *(i - 1) + d;
	return v;
}

inline double_t aritho_d(const std::vector<double_t>& v) { return v.at(1) - v.at(0); }    // ��������� ������ �������� ����� ���������� �������������� ����������

inline double_t aritho_sum(std::vector<double_t>& v) { return (v.at(0) + v.at(v.size() - 1)) / 2 * v.size(); }    // ��������� ������ �����  �������������� ����������

inline double_t aritho_search(const std::vector<double_t>& v, const uint32_t& an) { 
    return v.size() >= an ? v.at(an - 1) : v.at(0) + aritho_d(v) * (an - 1); }    // ��������� ����� ������� � ������������  �������������� ����������

size_t aritho_search(const double_t& el, const std::vector<double_t>& v) {     // ��������� ����� ����� �� ����� ���� ������� � ������������ � �� ������������  �������������� ����������
	if (std::find(v.begin(), v.end(), el) != v.end())
		return std::find(v.begin(), v.end(), el) - v.begin() + 1;

	size_t i = v.size() + 1;
	for (double_t d = aritho_d(v), g = v.at(i - 2) + d; g <= el; i++, g += d)
		if (g == el)
			return i;
	return NULL;
}

bool is_aritho(const std::vector<double_t>& v) {    // ���������, �������� �� ���������� �������������� ���������� �������������� �����������
	for (auto& el : v)
		if (el + aritho_d(v) != *(&el + 1) && el != v.at(v.size() - 1))
			return false;
	return true;
}



///  matrix  ///
/// class Matrix ///
//  ����� �������  //
//     TODO       //
template<class T>
class Matrix {
	//  class Matrix  //
	T** matrix; // ���� �������
	uint32_t m, n; // ������ � ������� 
public:
	Matrix(const uint32_t& m = 1, const uint32_t& n = 1, const T& aggr = {}) : m(m), n(n)    // ����������� �� ��� ��������� ������ Matrix. ��������� ���-�� �����, ������, � ��, ��� ��������� �������
	{
		matrix = new T * [m];

		for (uint32_t i = 0; i < m; i++) {
			matrix[i] = new T[n];
			for (uint32_t g = 0; g < n; g++)
				matrix[i][g] = aggr;
		}
	}

	~Matrix()    // ���������� ������ Matrix
	{
		for (uint32_t i = 0; i < m; i++)
			delete[]matrix[i];
		delete[]matrix;
	}

	const auto operator[](uint32_t& m) { return matrix[m]; }    // ������������� �������� ��������� � ��������� ������� �� �������

	T getM() { return m; }          // ������ ��� m
	T getN() { return n; }           // ������ ��� m
	T getSize() { return m * n; }    // ������ ��� ������� ����� �������
	void getMat() const {    // ������ ��� ��������� �� ����� ���� �������
		for (uint32_t i = 0; i < m; i++) {
			for (uint32_t g = 0; g < n; g++)
				std::cout << matrix[i][g] << tab;
			std::cout << '\n';
		}
		std::cout.flush();
	}

	void arrgs(const T& top_half, const T& bottom_half, const T& diagonal) {    // ����� ��� ���������� ������� ���������� ���������� ���: ������� ��������, ������ ��������, ���������
		for (uint32_t i = 0; i < m; ++i)
			for (uint32_t g = 0; g < n; ++g)
				(*this)[i][g] = i < g ? top_half : i > g ? bottom_half : diagonal;
	}

	const std::string search(T& el) const {    // ����� ��� ������ �������� � �������
		for (uint32_t i = 0; i < m; i++)
			for (uint32_t g = 0; g < n; g++)
				if ((*this)[i][g] == el)
					return (std::to_string(i) += ' ') += std::to_string(g);
		return "-1";
	}

	const std::string half(T& el) const {    // �����, ��� ����������� � ����� �������� ��������� �������
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

	friend bool operator==(const Matrix<T>& m1, const Matrix<T>& m2) {    // ������������� ��������-���� ��� ��������� ���� ������
		if (m1.sizes() != m2.sizes())
			return false;
		for (uint32_t i = 0; i < m1.getM(); i++)
			for (uint32_t g = 0; g < m1.getN(); g++)
				if (m1[i][g] != m2[i][g])
					return false;
		return true;
	}

	friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {    // ������������� ��������-���� ��� ������ ���� ��������� �������
		for (uint32_t i = 0; i < matrix.m; i++) {
			for (uint32_t g = 0; g < matrix.n; g++)
				std::cout << matrix[i][g] << '\t';
			std::cout << '\n';
		}
		std::cout.flush();
		return os;
	}
	//  class Matrix end  //
};

void timer_with_chrono()     // ������ (�������-_*)
{
	char sec = 0, min = 0, hour = 0, day = 0;
	while (day < 1)
	{
		timer a;
		std::cout << "Passed time: " << "sec: " << sec << string(" ") * (5 - ranks(sec))
			<< "min: " << min << string(" ") * (5 - ranks(min)) << "hour: " << hour << '\r';
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

std::string decimal_to_binary(const uint64_t& val)    // ������� ����� �� ���������� � �������� ������� ���������
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

const uint64_t binary_to_decimal(const std::string& str)    // ������� ����� �� �������� ������� ��������� � ����������
{
	if (str.size() > 64)
		return 0;
	uint64_t res = 0;
	for (size_t i = 0; i < str.size(); i++)
		res = res * 2 + str.at(i) - '0';
	return res;
}

// end 
// ���� ���, �����.

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
