
#include "Vertex.h"




Vertex::Vertex(std::string name){
    if(!isValid(name)){
        throw; //todo define throw bad name
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
    for (const char &c : exp) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
            || (c == '[') || (c == ']') || (c == ';')) {
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
    for (unsigned int i = 0; i < exp.length(); i++) {
        if (exp[i] == '[') {
            stk.push(exp[i]);
        }
        else if (exp[i] == ']') {
            stk.pop();
        }
        else if (exp[i] == ';'){
            if(stk.empty()){
                return false;
            }
            else{
                return true;
            }
        }
    }
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

