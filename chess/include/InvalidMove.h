#ifndef INVALID_MOVE_H
#define INVALID_MOVE_H

#include <stdexcept>
#include <string>

class InvalidMove : public std::runtime_error {
public:
    InvalidMove(const std::string &message) : std::runtime_error(message) {}
};

#endif