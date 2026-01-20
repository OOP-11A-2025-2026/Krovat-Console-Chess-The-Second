#ifndef INVALID_MOVE_H
#define INVALID_MOVE_H

#include <stdexcept>
#include <string>

using namespace std;

class InvalidMove : public runtime_error {
public:
    InvalidMove(const string &message) : runtime_error(message) {}
};

#endif