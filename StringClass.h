#pragma once
#include<iostream>
using namespace std;
//My string class 21.09.2021
class StringClass
{
	char* str = nullptr;
public:
	//Проверка на пустую строку
	bool CheckForEmptiness() {
		if (str == nullptr) return true;
		else return false;
	}

	//Поиск подстроки
	int operator()(const char x[]) {
		bool flg = true;
		int j = 0;
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] == x[0]) {
				for (j = 0; j < strlen(x); j++, i++) {
					if (str[i] != x[j]) {
						flg = false;
						break;
					}
				}
				if (flg != false) return i - strlen(x);
				flg = true;
				i -= --j;
			}
		}
		return -1;
	}

	//Поиск подстроки и замена
	char* replacementhStr(const char what[], const char wher[]) {
		int index = operator()(wher);
		if(index!=-1){
			char* tmp = new char[strlen(what) + strlen(str) + 1];
			for (int i = 0, j = 0; i < (strlen(what) + strlen(str) + 1); i++) {
				if (i < index) {
					tmp[i] = str[i];
				}
				else if (i >= index && i < index + strlen(what)) {
					tmp[i] = what[j];
					j++;
				}
				else {
					tmp[i] = str[(i + strlen(wher)) - j];
				}
			}
			cout << tmp << endl;
			return tmp;
		}
		return nullptr;
	}

	//Переворот строки
	void coupStr() {
		char* tmp = new char[strlen(str)];
		for (int i = 0; i < strlen(str); i++) {
			tmp[i] = str[i];
		}
		for (int i = 0; i < strlen(str); i++) {
			str[i] = tmp[(strlen(str) - 1) - i];
		}
		tmp = nullptr;
	}

	//Получение строки
	char* getStr() { return str; }
	
	//Длина строки
	int strleng() { for (int i = 0;; i++) { if (str[i] == '\0') return i; } }

	//Оператор прибавления_присвоение строки
	void operator+=(const char two[]) {
		char* tmp = new char[strlen(str) + strlen(two)];
		for (int i = 0; i < (strlen(str) + strlen(two)); i++) {
			if (i < strlen(str)) { tmp[i] = str[i]; }
			else { tmp[i] = two[i - strlen(str)]; }
		}
		tmp[strlen(str) + strlen(two)] = '\0';
		str = nullptr; str = new char[strlen(tmp) + 1]; strcpy_s(str, strlen(tmp) + 1, tmp);
	}
	//Оператор прибавления_присвоение класса
	void operator+=(const StringClass& x) {
		char* tmp = new char[strlen(str) + strlen(x.str)];
		for (int i = 0; i < (strlen(str) + strlen(x.str)); i++) {
			if (i < strlen(str)) { tmp[i] = str[i]; }
			else { tmp[i] = x.str[i - strlen(str)]; }
		}
		tmp[strlen(str) + strlen(x.str)] = '\0';
		str = nullptr; str = new char[strlen(tmp) + 1]; strcpy_s(str, strlen(tmp) + 1, tmp);
	}

	//Оператор прибавления строки
	char* operator+(const char two[]) {
		char* tmp = new char[strlen(str) + strlen(two)];
		for (int i = 0; i < (strlen(str) + strlen(two)); i++) {
			if (i < strlen(str)) { tmp[i] = str[i]; }
			else { tmp[i] = two[i - strlen(str)]; }
		}
		tmp[strlen(str) + strlen(two)] = '\0';
		return tmp;
	}

	//Оператор прибавления класса
	StringClass operator+(const StringClass& x) {
		char* tmp = new char[strlen(str) + strlen(x.str)];
		for (int i = 0; i < (strlen(str) + strlen(x.str)); i++) {
			if (i < strlen(str)) { tmp[i] = str[i]; }
			else { tmp[i] = x.str[i - strlen(str)]; }
		}
		tmp[strlen(str) + strlen(x.str)] = '\0';
		StringClass S_tmp(tmp);
		return S_tmp;
	}

	//Сравнение строк со строкой
	//Больше меньше
	bool operator>(const char str[]) { if (strlen(this->str) > strlen(str)) { return true; }return false; }
	bool operator<(const char str[]) { return!operator>(str); }
	//Больше_равно меньше_равно
	bool operator>=(const char str[]) { if (strlen(this->str) >= strlen(str)) { return true; }return false; }
	bool operator<=(const char str[]) { return!operator>(str); }
	//Равно не равно
	bool operator == (const char str[]) {
		if (strlen(this->str) != strlen(str)) return false;
		for (size_t i = 0; i < strlen(this->str); i++) if (this->str[i] != str[i]) { return false; }
		return true;
	}
	bool operator!=(const char str[]) { return!operator==(str); }

	//Сравнение строк с классом
	//Больше меньше
	bool operator>(const StringClass& x) { return operator>(x.str); }
	bool operator<(const StringClass& x) { return operator<(x.str); }
	//Больше_равно меньше_равно
	bool operator>=(const StringClass& x) { return operator>=(x.str); }
	bool operator<=(const StringClass& x) { return operator<=(x.str); }
	//Равно не равно
	bool operator==(const StringClass& x) { return operator==(x.str); }
	bool operator!=(const StringClass& x) { return operator!=(x.str); }

	//вывод
	friend ostream& operator<<(ostream& os, const StringClass& str) { os << str.str; return os; }

	char operator[] (int index) { return this->str[index]; }

	//Ввод
	friend istream& operator>> (istream& is, StringClass& str)
	{
		str.str = nullptr; str.str = new char[255];
		is.getline(str.str, 255);
		return is;
	}

	//Перенос строки !(move(NAMECLASS))
	StringClass& operator=(StringClass&& x) {
		if (this->str != nullptr)this->str = nullptr;
		this->str = new char[strlen(x.str) + 1];
		strcpy_s(this->str, strlen(x.str) + 1, x.str);
		x.str = nullptr;
		return *this;
	}

	//Присваивание строки
	StringClass& operator=(StringClass& x) {
		if (this->str != nullptr)this->str = nullptr;
		this->str = new char[strlen(x.str) + 1];
		strcpy_s(this->str, strlen(x.str) + 1, x.str);
		return *this;
	}

	//Без аргументов
	StringClass() { str = nullptr; }

	//С размерностью строки
	StringClass(int size) { str = nullptr; str = new char[size]; }

	//С строкой(Размерность находиться автоматически)
	StringClass(const char str[]) { this->str = nullptr; this->str = new char[strlen(str) + 1]; strcpy_s(this->str, strlen(str) + 1, str); }

	//Конструкторо копирования
	StringClass(const StringClass& x) { this->str = new char[strlen(x.str) + 1]; strcpy_s(this->str, strlen(x.str) + 1, x.str); }

	//Конструкторо переноса !(move(NAMECLASS))
	StringClass(StringClass&& x) { this->str = new char[strlen(x.str) + 1]; strcpy_s(this->str, strlen(x.str) + 1, x.str); x.str = nullptr; }

	//Деструктор
	~StringClass() { delete[] this->str; }
};