#include "json.hpp"
#include <iostream>
using json = nlohmann::json;
int main() {
	json js = R"(
 [
    ["Si-9.15", "RTS-9.15", "GAZP-9.15"],
    [100024, 100027, 100050],
    ["Futures contract for USD/RUB", "Futures contract for index RTS", "Futures contract for Gazprom shares"]
]
)"_json;
	json jsresult;
	for (int i = 0; i < 3; i++) {
		json js_el;
		js_el["ticker"] = js[0][i];
		js_el["id"] = js[1][i];
		js_el["describtion"] = js[2][i];
		jsresult[i] = js_el;
	}

	std::cout << jsresult;
	system("pause");
}