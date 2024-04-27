#include "CommandParser.h"
#include <map>

namespace {
	const int CREATE_SPHERE = 0;
	const int CREATE_PARALLELEPIPED = 1;
	const int CREATE_CYLINDER = 2;
	const int CREATE_CONE = 3;
	const int CREATE_COMPOUND = 4;
	const int ENOUGH_BODIES = 5;
	const std::map<int, std::string> COMMAND_CREATE_KEYS{
		{CREATE_SPHERE, "Sphere"},
		{CREATE_PARALLELEPIPED, "Parallelepiped"},
		{CREATE_CYLINDER, "Cylinder"},
		{CREATE_CONE, "Cone"},
		{CREATE_COMPOUND, "Compound"},
		{ENOUGH_BODIES, "Enough"}
	};
	const int PRINT_ALL_BODIES = 0;
	const int PRINT_BODY_MAX_MASS = 1;
	const int PRINT_LIGHTEST_BODY = 2;
	const int EXIT = 3;
	const std::map<int, std::string> COMMAND_KEYS{
		{PRINT_ALL_BODIES, "Print all bodies"},
		{PRINT_BODY_MAX_MASS, "Print body with max mass"},
		{PRINT_LIGHTEST_BODY, "Print lightest body in liquid"},
		{EXIT, "Exit"}
	};
}

void CommandParser::Handle(std::istream& in, std::ostream& out)
{
	PrintCreateCommands(out);
	int command;
	bool isCreatingBodies = true;
	while (in >> command)
	{
		try
		{
			if (isCreatingBodies)
			{
				if (command == ENOUGH_BODIES)
				{
					isCreatingBodies = false;
					PrintCommands(out);
					continue;
				}
				DefineCreateCommands(command, in);
				out << std::endl << "Success created" << std::endl;
			}
			else
			{
				if (command == EXIT)
				{
					break;
				}
				DefineCommands(command, out);
			}
		}
		catch (const std::exception& e)
		{
			out << e.what() << std::endl;
		}
	}
}

void CommandParser::PrintCreateCommands(std::ostream& out) const
{
	for (auto commandPair : COMMAND_CREATE_KEYS)
	{
		out << "[" << commandPair.first << "]: " << commandPair.second << "\n";
	}
}

void CommandParser::DefineCreateCommands(int command, std::istream& in)
{
	switch (command)
	{
	case CREATE_SPHERE:
		CreateSphere(in);
		break;
	case CREATE_PARALLELEPIPED:
		CreateParallelepiped(in);
		break;
	case CREATE_CYLINDER:
		CreateCylinder(in);
		break;
	case CREATE_CONE:
		CreateCone(in);
		break;
	case CREATE_COMPOUND:
		CreateCompound(in);
		break;
	default:
		throw std::invalid_argument("Unknown command to create");
	}
}

void CommandParser::CreateSphere(std::istream& in)
{
	double density, radius;
	in >> density >> radius;
	m_store.CreateSphere(density, radius);
}

void CommandParser::CreateParallelepiped(std::istream& in)
{
	double density, width, height, depth;
	in >> density >> width >> height >> depth;
	m_store.CreateParallelepiped(density, width, height, depth);
}

void CommandParser::CreateCylinder(std::istream& in)
{
	double density, baseRadius, height;
	in >> density >> baseRadius >> height;
	m_store.CreateCylinder(density, baseRadius, height);
}

void CommandParser::CreateCone(std::istream& in)
{
	double density, baseRadius, height;
	in >> density >> baseRadius >> height;
	m_store.CreateCone(density, baseRadius, height);
}

void CommandParser::CreateCompound(std::istream& in)
{
	auto bodies = CreateBodiesForCompound(in);
	m_store.CreateCompound(bodies);
}

void CommandParser::PrintCommands(std::ostream& out) const
{
	for (auto commandPair : COMMAND_KEYS)
	{
		out << "[" << commandPair.first << "]: " << commandPair.second << "\n";
	}
}

void CommandParser::DefineCommands(int command, std::ostream& out) const
{
	switch (command)
	{
	case PRINT_ALL_BODIES:
		PrintAllBodies(out);
		break;
	case PRINT_BODY_MAX_MASS:
		PrintBodyWithMaxMass(out);
		break;
	case PRINT_LIGHTEST_BODY:
		PrintLightestBodyInLiquid(out);
		break;
	default:
		throw std::invalid_argument("Unknown command");
	}
}

void CommandParser::PrintAllBodies(std::ostream& out) const
{
	out << std::endl;
	auto printFn = [&out](const std::shared_ptr<CBody>& body)
	{
		out << body->ToString();
	};
	m_store.ExecuteFnToAllBodies(printFn);
	out << std::endl;
}

void CommandParser::PrintBodyWithMaxMass(std::ostream& out) const
{
	auto body = m_store.FindBodyWithMaxMass();
	out << std::endl << body->ToString() << std::endl;
}

void CommandParser::PrintLightestBodyInLiquid(std::ostream& out) const
{
	auto body = m_store.FindLightestBodyInLiquid();
	out << std::endl << body->ToString() << std::endl;
}

std::vector<std::shared_ptr<CBody>> CommandParser::CreateBodiesForCompound(std::istream& in)
{
	int command;
	std::vector<std::shared_ptr<CBody>> bodies;

	while (in >> command)
	{
		switch (command)
		{
		case CREATE_SPHERE:
			bodies.push_back(CreateSphereForCompound(in));
			break;
		case CREATE_PARALLELEPIPED:
			bodies.push_back(CreateParallelepipedForCompound(in));
			break;
		case CREATE_CYLINDER:
			bodies.push_back(CreateCylinderForCompound(in));
			break;
		case CREATE_CONE:
			bodies.push_back(CreateConeForCompound(in));
			break;
		case CREATE_COMPOUND:
			bodies.push_back(CreateCompoundForCompound(in));
			break;
		default:
			return bodies;
		}
	}
}

std::shared_ptr<CSphere> CommandParser::CreateSphereForCompound(std::istream& in)
{
	int density, radius;
	in >> density >> radius;
	CSphere sphere(density, radius);
	return std::make_shared<CSphere>(sphere);
}

std::shared_ptr<CParallelepiped> CommandParser::CreateParallelepipedForCompound(std::istream& in)
{
	int density, width, height, depth;
	in >> density >> width >> height >> depth;
	CParallelepiped parallelipiped(density, width, height, depth);
	return std::make_shared<CParallelepiped>(parallelipiped);
}

std::shared_ptr<CCylinder> CommandParser::CreateCylinderForCompound(std::istream& in)
{
	int density, baseRadius, height;
	in >> density >> baseRadius >> height;
	CCylinder cylinder(density, baseRadius, height);
	return std::make_shared<CCylinder>(cylinder);
}

std::shared_ptr<CCone> CommandParser::CreateConeForCompound(std::istream& in)
{
	int density, baseRadius, height;
	in >> density >> baseRadius >> height;
	CCone cone(density, baseRadius, height);
	return std::make_shared<CCone>(cone);
}

std::shared_ptr<CCompound> CommandParser::CreateCompoundForCompound(std::istream& in)
{
	auto bodies = CreateBodiesForCompound(in);
	CCompound compound(bodies);
	return std::make_shared<CCompound>(compound);
}
