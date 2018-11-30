#pragma once
#include <iostream>
#include <sstream>
#include <any>
#include <map>
#include <vector>
#include <fstream>
namespace JSON {
	// ConsoleApplication12.cpp: определяет точку входа для консольного приложения.
	//




	class Json {
		std::map<std::string, std::any> Objects;
		std::vector<std::any> arrays;
		bool isarr = false;
		bool undef=false ;
		bool getline_braket(std::istringstream & stream, std::string & dist, char delim, char first_char);
			
		
		
	public:

		// Конструктор из строки, содержащей Json-данные.
		Json(const std::string& s) ;

		// Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
		bool is_array() const ;
		// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
		bool is_object() const ;
		void error_parse();
		// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
		// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
		// Если экземпляр является JSON-массивом, генерируется исключение.
		std::any& operator[](const std::string& key) ;

		// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
		// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
		// Если экземпляр является JSON-объектом, генерируется исключение.
		std::any& operator[](int index);

		// Метод возвращает объект класса Json из строки, содержащей Json-данные.
		static Json parse(const std::string& s);

		// Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
		static Json parseFile(const std::string& path_to_file) ;
	};

	

}