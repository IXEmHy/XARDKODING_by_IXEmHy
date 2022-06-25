#pragma once
// P.S. Комментарии пока что будут на русском -_- //
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
T convert(const std::string& s)                                   // Конвертация строки в число (Код не мой)
{
	std::istringstream iss(s, std::istringstream::in);
	T res{};
	iss >> res;
	return res;
}

template<typename T>
std::string convert(T val)                                        // Конвертация числа в строку (Код не мой)
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

std::string decimal_to_binary(const uint64_t& val)                // Перевод числа из десятичной в двоичную систему счисления
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

const uint64_t binary_to_decimal(const std::string& str)          // Перевод числа из двоичной системы счисления в десятичную
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
//  класс Матрица  //
//     TODO       //
template<class T>
class Matrix {                                                    //  class Matrix  //                                                              
	T** matrix;                                                   // Сама матрица
	uint32_t m, n;                                                // Строки и колонны 
public:
	Matrix(const uint32_t& m = 1,                                 // Конструктор не пол умолчанию класса Matrix. 
		const uint32_t& n = 1,                                    // Принимает кол-во строк, колонн, и то, чем заполнить матрицу
		const T& aggr = {}) : m(m), n(n)                          
	{
		matrix = new T*[m];
		for (uint32_t i = 0; i < m; i++) {
			matrix[i] = new T[n];
			for (uint32_t g = 0; g < n; g++)
				matrix[i][g] = aggr;
		}
	}

	~Matrix()                                                     // Деструктор класса Matrix
	{
		for (uint32_t i = 0; i < m; i++)
			delete[] matrix[i];
		delete[]matrix;
	}

	auto operator[](const uint32_t& m) const { return matrix[m]; }// перегруженный оператор обращение к эелементу массива по индексу

	T getM() { return m; }                                        // Геттер для m
	T getN() { return n; }                                        // Геттер для m
	T getSize() { return m * n; }                                 // Геттер для размера всего массива
	void getMat() const {										  // Геттер для выведения на экран всей матрицы
		for (uint32_t i = 0; i < m; i++) {
			for (uint32_t g = 0; g < n; g++)
				std::cout << matrix[i][g] << tab;
			std::cout << '\n';
		}
		std::cout.flush();
	}

	void arrgs(const T& top_half,                                 // Метод для заполнения матрицы указанными значениями для:
		const T& bottom_half,                                     // верхней половины, нижней половины, диагонали
		const T& diagonal) {    
		for (uint32_t i = 0; i < m; ++i)
			for (uint32_t g = 0; g < n; ++g)
				(*this)[i][g] = i < g ? top_half 
				: i > g ? bottom_half : diagonal;
	}

	const std::string search(T& el) const {                       // Метод для поиска элемента в матрице
		for (uint32_t i = 0; i < m; i++)
			for (uint32_t g = 0; g < n; g++)
				if ((*this)[i][g] == el)           
					return (std::to_string(i) += ' ')
					+= std::to_string(g);
		return "-1";
	}

