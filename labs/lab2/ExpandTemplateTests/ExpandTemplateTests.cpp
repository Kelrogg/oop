#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../ExpandTemplate/ExpandTemplate.h"

TEST_CASE("Tasks tests")
{
	std::string iss{ "Hello, %USER_NAME%. Today is {WEEK_DAY}." };
	map<string, string> params{
		{"%USER_NAME%", "Ivan Petrov" },
		{ "{WEEK_DAY}", "Friday"}
	};
	REQUIRE(ExpandTemplate(iss, params) == "Hello, Ivan Petrov. Today is Friday.");


	iss =  "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
	params = {
		{ "%USER_NAME%", "Super %USER_NAME% {WEEK_DAY}" },
		{ "{WEEK_DAY}", "Friday. {WEEK_DAY}" }
	};
	REQUIRE(ExpandTemplate(iss, params) == 
		"Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}."
	);


	iss = "-AABBCCCCCABC+";
	params = {
		{ "A", "[a]" },
		{ "AA", "[aa]" },
		{ "B", "[b]" },
		{ "BB", "[bb]" },
		{ "C", "[c]" },
		{ "CC", "[cc]" }
	};
	REQUIRE(ExpandTemplate(iss, params) == "-[aa][bb][cc][cc][c][a][b][c]+");
}

SCENARIO("Boundary situations of using the ExpandTemplate function")
{
	using ParamsMap = std::map<std::string, std::string>;

	ParamsMap params;
	params["A"] = "[a]";
	params["AA"] = "[aa]";
	params["B"] = "[b]";
	params["BB"] = "[bb]";
	params["C"] = "[c]";
	params["CC"] = "[cc]";
	const ParamsMap copiedParams(params);

	ParamsMap emptyParamsMap{};
	const ParamsMap copiedEmptyParamsMap{ emptyParamsMap };

	WHEN("An empty string is processed, the result will be an empty string")
	{
		std::string emptyString = "";
		THEN("Result is empty string and given string and map are still the same")
		{
			std::string result = ExpandTemplate(emptyString, params);

			REQUIRE(std::size(result) == 0);

			REQUIRE(std::size(emptyString) == 0);
			REQUIRE(params == copiedParams);
		}
	}

	WHEN("Passing string with no templates in, the result will be the same string")
	{
		std::string stringWithNoTemplatesIn = "10% of 110 is 11. '{' is open bracket, but '}' is closing";
		const std::string savedTemplateString(stringWithNoTemplatesIn);
		THEN("Result is equal to given string and given map isn't changed")
		{
			std::string result = ExpandTemplate(stringWithNoTemplatesIn, params);

			REQUIRE(result == savedTemplateString);

			REQUIRE(stringWithNoTemplatesIn == savedTemplateString);
			REQUIRE(params == copiedParams);
		}
	}

	WHEN("Passing empty params map, the result will be the same string")
	{
		std::string regularString = "abcdef";
		const std::string savedRegularString(regularString);
		THEN("Result is equal to given string and given map isn't changed")
		{
			std::string result = ExpandTemplate(regularString, emptyParamsMap);

			REQUIRE(result == savedRegularString);

			REQUIRE(regularString == savedRegularString);
			REQUIRE(emptyParamsMap == copiedEmptyParamsMap);
		}
	}
}

