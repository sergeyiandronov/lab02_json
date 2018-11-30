#pragma once
#include <iostream>
#include <sstream>
#include <any>
#include <map>
#include <vector>
#include <fstream>
namespace JSON {
	// ConsoleApplication12.cpp: ���������� ����� ����� ��� ����������� ����������.
	//




	class Json {
		std::map<std::string, std::any> Objects;
		std::vector<std::any> arrays;
		bool isarr = false;
		bool undef=false ;
		bool getline_braket(std::istringstream & stream, std::string & dist, char delim, char first_char);
			
		
		
	public:

		// ����������� �� ������, ���������� Json-������.
		Json(const std::string& s) ;

		// ����� ���������� true, ���� ������ ��������� �������� � ���� JSON-������. ����� false.
		bool is_array() const ;
		// ����� ���������� true, ���� ������ ��������� �������� � ���� JSON-������. ����� false.
		bool is_object() const ;
		void error_parse();
		// ����� ���������� �������� �� ����� key, ���� ��������� �������� JSON-��������.
		// �������� ����� ����� ���� �� ��������� �����: Json, std::string, double, bool ��� ���� ������.
		// ���� ��������� �������� JSON-��������, ������������ ����������.
		std::any& operator[](const std::string& key) ;

		// ����� ���������� �������� �� ������� index, ���� ��������� �������� JSON-��������.
		// �������� ����� ����� ���� �� ��������� �����: Json, std::string, double, bool ��� ���� ������.
		// ���� ��������� �������� JSON-��������, ������������ ����������.
		std::any& operator[](int index);

		// ����� ���������� ������ ������ Json �� ������, ���������� Json-������.
		static Json parse(const std::string& s);

		// ����� ���������� ������� ������ Json �� �����, ����������� Json-������ � ��������� �������.
		static Json parseFile(const std::string& path_to_file) ;
	};

	

}