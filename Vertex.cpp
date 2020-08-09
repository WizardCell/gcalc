
#include "Vertex.h"
#include "Exceptions.h"



Vertex::Vertex(const std::string name){
    if(name.empty()){
        throw IllegalName();
    }
    if(!isValid(name)){
        throw IllegalName();
    }
    this->name=name;
}

/*Vertex::Vertex(const Vertex& other) {
    this->name = other.name;
}*/


bool Vertex::operator==(const Vertex &other) const {
    return (this->name == other.name);
}

bool Vertex::isValid(const std::string name) {
    return (AreLettersInRange(name) && isBracketBalanced(name) && isSemicolonValid(name));
}


bool Vertex::AreLettersInRange(std::string exp) {
    if(exp.empty()){
        return false;
    }
    for (const char &c : exp) {
        if (isalnum(c) || isdigit(c) || (c == '[') || (c == ']') || (c == ';')) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
    }


bool Vertex::isBracketBalanced(std::string exp) {
    std::stack<char> stk;
    for (unsigned int i = 0; i < exp.length(); i++) {
        if (exp[i] == '[')
            stk.push(exp[i]);
        else if (exp[i] == ']') {
            if (stk.empty() ) {
                return false;
            }
            else {
                stk.pop();
            }
        }
    }
    return stk.empty();

}

bool Vertex::isSemicolonValid(std::string exp) {
    std::stack<char> stk;
    bool flag = true;
    for (char i : exp) {
        if (i == '[') {
            stk.push(i);
        }
        else if (i == ']') {
            stk.pop();
        }
        else if (i == ';'){
            if(stk.empty()){
                flag = false;
            }
        }
    }
    return flag;
}

std::string Vertex::getName() const {
    return name;
}



void Vertex::setName(const std::string newName) {
    if (isValid(newName)) {
        name = newName;
    }
}

bool Vertex::operator<(const Vertex& other) const
{
    return this->name < other.name;
}

bool Vertex::operator<=(const Vertex& other) const
{
    return this->name <= other.name;
}

bool Vertex::operator>(const Vertex& other) const
{
    return this->name > other.name;
}

bool Vertex::operator>=(const Vertex& other) const
{
    return this->name >= other.name;
}

//std::ostream& operator<<(std::ostream& os, Vertex vertex)
//{
//	return os << vertex.getName();
//}

