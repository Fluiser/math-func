#include "math_vector.h"
#ifndef OBJECT_H
#define OBJECT_H

class Object {
    math::vector<double> _vector;
public:
    Object() = default;

    Object(math::vector<double>);

    Object(const Object &);

    math::vector<double>& vector();
};

#endif