#pragma once
#include <string>

std::string operator*
(const std::string& str, 
	const uint32_t& num);
// ������������� �������� �������� *, 
// ��������� �������������� ������ ��������� ��� - �� ���


std::string operator*
(const uint32_t& num, 
	const std::string& str);
// ������������� �������� �������� *, 
// ��������� �������������� ������ ��������� ���-�� ���


std::string& operator/
(std::string& str, 
	const std::string& str2);
// ������������� �������� ��������, 
// ��������� ������� ��� ���������(str2) �� ������ (str)


std::string& operator-
(std::string& str, 
	const std::string& str2);
// ������������� �������� �������� -, 
// ������� ���������(str2) �� ������ (str)


bool operator==
(const std::string& str, 
	const std::string& str2); 
// ������������� �������� �������� ==, 
// ��������� �������� ��� ������ ����� �����


bool operator!=
(const std::string& str, 
	const std::string& str2); 
// ������������� �������� �������� !=,
// ��������� ��������� �� ����������� ��� ������ ����� �����


size_t strlen_t(const char* str, 
	size_t len);
// ������� ��������� ������ ������ ������ 
// (� ���� ������� ������ �� ������ ������������� ����)