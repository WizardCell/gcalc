
#include <cstring>
#include "Exceptions.h"

const char *IllegalArgument::what() const noexcept {
    return "Error: IllegalArgument";
}

const char *IllegalName::what() const noexcept {
    return "Error: Illegal name";
}

const char *UndefinedVariable::what() const noexcept {
    return to_print.c_str();
}

const char *UnrecognizedCommand::what() const noexcept {
    return to_print.c_str();
}

const char *EdgeMissingBeginPoint::what() const noexcept {
    return to_print.c_str();
}

const char *EdgeMissingEndPoint::what() const noexcept {
    return to_print.c_str();
}

const char *OutOfRange::what() const noexcept {
    return "Error: OutOfRange";
}

const char *SelfEdge::what() const noexcept {
    return "Error: Self edge";
}


const char *ParallelEdges::what() const noexcept {
    return "Error: Parallel edges";
}

const char *RedefinedVertex::what() const noexcept {
    return "Error: Redefined vertex";
}

const char *FileDidntOpen::what() const noexcept {
    return "Error: Couldn't open file";
}

const char *ReadFailed::what() const noexcept {
    return "Error: Couldn't read from file successfully";
}

const char *WriteFailed::what() const noexcept {
    return "Error: Couldn't write to file successfully";
}
