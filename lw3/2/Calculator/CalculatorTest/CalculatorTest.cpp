#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Calculator/CommandParser.h"

SCENARIO("Execute func")
{
	auto GetValue = [](std::string identifier)
	{
		const std::map<std::string, double> vars{
			{ "OperationIsNone", 122 },
			{ "AddVar1", 5 },
			{ "AddVar2", 10 },
			{ "SubVar1", 79 },
			{ "SubVar2", 13 },
			{ "MulVar1", 13 },
			{ "MulVar2", 87 },
			{ "DivVar1", 13 },
			{ "DivVar2", 6.5 },
			{ "Undefined", NAN }
		};

		return vars.at(identifier);
	}; 
	
	WHEN("Func with 1 arg without operation")
	{
		THEN("Ans = value of var")
		{
			Function func("OperationIsNone");
			CHECK(func.Execute(GetValue) == 122);
		}
	}
	WHEN("Sum 5 and 10")
	{
		THEN("Ans = 15")
		{
			Function func("AddVar1", Operations::ADD, "AddVar2");
			CHECK(func.Execute(GetValue) == 15);
		}
	}
	WHEN("Difference 79 and 13")
	{
		THEN("Ans = 66")
		{
			Function func("SubVar1", Operations::SUB, "SubVar2");
			CHECK(func.Execute(GetValue) == 66);
		}
	}
	WHEN("Multiply 13 with 87")
	{
		THEN("Ans = 1131")
		{
			Function func("MulVar1", Operations::MUL, "MulVar2");
			CHECK(func.Execute(GetValue) == 1131);
		}
	}
	WHEN("Division 13 to 6.5")
	{
		THEN("Ans = 2")
		{
			Function func("DivVar1", Operations::DIV, "DivVar2");
			CHECK(func.Execute(GetValue) == 2);
		}
	}
	WHEN("Var is not undefined")
	{
		THEN("Ans = Nan")
		{
			Function func("AddVar1", Operations::ADD, "Undefined");
			CHECK(std::isnan(func.Execute(GetValue)));
		}
	}
	WHEN("Opearation = none with 2 args")
	{
		THEN("Will be throw exception")
		{
			auto declareFunction = []()
			{
				Function func("AddVar1", Operations::NONE, "AddVar2");
			};
			CHECK_THROWS_WITH(declareFunction(), "Function with 2 args can't has none operation");
		}
	}
	WHEN("Identifier is empty fn with 1 arg")
	{
		THEN("Will be throw exception")
		{
			auto declareFunction = []()
			{
				Function func("");
			};
			CHECK_THROWS_WITH(declareFunction(), "Identifier can't be empty str");
		}
	}
	WHEN("Identifiers are empty fn with 2 arg")
	{
		THEN("Will be throw exception")
		{
			auto declareFunction = []()
			{
				Function func("", Operations::SUB, "");
			};
			CHECK_THROWS_WITH(declareFunction(), "Identifier can't be empty str");
		}
	}
}

SCENARIO("Add new var")
{
	WHEN("Declare new var")
	{
		THEN("Var has Nan value")
		{
			Calculator calculator;
			calculator.Var("id");
			CHECK(std::isnan(calculator.GetValueByIdentifier("id")));
		}
	}
	WHEN("Identifier already used")
	{
		THEN("Will be throw exception")
		{
			Calculator calculator;
			calculator.Var("id");
			CHECK_THROWS_WITH(calculator.Var("id"), "Identifier already used");
		}
	}
}

SCENARIO("Edit var by let")
{
	std::string identifier = "id";
	std::string value = "25";

	WHEN("Value not declared")
	{
		THEN("Value will be declare and has value")
		{
			Calculator calculator;
			calculator.Let(identifier, value);
			CHECK(calculator.GetValueByIdentifier(identifier) == std::stod(value));
		}
	}

	WHEN("Value already declared")
	{
		THEN("Value has new value")
		{
			Calculator calculator;
			calculator.Var(identifier);
			calculator.Let(identifier, value);
			CHECK(calculator.GetValueByIdentifier(identifier) == std::stod(value));
		}
	}
	WHEN("Value is var")
	{
		THEN("New var has value of entered var")
		{
			Calculator calculator;
			calculator.Let("var1", "5");
			calculator.Let("var2", "var1");
			CHECK(calculator.GetValueByIdentifier("var2") == 5);
		}
	}
	WHEN("Value is func")
	{
		THEN("New var has result of entered func")
		{
			Calculator calculator;
			calculator.Let("var1", "2");
			calculator.Let("var2", "3");
			calculator.FnBinary("func", "var1", Operations::ADD, "var2");
			calculator.Let(identifier, "func");
			CHECK(calculator.GetValueByIdentifier(identifier) == 5);
		}
	}
	WHEN("Value has unknown identifier")
	{
		THEN("Will be throw exception")
		{
			Calculator calculator;
			CHECK_THROWS_WITH(calculator.Let("var1", "var2"), "Invalid value");
		}
	}
}
SCENARIO("Declare functions")
{
	WHEN("Declare func with unknown identifiers")
	{
		THEN("Will be throw exception")
		{
			Calculator calculator;
			CHECK_THROWS_WITH(calculator.FnBinary("func", "1arg", Operations::ADD, "2arg"), "Unknown argument");
		}
	}
	WHEN("Declare func with 1 argument")
	{
		THEN("Count of funcs will be increase")
		{
			Calculator calculator;
			calculator.Let("1arg", "25");
			calculator.FnUnary("func", "1arg");
			CHECK(calculator.GetValueByIdentifier("func") == 25);
		}
	}
	WHEN("Declare func with operation and 2 argument")
	{
		THEN("Count of funcs will be increase")
		{
			Calculator calculator;
			calculator.Let("1arg", "20");
			calculator.Let("2arg", "50");
			calculator.FnBinary("func", "1arg", Operations::ADD, "2arg");
			CHECK(calculator.GetValueByIdentifier("func") == 70);
		}
	}
	WHEN("Identifier already used")
	{
		THEN("Will be throw exception")
		{
			Calculator calculator;
			calculator.Var("id");
			CHECK_THROWS_WITH(calculator.FnBinary("id", "arg1", Operations::ADD, "arg2"), "Identifier already used");
		}
	}
	WHEN("Args of func are funcs: (5 + 10) * (13 / 6.5)")
	{
		THEN("Result of func = 30")
		{
			Calculator calculator;
			calculator.Let("var1", "5");
			calculator.Let("var2", "10");
			calculator.Let("var3", "13");
			calculator.Let("var4", "6.5");
			calculator.FnBinary("fn1", "var1", Operations::ADD, "var2");
			calculator.FnBinary("fn2", "var3", Operations::DIV, "var4");
			calculator.FnBinary("fn3", "fn1", Operations::MUL, "fn2");
			CHECK(calculator.GetValueByIdentifier("fn3") == 30);
		}
	}
}

