
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class Exception             : public std::exception {
};

class ProjectException      : public Exception {
};

class IllegalArgument       : public ProjectException {
public:
    const char *what() const noexcept override;
};

class IllegalName           : public ProjectException {
public:
    const char *what() const noexcept override;
};

class UndefinedVariable     : public ProjectException {
public:
    std::string to_print;
    explicit UndefinedVariable(std::string variable):to_print("Error: Undefined variable '" + variable + "'"){}
    const char *what() const noexcept override;
};

class UnrecognizedCommand   : public ProjectException {
public:
    std::string to_print;
    explicit UnrecognizedCommand(std::string command):to_print("Error: Unrecognized command '" + command + "'"){}
    const char *what() const noexcept override;
};

class EdgeMissingBeginPoint : public ProjectException {
public:
    std::string to_print;
    EdgeMissingBeginPoint(std::string src, std::string dst):to_print("Error: Cannot add edge <" + src + "," + dst + "> due to missing beginpoint."){}

    const char *what() const noexcept override;
};

class EdgeMissingEndPoint   : public ProjectException {
public:
    std::string to_print;
    EdgeMissingEndPoint(std::string src, std::string dst):to_print("Error: Cannot add edge <" + src + "," + dst + "> due to missing beginpoint."){}

    const char *what() const noexcept override;
};

class OutOfRange            : public ProjectException {
public:
    const char *what() const noexcept override;
};

class SelfEdge              : public ProjectException {
public:
    const char *what() const noexcept override;
};

class ParallelEdges         : public ProjectException {
public:
    const char *what() const noexcept override;
};

class RedefinedVertex       : public ProjectException {
public:
    const char *what() const noexcept override;
};

class FileDidntOpen         : public ProjectException {
public:
    const char *what() const noexcept override;
};

class ReadFailed         : public ProjectException {
public:
    const char *what() const noexcept override;
};

class WriteFailed         : public ProjectException {
public:
    const char *what() const noexcept override;
};



#endif