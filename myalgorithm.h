#pragma once
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



///  return end elements  ///
template <size_t N>
const char* end(const char(&str)[N]) { return str + N; }
template <size_t N>
const int64_t* end(const int64_t(&arr)[N]) { return arr + N; }
template<size_t N>
const int32_t* end(const int32_t(&arr)[N]) { return arr + N; }
template<size_t N>
const int16_t* end(const int16_t(&arr)[N]) { return arr + N; }




/// return size array ///
template <size_t N>
const int64_t size(const char(&str)[N]) { return N; }
template <size_t N>
const int64_t size(const int64_t(&arr)[N]) { return N; }
template <size_t N>
const int64_t size(const int32_t(&arr)[N]) { return N; }
template <size_t N>
const int64_t size(const int16_t(&arr)[N]) { return N; }


/// ranks ///
template <typename T>
uint16_t ranks(const T& val)
{
	uint16_t res = 0;
	T temp = val;
	do {
		temp /= 10;
		res++;
	} while (int64_t(temp) > 0);
	return res;
}

/// factorial of a number ///
uint64_t factorial(uint16_t N) { return N > 1 ? N * factorial(N - 1) : 1; }


/// degree of a number ///
uint64_t degree(uint64_t x, uint64_t y) { return y > 0 ? x * degree(x, y - 1) : 1; }


/// swap number ///
void swap(int64_t* a, int64_t* b) {
	int64_t temp = *a;
	*a = *b;
	*b = temp;
}


/// swap to fraction ///
void swap(float_t* a, float_t* b) {
	float_t temp = *a;
	*a = *b;
	*b = temp;
}
void swap(double_t* a, double_t* b) {
	double_t temp = *a;
	*a = *b;
	*b = temp;
}







/// convert str in number or nymber vice versa  ///
template<typename T>
T convert(const std::string& s)
{
	std::istringstream iss(s, std::istringstream::in);
	T res{};
	iss >> res;
	return res;
}

template<typename T>
std::string convert(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

///  operators  ///
//   string     //
std::string operator*(const std::string& str, const uint32_t& num) { return num ? str + operator*(str, num - 1) : ""; }
std::string operator*(const uint32_t& num, const std::string& str) { return operator*(str, num); }

std::string operator+(const std::string& str, const uint32_t& num) { return str + std::to_string(num); }
std::string operator+(const uint32_t& num, const std::string& str) { return str + std::to_string(num); }


std::string& operator/(std::string& str, const std::string& str2)
{
	return str.find(str2) != str.npos ? operator/(str.erase(str.find(str2), str2.length()), str2) : str;
}

std::string& operator/=(std::string& str, const std::string& str2)
{
	return str.find(str2) != str.npos ? operator/=(str.erase(str.find(str2), str2.length()), str2) : str;
}


std::string& operator-(std::string& str, const std::string& str2)
{
	return str.find(str2) != str.npos ? str.erase(str.find(str2), str2.length()) : str;
}

bool operator == (const std::string& str, const std::string& str2) { return str.size() == str2.size() && str.find(str2, 0) != str.npos; }
bool operator != (const std::string& str, const std::string& str2) { return str.size() != str2.size() || str.find(str2, 0) == str.npos; }







/// math ///
std::vector<double_t> aritho(const double_t& a1, const double_t& d = 1, const uint32_t& size = 2, std::vector<double_t> v = { 0 })
{
	v.at(0) = a1; v.resize(size);
	for (auto i = v.begin() + 1; i < v.end(); i++)
		*i = *(i - 1) + d;
	return v;
}

inline double_t aritho_d(const std::vector<double_t>& v)
{
	return v.at(1) - v.at(0);
}

inline double_t aritho_sum(std::vector<double_t>& v)
{
	return (v.at(0) + v.at(v.size() - 1)) / 2 * v.size();
}

inline double_t aritho_search(const std::vector<double_t>& v, const uint32_t& an = 0)
{
	return v.size() >= an ? v.at(an - 1) : v.at(0) + aritho_d(v) * (an - 1);
}

double_t aritho_search(const double_t& el, const std::vector<double_t>& v)
{
	if (std::find(v.begin(), v.end(), el) != v.end())
		return std::find(v.begin(), v.end(), el) - v.begin() + 1;

	size_t i = v.size() + 1;
	for (double_t d = aritho_d(v), g = v.at(i - 2) + d; g <= el; i++, g += d)
		if (g == el)
			return i;
	return NULL;
}

bool is_aritho(const std::vector<double_t>& v)
{
	for (auto& el : v)
		if (el + aritho_d(v) != *(&el + 1) && el != v.at(v.size() - 1))
			return false;
	return true;
}





///  matrix  ///
template<class T>
class Matrix {
	T** matrix;
	size_t m = 0, n = 0;
public:
	Matrix(const size_t& m = 1, const size_t& n = 1, T aggr = 0)
	{
		this->m = m; this->n = n;

		matrix = new T * [m];
		for (uint16_t i = 0; i < m; i++)
			matrix[i] = new T[n];

		for (uint16_t i = 0; i < m; i++)
			for (uint16_t g = 0; g < n; g++)
				matrix[i][g] = aggr;
	}
	~Matrix()
	{
		for (uint16_t i = 0; i < m; i++)
			delete[]matrix[i];
		delete[]matrix;
	}

	size_t sizes() const { return m * n; }


	size_t getM() const { return m; }

	size_t getN() const { return n; }

	void getMat()
	{
		for (uint16_t i = 0; i < m; i++) {
			for (uint16_t g = 0; g < n; g++)
				std::cout << matrix[i][g] << '\t';
			std::cout << '\n';
		}
	}



	std::string search(T el)
	{
		for (size_t i = 0; i < m; i++)
			for (size_t g = 0; g < n; g++)
				if ((*this)[i][g] == el)
					return (std::to_string(i) += ' ') += std::to_string(g);
		return "-1";
	}

	int16_t half(T el) {

		if (search(el) == "-1")
			return -1;
		std::string i = search(el), g = search(el);
		auto ind = i.find(' ');
		i.erase(ind, i.size()); g.erase(0, ind + 1);
		if (convert<int>(i) < convert<int>(g))
			return 1;
		else if (convert<int>(i) > convert<int>(g))
			return 0;
		return 2;
	}



	const auto operator[](size_t m) { return matrix[m]; }


	friend bool operator==(const Matrix& m1, const Matrix& m2) {
		if (m1.sizes() != m2.sizes())
			return false;
		for (uint16_t i = 0; i < m1.getM(); i++)
			for (uint16_t g = 0; g < m1.getN(); g++)
				if (m1[i][g] != m2[i][g])
					return false;
		return true;
	}

	friend bool operator!=(const Matrix& m1, const Matrix& m2) {
		return !operator==(m1, m2);
	}

	friend std::ostream& operator<<(std::ostream& os, Matrix& matrix)
	{
		for (uint16_t i = 0; i < matrix.m; i++) {
			for (uint16_t g = 0; g < matrix.n; g++)
				std::cout << matrix[i][g] << '\t';
			std::cout << '\n';
		}
		return os;
	}

};


void timer_with_chrono()
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

std::string decimal_to_binary(const uint64_t& val)
{
	auto temp = val;
	std::string res;

	do {
		res.insert(0, std::to_string(temp % 2));
		temp /= 2;
	} while (temp > 0);

	return res;
}

const uint64_t binary_to_decimal(const std::string& str)
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
