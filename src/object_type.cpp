#include <nastya/object_type.hpp>

#include <nastya/object.hpp>

namespace nastya
{
    bool is_numeric(ObjectType type)
    {
        return (type == ObjectType::Integer || type == ObjectType::Float);
    }

    bool is_primitive(ObjectType type)
    {
        return (type == ObjectType::Integer || type == ObjectType::Float || type == ObjectType::String) ;
    }

    bool is_list(ObjectType type)
    {
        return type == ObjectType::List;
    }

    bool is_callable(ObjectType type)
    {
        return type == ObjectType::Lambda;
    }
}
