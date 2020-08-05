
#include "Vertex.h"

#include <stack>
#include <iostream>


Vertex::Vertex(std::string name)
	:name(name)
{
	std::cout << "vertex constructed" << std::endl;
}

Vertex::Vertex(const Vertex& other)
{
	this->name = other.name;
}

Vertex::~Vertex()
{

}

bool Vertex::operator==(const Vertex& other) const
{
	return this->name == other.name;
}

bool Vertex::isValid(const std::string name)
{
	return AreLettersInRange(name) && isBracketBalanced(name) && isSemicolonValid(name);
}

bool Vertex::AreLettersInRange(std::string exp)
{
	for (const char& c : exp)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
			|| c == '[' || c == ']' || c == ';')
		{
			continue;
		}
		else
		{
			return false;
		}
	}	

	return true;
}

// Helper function
bool Vertex::ArePair(char opening, char closing)
{
	if (opening == '[' && closing == ']')
		return true;
	return false;
}

bool Vertex::isBracketBalanced(std::string exp)
{
	std::stack<char> stk;
	for (unsigned int i = 0; i < exp.length(); i++)
	{
		if (exp[i] == '[')
			stk.push(exp[i]);
		else if (exp[i] == ']')
		{
			if (stk.empty() || !ArePair(stk.top(), exp[i]))
				return false;
			else
				stk.pop();
		}
	}
	return stk.empty() ? true : false;

}

bool Vertex::isSemicolonValid(std::string exp)
{
	bool canGetSemicolon = true;
	for (const char& c : exp)
	{
		if (c == ';'  && !canGetSemicolon)
		{
			return false;
		}
		else if (c == '[')
		{
			canGetSemicolon = true;
		} 
		else if(c == ']')
		{
			canGetSemicolon = false;
		}
		else
		{
			continue;
		}
	}
	return true;
}

std::string Vertex::getName() const
{
	return name;
}

void Vertex::setName(const std::string newName)
{
	if (isValid(newName))
	{
		name = newName;
	}
}

//std::ostream& operator<<(std::ostream& os, Vertex vertex)
//{
//	return os << vertex.getName();
//}

