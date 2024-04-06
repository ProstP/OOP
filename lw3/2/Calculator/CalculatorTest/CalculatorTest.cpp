#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Calculator/CommandParser.h"
#include "../Calculator/UndefinedValue.h"

SCENARIO("Execute func")
{
	const std::map<std::string, std::string> vars{
		{ "OperationIsNone", "122" },
		{ "1AddVar", "5" },
		{ "2AddVar", "10" },
		{ "1SubVar", "79" },
		{ "2SubVar", "13" },
		{ "1MulVar", "13" },
		{ "2MulVar", "87" },
		{ "1DivVar", "13" },
		{ "2DivVar", "6.5" },
		{ "Undefined", UNDEFINED_VALUE}
	};
	WHEN("Func with 1 arg without operation")
	{
		THEN("Ans = value of var")
		{
			Function func("OperationIsNone", Operations::NONE, "");
			CHECK(std::stod(func.Execute(vars, {})) == 122);
		}
	}
	WHEN("Sum 5 and 10")
	{
		THEN("Ans = 15")
		{
			Function func("1AddVar", Operations::ADD, "2AddVar");
			CHECK(std::stod(func.Execute(vars, {})) == 15);
		}
	}
	WHEN("Difference 79 and 13")
	{
		THEN("Ans = 66")
		{
			Function func("1SubVar", Operations::SUB, "2SubVar");
			CHECK(std::stod(func.Execute(vars, {})) == 66);
		}
	}
	WHEN("Multiply 13 with 87")
	{
		THEN("Ans = 1131")
		{
			Function func("1MulVar", Operations::MUL, "2MulVar");
			CHECK(std::stod(func.Execute(vars, {})) == 1131);
		}
	}
	WHEN("Division 13 to 6.5")
	{
		THEN("Ans = 2")
		{
			Function func("1DivVar", Operations::DIV, "2DivVar");
			CHECK(std::stod(func.Execute(vars, {})) == 2);
		}
	}
	WHEN("Var is not undefined")
	{
		THEN("Ans = Nan")
		{
			Function func("1AddVar", Operations::ADD, "Undefined");
			CHECK(func.Execute(vars, {}) == UNDEFINED_VALUE);
		}
	}
	WHEN("Args of funcs are funcs: (5 + 10) and (13 / 6.5)")
	{
		THEN("15 * 2 = 30")
		{
			Function funcSum("1AddVar", Operations::ADD, "2AddVar");
			Function funcDiv("1DivVar", Operations::DIV, "2DivVar");
			const std::map<std::string, Function> funcs{
				{ "Sum", funcSum },
				{ "Div", funcDiv }
			};
			Function func("Sum", Operations::MUL, "Div");
			CHECK(std::stod(func.Execute(vars, funcs)) == 30);
		}
	}
	WHEN("Identifier is unknown")
	{
		THEN("Will throw exception")
		{
			Function func("1DivVar", Operations::DIV, "unknown");
			CHECK_THROWS_WITH(func.Execute(vars, {}), "Unknown identifier: unknown");
		}
	}
}

SCENARIO("Add new var")
{
	WHEN("Declare new var")
	{
		THEN("Count of vars will be increase and var has undefined value")
		{
			Calculator calculator;
			calculator.Var("id");
			auto vars = calculator.GetVars();
			CHECK(vars.size() == 1);
			CHECK(vars["id"] == UNDEFINED_VALUE);
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
			auto vars = calculator.GetVars();
			CHECK(vars.size() == 1);
			CHECK(vars.at(identifier) == value);
		}
	}

	WHEN("Value already declared")
	{
		THEN("Value has new value")
		{
			Calculator calculator;
			calculator.Var(identifier);
			calculator.Let(identifier, value);
			auto vars = calculator.GetVars();
			CHECK(vars.at(identifier) == value);
		}
	}
	WHEN("Value is var")
	{
		THEN("New var has value of entered var")
		{
			Calculator calculator;
			calculator.Let("var1", "5");
			calculator.Let("var2", "var1");
			auto vars = calculator.GetVars();
			CHECK(vars.at("var2") == "5");
		}
	}
	WHEN("Value is func")
	{
		THEN("New var has value of entered var")
		{
			Calculator calculator;
			calculator.Let("var1", "2");
			calculator.Let("var2", "3");
			calculator.Fn("func", "var1", Operations::ADD, "var2");
			calculator.Let(identifier, "func");
			auto vars = calculator.GetVars();
			CHECK(vars.at(identifier) == "5.000000");
		}
	}
	WHEN("Value is invalid")
	{
		THEN("New var has value of entered var")
		{
			Calculator calculator;
			CHECK_THROWS_WITH(calculator.Let(identifier, "value"), "Value must be digit or var");
		}
	}
}

SCENARIO("Declare functions")
{
	WHEN("Declare func with 1 argument")
	{
		THEN("Count of funcs will be increase")
		{
			Calculator calculator;
			calculator.Fn("func", "1arg");
			CHECK(calculator.GetFuncs().size() == 1);
		}
	}
	WHEN("Declare func with operation and 2 argument")
	{
		THEN("Count of funcs will be increase")
		{
			Calculator calculator;
			calculator.Fn("func", "1arg", Operations::ADD, "2arg");
			CHECK(calculator.GetFuncs().size() == 1);
		}
	}
	WHEN("Identifier already used")
	{
		THEN("Will be throw exception")
		{
			Calculator calculator;
			calculator.Var("id");
			CHECK_THROWS_WITH(calculator.Fn("id", "arg1", Operations::ADD, "arg2"), "Identifier already used");
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
	WHEN("Fn command")
	{
		std::string ans = GetAnsFromParser("fn f = x * x", commandParser);
		CHECK(ans.empty());
	}
	WHEN("Invalid print command")
	{
		std::string ans = GetAnsFromParser("print x, y", commandParser);
		CHECK(ans == "Invalid command\n");
	}
	WHEN("Print command")
	{
		std::string ans = GetAnsFromParser("let x=4\nfn f=x*x\nprint f", commandParser);
		CHECK(ans == "16.00\n");
	}
	WHEN("Printvars command")
	{
		std::string ans = GetAnsFromParser("let x=4\nlet y=5\nprintvars", commandParser);
		CHECK(ans == "x:4.00\ny:5.00\n");
	}
	WHEN("Printfns command")
	{
		std::string ans = GetAnsFromParser("let x=4\nlet y=5\nfn f1=x*y\nfn f2=x*x\nprintfns", commandParser);
		CHECK(ans == "f1:20.00\nf2:16.00\n");
	}
}
