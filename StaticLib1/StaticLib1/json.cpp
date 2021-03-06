// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// StaticLib1.pch будет использоваться в качестве предкомпилированного заголовка
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

// TODO: Установите ссылки на любые требующиеся дополнительные заголовки в файле STDAFX.H
// , а не в данном файле
// ConsoleApplication12.cpp: определяет точку входа для консольного приложения.
//


namespace JSON{
	void Json::error_parse() {
		Objects.clear();
		arrays.clear();
		undef = true; 
		
		return;
	}
	bool Json::getline_braket(std::istringstream & stream, std::string & dist, char delim, char first_char) {
		char op;
		int braket1 = 0;
		if (first_char == '{') {
			braket1 = 1;
		}
		int braket2 = 0;
		if (first_char == '[') {
			braket2 = 1;
		}
		bool in_quote = false;
		bool delim_braket = (delim == '}' || delim == ']');

		while (stream >> op) {
			std::string ops(1, op);


			if (op == '"') {
				in_quote = !in_quote;
			}
			if (op == '{' && !in_quote) {
				braket1++;
			}
			if (op == '}' && !in_quote) {
				braket1--;
			}
			if (op == '[' && !in_quote) {
				braket2++;
			}
			if (op == ']' && !in_quote) {
				braket2--;
			}
			if (braket1<0) {
				return false;
			}
			if (braket2<0) {
				return false;
			}
			if (!(braket1 == 0 && braket2 == 0) && op == delim && !delim_braket) {
				return false;

			}
			if (braket1 == 0 && braket2 == 0 && op == delim) {
				return true;

			}
			dist += ops;
		}
		if (braket1 == 0 && braket2 == 0) {
			return true;
		}
		return false;
	}


