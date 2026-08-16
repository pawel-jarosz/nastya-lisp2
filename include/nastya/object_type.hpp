#pragma once

#include <ostream>

namespace nastya
{
    enum class ObjectType {
            Object,
            Atom,
            Integer,
            Float,
            String,
            List,
            Lambda
    };

    std::ostream& operator<<(std::ostream& os, ObjectType type);

    bool is_numeric(ObjectType type);
    bool is_primitive(ObjectType type);
    bool is_atomic(ObjectType type);
    bool is_list(ObjectType type);
    bool is_callable(ObjectType type);
}