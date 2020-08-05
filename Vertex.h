
#ifndef PROJECT_VERTEX_H
#define PROJECT_VERTEX_H

#include "Edge.h"

#include <string>



class Vertex
{
private:
	std::string name;

	/**
	 * Checks whether the specified `name` is valid or not based on certain rules.
	 *
	 * @param name - the specified `name`.
	 * @return true if valid, false otherwise.
	 */
	static bool isValid(std::string name);

	/**
	 *  Checks if letters of an expression are in a certain range.
	 */
	static bool AreLettersInRange(std::string exp);

	/**
	 * Function to check whether two characters are opening
	 * and closing of same type.
	 */
	static bool ArePair(char opening, char closing);

	/**
	 * Checks if brackets in 'exp' are balanced.
	 *
	 * @param exp - the specified expression.
	 * @return true if balanced, false otherwise.
	 */
	static bool isBracketBalanced(std::string exp);

	/**
	 * Checks if ';' is between brackets.
	 */
	static bool isSemicolonValid(std::string exp);

public:
	Vertex() = default;
	Vertex(std::string name);
	Vertex(const Vertex& other);
	~Vertex();

	std::string getName() const;
	void setName(const std::string newName);

	//friend std::ostream& operator<<(std::ostream& os, const Vertex vertex);
	bool operator==(const Vertex& other) const;

};

//std::ostream& operator<<(std::ostream& os, const Vertex vertex);



#endif //PROJECT_VERTEX_H