	// Конструктор из строки, содержащей Json-данные.
	Json::Json(const std::string& s) {
		std::istringstream stream(s);
		
		
		std::string key;
		std::string value;
		std::string valuebool;
		int valuei=0;
		bool valueb;
		char fc;
		char op;
		
		if (stream >> op) {
			if (op == '{') {
				this->isarr = false;
				if (!(stream >> op)) { error_parse(); return; }
				if (op == '}') { return; }
				stream.seekg(-1, std::ios_base::cur);
			}
			else if (op == '[') {
				this->isarr = true;
				if (!(stream >> op)) { error_parse(); return; }
				if (op == ']') { return; }
				stream.seekg(-1, std::ios_base::cur);
			}
			else {
				error_parse(); return;
			}
			
		}
		else { error_parse(); return; }
		
		if (!isarr) {
			std::string json_body = "";

			if (!getline_braket(stream, json_body, '}', '{')) {
				error_parse(); return;
			}

			std::istringstream stream_body(json_body);
			while (stream_body >> op) {
				
				value = "";
				if (op != '"') { error_parse(); return; }
				std::getline(stream_body, key, '"');
				char delim;
				if (!(stream_body >> delim)) { error_parse(); return; }
				if (delim != ':') { error_parse(); return; }

				char JsonOpen;

				if (!(stream_body >> JsonOpen)) { error_parse(); return; }

				if (JsonOpen == '{') {
					if (!getline_braket(stream_body, value, '}', '{')) { error_parse(); return; }
					value = '{' + value + '}';
					char endelement;
					if (stream_body >> endelement) {
						if (endelement != ',') {
							error_parse(); return;

						}
						if (!(stream_body >> endelement)) {
							error_parse(); return;
						}
						stream_body.seekg(-1, std::ios_base::cur);
					}
				}
				if (JsonOpen == '[') {
					if (!getline_braket(stream_body, value, ']', '[')) { error_parse(); return; }
					value = '[' + value + ']';
					char endelement;
					if (stream_body >> endelement) {
						if (endelement != ',') {
							error_parse(); return;

						}
						if (!(stream_body >> endelement)) {
							error_parse(); return;
						}
						stream_body.seekg(-1, std::ios_base::cur);
					}
				}
				if (!(JsonOpen == '{' || JsonOpen == '[')) {
					stream_body.seekg(-1, std::ios_base::cur);
					getline_braket(stream_body, value, ',', 0);
				}
				std::istringstream streamvalue(value);
				if (streamvalue >> fc) {
					if (fc == '"') {
						std::getline(streamvalue, value, '"');
						Objects.insert(std::make_pair(key, std::make_any<decltype(value)>(value)));

					}
					if (fc == '1' || fc == '2' || fc == '3' || fc == '4' || fc == '5' || fc == '6' || fc == '7' || fc == '8' || fc == '9' || fc == '0') {
						streamvalue.seekg(-1, std::ios_base::cur);
						if (!(streamvalue >> valuei)) { error_parse(); return; }
						Objects.insert(std::make_pair(key, std::make_any<decltype(valuei)>(valuei)));
					}
					if (fc == 't' || fc == 'f') {
						streamvalue.seekg(-1, std::ios_base::cur);
						streamvalue >> valuebool;
						if (valuebool == "true") {
							valueb = true;
						}
						else if (valuebool == "false") {
							valueb = false;
						}
						else { error_parse(); return; }
						Objects.insert(std::make_pair(key, std::make_any<decltype(valueb)>(valueb)));

					}
					if (fc == 'n') {
						streamvalue.seekg(-1, std::ios_base::cur);
						streamvalue >> value;
						if (value == "null") {
							value = "";
						}
						else { error_parse(); return; }
						Objects.insert(std::make_pair(key, std::make_any<decltype(value)>(value)));

					}
					if (fc == '{') {

						std::string childJson;
						std::getline(streamvalue, childJson);
						childJson = "{" + childJson;
						Json chjs(childJson);
						if (chjs.undef) { error_parse(); return; }
						Objects.insert(std::make_pair(key, std::make_any<decltype(chjs)>(chjs)));
					}
					if (fc == '[') {

						std::string childJson;
						std::getline(streamvalue, childJson);
						childJson = "[" + childJson;
						Json chjs(childJson);
						if (chjs.undef) { error_parse(); return; }
						Objects.insert(std::make_pair(key, std::make_any<decltype(chjs)>(chjs)));
					}
				}
				else {
				    error_parse(); 
					return;
				}
			}

		}
		if (isarr) {
			std::string json_body = "";

			if (!getline_braket(stream, json_body, ']', '[')) { error_parse(); return; }

			std::istringstream stream_body(json_body);
			while (stream_body >> op) {
				value = "";

				if (op == '{') {
					if (!getline_braket(stream_body, value, '}', '{')) { error_parse(); return; }
					value = '{' + value + '}';
					char endelement;
					if (stream_body >> endelement) {
						if (endelement != ',') {
							error_parse(); return;

						}
						if (!(stream_body >> endelement)) {
							error_parse(); return;
						}
						stream_body.seekg(-1, std::ios_base::cur);
					}
				}
				if (op == '[') {
					if (!getline_braket(stream_body, value, ']', '[')) { error_parse(); return; }
					value = '[' + value + ']';
					char endelement;
					if (stream_body >> endelement) {
						if (endelement != ',') {
							error_parse(); return;

						}
						if (!(stream_body >> endelement)) {
							error_parse(); return;
						}
						stream_body.seekg(-1, std::ios_base::cur);
					}
				}
				if (!(op == '{' || op == '[')) {
					stream_body.seekg(-1, std::ios_base::cur);
					getline_braket(stream_body, value, ',', 0);
				}
				std::istringstream streamvalue(value);
				if (streamvalue >> fc) {
					if (fc == '"') {
						std::getline(streamvalue, value, '"');
						arrays.push_back(std::make_any<decltype(value)>(value));

					}
					if (fc == '1' || fc == '2' || fc == '3' || fc == '4' || fc == '5' || fc == '6' || fc == '7' || fc == '8' || fc == '9' || fc == '0') {
						streamvalue.seekg(-1, std::ios_base::cur);
						if (!(streamvalue >> valuei)) { error_parse(); return; }
						arrays.push_back(std::make_any<decltype(valuei)>(valuei));
					}
					if (fc == 't' || fc == 'f') {
						streamvalue.seekg(-1, std::ios_base::cur);
						streamvalue >> valuebool;
						if (valuebool == "true") {
							valueb = true;
						}
						else if (valuebool == "false") {
							valueb = false;
						}
						else { error_parse(); return; }
						arrays.push_back(std::make_any<decltype(valueb)>(valueb));

					}
					if (fc == 'n') {
						streamvalue.seekg(-1, std::ios_base::cur);
						streamvalue >> value;
						if (value == "null") {
							value = "";
						}
						else { error_parse(); return; }
						Objects.insert(std::make_pair(key, std::make_any<decltype(value)>(value)));

					}
					if (fc == '{') {

						std::string childJson;
						std::getline(streamvalue, childJson);
						childJson = "{" + childJson;
						Json chjs(childJson);
						if (chjs.undef) { error_parse(); return; }
						arrays.push_back(std::make_any<decltype(chjs)>(chjs));
					}
					if (fc == '[') {

						std::string childJson;
						std::getline(streamvalue, childJson);
						childJson = "[" + childJson;
						Json chjs(childJson);
						if (chjs.undef) { error_parse(); return; }
						arrays.push_back(std::make_any<decltype(chjs)>(chjs));
					}
				}
				else {
					error_parse();
					return;
				}
			}

		}

	};

	// Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
	bool Json::is_array() const { if (undef) { throw "Error while parsing"; } return isarr; };
	// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
	bool Json::is_object() const { if (undef) { throw "Error while parsing"; } return !isarr; };

	// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
	// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
	// Если экземпляр является JSON-массивом, генерируется исключение.
	std::any& Json::operator[](const std::string& key) { if (undef) { throw "Error while parsing"; }if (isarr) { throw "Not json object"; }return Objects[key]; };

	// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
	// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
	// Если экземпляр является JSON-объектом, генерируется исключение.
	std::any& Json::operator[](int index) { if (undef) { throw "Error while parsing"; }if (!isarr) { throw "Not json array"; } return  arrays[index]; }

	// Метод возвращает объект класса Json из строки, содержащей Json-данные.
	 Json Json::parse(const std::string& s) {
		Json js(s);
		return js;
	};

	// Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
	Json Json::parseFile(const std::string& path_to_file) {
		std::ifstream fs(path_to_file);
		std::string to_parse;
		std::string tmp_string;
		while (!fs.eof()) {
			std::getline(fs, tmp_string);
			to_parse += tmp_string;
		}
		Json js(to_parse);
		return js;
	};

}