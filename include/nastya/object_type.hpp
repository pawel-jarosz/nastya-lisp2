#pragma once

namespace nastya
{
    enum class ObjectType {
            Object,
            Integer,
            Float,
            String,
            List,
            Lambda
    };

    bool is_numeric(ObjectType type);
    bool is_primitive(ObjectType type);
    bool is_list(ObjectType type);
    bool is_callable(ObjectType type);
}