std::string GetAnsFromParser(const std::string& command, CommandParser& commandParser)
{
	std::istringstream input(command);
	std::stringstream out;
	commandParser.Handle(input, out);
	std::string ans;
	std::string line;
	while (std::getline(out, line))
	{
		ans = ans + line + "\n";
	}
	return ans;
}

SCENARIO("Parsing commands")
{
	Calculator calculator;
	CommandParser commandParser(calculator);
	WHEN("Unknown command")
	{
		std::string ans = GetAnsFromParser("command x", commandParser);
		CHECK(ans == "Unknown command\n");
	}
	WHEN("Invalid var command")
	{
		std::string ans = GetAnsFromParser("createvar x", commandParser);
		CHECK(ans == "Invalid command\n");
	}
	WHEN("Invalid var command, invalid identifier")
	{
		std::string ans = GetAnsFromParser("var 1x", commandParser);
		CHECK(ans == "Invalid command\n");
	}
	WHEN("Var command")
	{
		std::string ans = GetAnsFromParser("var x", commandParser);
		CHECK(ans.empty());
	}
	WHEN("Invalid let command")
	{
		std::string ans = GetAnsFromParser("let x", commandParser);
		CHECK(ans == "Invalid command\n");
	}
	WHEN("Invalid let command, invalid identifier")
	{
		std::string ans = GetAnsFromParser("let 1x = 2", commandParser);
		CHECK(ans == "Invalid command\n");
	}
	WHEN("Let command")
	{
		std::string ans = GetAnsFromParser("let x = 4", commandParser);
		CHECK(ans.empty());
	}
	WHEN("Invalid fn command")
	{
		std::string ans = GetAnsFromParser("fn f", commandParser);
		CHECK(ans == "Invalid command\n");
	}
	WHEN("Invalid fn command, invalid identifier")
	{
		std::string ans = GetAnsFromParser("let x=8\nfn 1f = x * x", commandParser);
		CHECK(ans == "Invalid command\n");
	}
	WHEN("Fn command")
	{
		std::string ans = GetAnsFromParser("let x=8\nfn f = x * x", commandParser);
		CHECK(ans.empty());
	}
	WHEN("Invalid print command")
	{
		std::string ans = GetAnsFromParser("print x, y", commandParser);
		CHECK(ans == "Invalid command\n");
	}
	WHEN("Print command var value")
	{
		std::string ans = GetAnsFromParser("let x=4\nprint x", commandParser);
		CHECK(ans == "4.00\n");
	}
	WHEN("Print command fn value")
	{
		std::string ans = GetAnsFromParser("let x=4\nfn f=x*x\nprint f", commandParser);
		CHECK(ans == "16.00\n");
	}
	WHEN("Invalid printvars command")
	{
		std::string ans = GetAnsFromParser("let x=4\nlet y=5\nprintvarsss", commandParser);
		CHECK(ans == "Invalid command\n");
	}
	WHEN("Printvars command")
	{
		std::string ans = GetAnsFromParser("let x=4\nlet y=5\nprintvars", commandParser);
		CHECK(ans == "x:4.00\ny:5.00\n");
	}
	WHEN("Invalid printfns command")
	{
		std::string ans = GetAnsFromParser("let x=4\nlet y=5\nfn f1=x*y\nfn f2=x*x\ndsdprintfns", commandParser);
		CHECK(ans == "Invalid command\n");
	}
	WHEN("Printfns command")
	{
		std::string ans = GetAnsFromParser("let x=4\nlet y=5\nfn f1=x*y\nfn f2=x*x\nprintfns", commandParser);
		CHECK(ans == "f1:20.00\nf2:16.00\n");
	}
	WHEN("Using reserved identifier")
	{
		std::string ans = GetAnsFromParser("var let", commandParser);
		CHECK(ans == "Identifier has already been reserved\n");
	}
}