	const std::string half(T& el) const {                         // Метод, для определения в какой половине находится элемент
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

	friend bool operator==(const Matrix<T>& m1,                   // Перегруженный оператор-друг для сравнения двух матриц
		const Matrix<T>& m2) {    
		if (m1.sizes() != m2.sizes())
			return false;
		for (uint32_t i = 0; i < m1.getM(); i++)
			for (uint32_t g = 0; g < m1.getN(); g++)
				if (m1[i][g] != m2[i][g])
					return false;
		return true;
	}

	friend std::ostream& operator<<(std::ostream& os,             // Перегруженный оператор-друг для вывода всех элементов матрицы
		const Matrix<T>& matrix) {   
		for (uint32_t i = 0; i < matrix.m; i++) {
			for (uint32_t g = 0; g < matrix.n; g++)
				std::cout << matrix[i][g] << tab;
			std::cout << '\n';
		}
		std::cout.flush();
		return os;
	}
	friend std::istream& operator>>(std::istream& os,             // Перегруженный оператор-друг для вывода всех элементов матрицы
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
{ return num > 0 ? degree_two(num / 2, res + 1) : res; }          // Функция для вычесления, в какой степени двойка, будет больше чем переданный аргумент


template<class T>
class VecEno                                                      // класс VecEno
{
	size_t       size, _capacity;                                 // размер и капасити вектора
	const size_t MAX_SIZE = 65536 / sizeof(T);                    // максимальный размер для вектора (максимально можно создать объект размер которого будет 65536 байт)
	T*           array;                                           // сам массив
public:
	class iterator                                                // класс iterator
	{ 
		T* el;                                                    // элемент на который указывает итератор
	public: 
		iterator(T* elm) { el = elm; }                            // конструктор инициализацией уже указателем из вне // не безопасно
		iterator(iterator* elm) { el = elm->el; }                 // конструктор копирования
		T& operator*() const { return *el; }                      // оператор разыменования
		T* operator-(const size_t& it) { return el - it; }        // оператор разности между указателем и числом (арифм. указателей)
		T* operator+(const size_t& it) { return el + it; }        // оператор сложения между указателем и числом (арифм. указателей)
		T* operator++() { return ++el; }                          // префиксный инкримент
		T* operator++(int) { return el++; }                       // постфиксный инкримент
		T* operator--() { return --el; }                          // префиксный декримент
		T* operator--(int) { return el--; }                       // постфиксный декримент
		 
		bool operator>(const iterator& it) { return el > it.el; } // оператор сравнения указателей (больше)
		bool operator<(const iterator& it) { return el < it.el; } // оператор сравнения указателей (меньше)
		bool operator!=(const iterator& it) { return el != it.el; }
	};

	VecEno() : size(1), _capacity(2) { array = new T[_capacity]; }  // конструктор по умолчанию

	VecEno(const std::initializer_list<T>& _init)                 // конструктор с заданием uniform-инициализации
	: size(_init.size()), _capacity(degree(2, degree_two(size))) {
		array = size >= MAX_SIZE ? new T[MAX_SIZE] : new T[_capacity];
		uint32_t i = 0;
		for (auto it = _init.begin(), end = _init.end(); it != end; it++, i++)
			array[i] = *it;
	}
	VecEno(const VecEno<T>& vec)                                  // конструктор копирования
	: size(vec.size), _capacity(degree(2, degree_two(size))) { 
		array = new T[_capacity];
		for (size_t i = 0; i < size; i++)
			array[i] = vec[i];
	}
	~VecEno() { delete[] array; }                                 // деструктор

	const size_t getSize() const { return size; }                 // геттер для size
	const size_t getCapacity() const { return _capacity; }        // геттер для _capacity
	const size_t getMAX_SIZE() const { return MAX_SIZE; }         // геттер для MAX_SIZE
	iterator begin() const { return iterator(array); }            // геттер для begin
	iterator end() const { return iterator(array + size); }       // геттер для end

	void reverse() {
		for (size_t i = 0; i < size / 2; i++)
			swap((*this)[i], (*this)[size - 1 - i]);
	}

	void setCapacity(const size_t& _capacity) {                   // сеттер для _capacity
		T* temp_ptr = array;
		size_t tempCap = this->_capacity;
		this->_capacity = _capacity;
		array = new T[_capacity];
		for (size_t i = 0; i < tempCap; i++)
			array[i] = temp_ptr[i];
		delete[] temp_ptr;
	}

	void push_back(const T& el) {                                 // добавить элемент в конец
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


	T& at(const size_t& ind) { return size > ind ? array[ind]     // обратится к элементу по индексу (безопасно)
		: throw "Выход за пределы вектора . . .\n"; } 
	T& operator[](const size_t& ind) { return array[ind]; }       // обратится к элементу по индексу

	friend std::ostream& operator<<                               // вывод вектора (для удобства)
		(std::ostream& os, const VecEno<T>& vec) {
		for (auto begin = vec.begin(), end = vec.end(); begin < end; begin++)
			std::cout << *begin << '\t';
		std::cout << std::endl;
		return os;
	}
};



double rad_deg(const double& rad) { return rad * RADIAN; }        // перевод радиан в грудусы
double deg_rad(const double& deg) { return deg * DEGREE; }        // перевод градусы в радианы

// reverse //
template<class T>                                                 // реверс массива встроенного типа
void reverse(T& arr) {
	for (size_t i = 0, size = sizeof(arr) / sizeof(arr[0]); i < size / 2; i++)
		swap(arr[i], arr[size - 1 - i]);
}

// SORT //
// choice sort //
template<typename T>
void sort(T& arr, bool smallset_to_largest = true) {              // сортировка массива встроенного типа
	for (size_t i = 0, g = 0, size = sizeof(arr) / sizeof(arr[0]); i != size - 1; i++)
		for (g = i + 1; g < size; g++)
			if (arr[i] != arr[g] && arr[i] > arr[g] == smallset_to_largest)
				swap(arr[i], arr[g]);
}

// min element //
template<typename T>
auto min_max(T& arr, bool _min = true) {                          // сортировка массива встроенного типа
	auto min_max = arr[0];
	for (size_t i = 1, size = sizeof(arr) / sizeof(arr[0]); i != size; i++)
		if (arr[i] != min_max && min_max > arr[i] == _min)
			min_max = arr[i];
	return min_max;
}

const char* layout(const std::string& st) {
	return st.find('q') != st.npos && st.find('Q') != st.npos ? "qwerty" : "йцукен";
}

std::string translit(const std::string& str, const int& from, const int& to) {
	std::string layout[2]
	{ "йцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ",
	  "qwertyuiop[]asdfghjkl;'zxcvbnm,.QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>" },
		res = str;

	for (size_t i = 0, find = -1; i < str.size(); i++) {
		find = layout[from].find(str[i]);
		res[i] = find != str.npos ? layout[to][find] : res[i];
	}
	return res;
}
#endif
