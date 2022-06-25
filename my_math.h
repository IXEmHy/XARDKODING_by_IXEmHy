#pragma once
#include <cstdint>
#include <vector>

/// factorial of a number ///
uint64_t factorial(uint16_t N);                                   // ������� ��� ���������� ���������� �����
/// degree of a number ///
uint64_t degree(uint64_t x, uint64_t y);                          // ������� ��� ���������� ������� �����


// ��������� ������� ��������� �������� � �������������� ���������� //

std::vector<double_t> aritho(const double_t& a1,                  // ������� ��������� ������� ������ �������������� ����������
	const double_t& d,
	const uint32_t& size,
	std::vector<double_t> v);

inline double_t aritho_d(const std::vector<double_t>& v);         // ��������� ������ �������� ����� ���������� �������������� ����������

inline double_t aritho_sum(std::vector<double_t>& v);             // ��������� ������ �����  �������������� ����������

inline double_t aritho_search                                     // ��������� ����� ������� � ������������  �������������� ����������
(const std::vector<double_t>& v,
	const uint32_t& an);

size_t aritho_search                                              // ��������� ����� ����� �� ����� ���� ������� � ������������
(const double_t& el,                          
	const std::vector<double_t>& v);                              // � �� ������������  �������������� ����������

bool is_aritho(const std::vector<double_t>& v);                   // ���������, �������� �� ���������� �������������� ���������� �������������� �����������

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