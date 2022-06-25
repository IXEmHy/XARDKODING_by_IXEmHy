#pragma once
#include <string>

std::string operator*
(const std::string& str, 
	const uint32_t& num);
// Перегруженный бинарный оператор *, 
// позволяет продублировать строку указанное кол - во раз


std::string operator*
(const uint32_t& num, 
	const std::string& str);
// Перегруженный бинарный оператор *, 
// позволяет продублировать строку указанное кол-во раз


std::string& operator/
(std::string& str, 
	const std::string& str2);
// Перегруженный бинарный оператор, 
// позволяет удалить все подстроки(str2) из строки (str)


std::string& operator-
(std::string& str, 
	const std::string& str2);
// Перегруженный бинарный оператор -, 
// удаляет подстроку(str2) из строки (str)


bool operator==
(const std::string& str, 
	const std::string& str2); 
// Перегруженный бинарный оператор ==, 
// позволяет сравнить две строки между собой


bool operator!=
(const std::string& str, 
	const std::string& str2); 
// Перегруженный бинарный оператор !=,
// позволяет проверить на неравенство две строки между собой


size_t strlen_t(const char* str, 
	size_t len);
// Функция позволяет узнать размер строки 
// (в учет размера строки не входит терминирующий нуль)