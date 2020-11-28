#include "object.h"

Object::Object(math::vector<double> vector)
{
    _vector = vector;
}

Object::Object(const Object& obj)
{
    _vector = obj._vector;
}

math::vector<double>& Object::vector()
{
    return _vector;
}