SCENARIO("The given string has templates inside, which must be replaced according to given map")
{
	using ParamsMap = std::map<std::string, std::string>;

	ParamsMap paramsExampleFirst{
		{ "%USER_NAME%", "Ivan Petrov" },
		{ "{WEEK_DAY}", "Friday" },
	};
	const ParamsMap savedFirstParamsExample(paramsExampleFirst);

	ParamsMap paramsExampleRecursiveSecond{
		{ "%USER_NAME%", "Super %USER_NAME% {WEEK_DAY}" },
		{ "{WEEK_DAY}", "Friday. {WEEK_DAY}" }
	};
	const ParamsMap savedSecondParamsExample(paramsExampleRecursiveSecond);

	ParamsMap paramsExampleThird{
		{ "A", "[a]" },
		{ "AA", "[aa]" },
		{ "B", "[b]" },
		{ "BB", "[bb]" },
		{ "C", "[c]" },
		{ "CCC", "[ccc]" },
		{ "CCAB", "[ccab]" },
		{ "CA", "[ca]" },
	};
	const ParamsMap savedThridParamsExample(paramsExampleThird);
	
	ParamsMap paramsExampleFourth{
		{ "1ab", "[!AB]" },
		{ "1abc", "[!ABC]" },
		{ "1ad", "[!AD]" },
		{ "1adef", "[!ADEF]" },
		{ "12ab", "[!@AB]" },
		{ "12abc", "[!@ABC]" },
		{ "12ad", "[!@AD]" },
		{ "12adef", "[!@ADEF]" },
		{ "1234", "[!@#$]" },
		{ "123456", "[!@#$%^]" },
		{ "123456g", "[!@#$%^G]" },
		{ "12345678", "[!@#$%^&*]" },
		{ "12345678hk", "[!@#$%^&*HK]" },
		{ "1234567890", "[!@#$%^&*()]" },
		{ "7890123", "[&*()!@#]" },
		{ "2ab", "[2AB]" },
		{ "2abc", "[@ABC]" },
		{ "2ad", "[@AD]" },
		{ "2adef", "[@ADEF]" },
		{ "234", "[@#$]" },
		{ "2345lm", "[@#$%LM]" },
		{ "23456", "[@#$%^]" },
		{ "23456g", "[@#$%^G]" },
		{ "2345678", "[@#$%^&*]" },
		{ "2345678hk", "[@#$%^&*HK]" },
		{ "234567890", "[@#$%^&*()]" },
		{ "CCCC", "[cccc]" },
		{ "C", "[c]" },
		{ "B", "[b]" },
	};
	const ParamsMap savedFourthParamsExample(paramsExampleFourth);

	WHEN("Search substrings doesn't intersect and insertion values doesn't contain search substrings")
	{
		std::string tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		const std::string savedTpl{ tpl };
		const std::string expectedResult = "Hello, Ivan Petrov. Today is Friday.";

		THEN("All substrings replaced correctly. No changes in given string. No changes in given paramsMap")
		{
			std::string result = ExpandTemplate(tpl, paramsExampleFirst);

			REQUIRE(result == expectedResult);

			REQUIRE(tpl == savedTpl);
			REQUIRE(paramsExampleFirst == savedFirstParamsExample);
		}
	}

	WHEN("Search substrings are represented in insertion values")
	{
		std::string tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		const std::string savedTpl{ tpl };
		const std::string expectedResult = "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.";

		THEN("All substrings replaced only once. No changes in given string. No changes in given paramsMap")
		{
			std::string result = ExpandTemplate(tpl, paramsExampleRecursiveSecond);

			REQUIRE(result == expectedResult);

			REQUIRE(tpl == savedTpl);
			REQUIRE(paramsExampleRecursiveSecond == savedSecondParamsExample);
		}
	}

	WHEN("Search substrings are intersecting each other")
	{
		std::string tpl = "-AABBCCCCCABC+";
		const std::string savedTpl{ tpl };
		const std::string expectedResult = "-[aa][bb][ccc][ccab][c]+";

		THEN("Replaced only the longest substrings. No changes in given string. No changes in given paramsMap")
		{
			std::string result = ExpandTemplate(tpl, paramsExampleThird);

			REQUIRE(result == expectedResult);

			REQUIRE(tpl == savedTpl);
			REQUIRE(paramsExampleThird == savedThridParamsExample);
		}
	}

	WHEN("String template doesn't contain any search string")
	{
		std::string tpl = "-jjjjjjjjjjjjjjjjjjj                       jjjjjjjjjjjjjjjjjj+";

		const std::string savedTpl{ tpl };
		const std::string expectedResult = "-jjjjjjjjjjjjjjjjjjj                       jjjjjjjjjjjjjjjjjj+";

		THEN("String template and params didn't changed")
		{
			std::string result = ExpandTemplate(tpl, paramsExampleFourth);

			REQUIRE(result == expectedResult);

			REQUIRE(tpl == savedTpl);
			REQUIRE(paramsExampleFourth == savedFourthParamsExample);
		}
	}

	WHEN("String template contain search string at begin and at end")
	{
		std::string tpl = "1234567890                       234567890";

		const std::string savedTpl{ tpl };
		const std::string expectedResult = "[!@#$%^&*()]                       [@#$%^&*()]";

		THEN("String expanded correctly, string template and params didn't changed")
		{
			std::string result = ExpandTemplate(tpl, paramsExampleFourth);

			REQUIRE(result == expectedResult);

			REQUIRE(tpl == savedTpl);
			REQUIRE(paramsExampleFourth == savedFourthParamsExample);
		}
	}

	WHEN("String template contain search string at begin and at end")
	{
		std::string tpl = "1 123 1234 CCC122345lm 112345k CCCB 789012345678901234";

		const std::string savedTpl{ tpl };
		const std::string expectedResult = 
			"1 123 [!@#$] [c][c][c]12[@#$%LM] 1[!@#$]5k [c][c][c][b] [&*()!@#]456[&*()!@#]4";

		THEN("String expanded correctly, string template and params didn't changed")
		{
			std::string result = ExpandTemplate(tpl, paramsExampleFourth);

			REQUIRE(result == expectedResult);

			REQUIRE(tpl == savedTpl);
			REQUIRE(paramsExampleFourth == savedFourthParamsExample);
		}
	}

	//paramsExampleFourth = {
	//	{ "C", "[c]" },
	//	{ "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC", "[long]" }
	//};
	//
	//WHEN("Worst case")
	//{
	//	std::string tpl = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
	//
	//	const std::string savedTpl{ tpl };
	//	const std::string expectedResult = 
	//		"[c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c][c]";
	//
	//	THEN("String expanded correctly")
	//	{
	//		std::string result = ExpandTemplate(tpl, paramsExampleFourth);
	//
	//		REQUIRE(result == expectedResult);
	//
	//		REQUIRE(tpl == savedTpl);
	//		REQUIRE(paramsExampleFourth == savedFourthParamsExample);
	//	}
	//}
}