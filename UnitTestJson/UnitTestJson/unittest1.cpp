#include "stdafx.h"
#include "CppUnitTest.h"
#include "json.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestJson
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::string json = "{\"lastname\" : \"Ivanov\",\"firstname\" : \"Ivan\",\"age\" : 25,\"islegal\" : false,\"marks\" : [		4,5,5,5,2,3	],\"address\" : {\"city\" : \"Moscow\",\"street\" : \"example\"	}}" ;

			JSON::Json object = JSON::Json::parse(json);
			Assert::IsTrue(std::any_cast<std::string>(object["lastname"])== "Ivanov");
			Assert::IsTrue(std::any_cast<bool>(object["islegal"])==false);
			Assert::IsTrue(std::any_cast<int>(object["age"])== 25);
			
			auto marks = std::any_cast<JSON::Json>(object["marks"]);
			Assert::IsTrue(std::any_cast<int>(marks[0])==4);
			Assert::IsTrue(std::any_cast<int>(marks[1])== 5);

			auto address = std::any_cast<JSON::Json>(object["address"]);
			Assert::IsTrue(std::any_cast<std::string>(address["city"])=="Moscow");
			Assert::IsTrue(std::any_cast<std::string>(address["street"]) =="example");
			JSON::Json js("{\"json\":[ \"Ivanov\",{\"path\": 5}, 25, false, {\"dog\":{\"city\":null},\"city\" : \"Moscow\",\"street\" : null  }  ]}");

			auto el1 = std::any_cast<int>(std::any_cast<JSON::Json>(js["json"])[2]);
			auto el = std::any_cast<std::string>(std::any_cast<JSON::Json>(std::any_cast<JSON::Json>(js["json"])[4])["city"]);
			auto el3= std::any_cast<int>(std::any_cast<JSON::Json>(std::any_cast<JSON::Json>(js["json"])[1])["path"]);
			auto el2 = std::any_cast<std::string>(std::any_cast<JSON::Json>(std::any_cast<JSON::Json>(std::any_cast<JSON::Json>(js["json"])[4])["dog"])["city"]);
			Assert::IsTrue(el=="Moscow");
			Assert::IsTrue(el3 == 5);
			Assert::IsTrue(el2 == "");
			JSON::Json jsnull("{}");
			JSON::Json jsarrnull("[]");
			
			// TODO: Разместите здесь код своего теста
		}

	};
}