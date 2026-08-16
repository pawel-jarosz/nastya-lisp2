#include <nastya/object_type.hpp>

namespace nastya
{
    bool is_numeric(ObjectType type)
    {
        return (type == ObjectType::Integer || type == ObjectType::Float);
    }

    bool is_atomic(ObjectType type)
    {
        return (type == ObjectType::Atom);
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

    std::ostream& operator<<(std::ostream& os, ObjectType type)
    {
        switch (type) {
            case ObjectType::Object:
                os << "Object";
                break;
            case ObjectType::Atom:
                os << "Atom";
                break;
            case ObjectType::Integer:
                os << "Integer";
                break;
            case ObjectType::Float:
                os << "Float";
                break;
            case ObjectType::String:
                os << "String";
                break;
            case ObjectType::List:
                os << "List";
                break;
            case ObjectType::Lambda:
                os << "Lambda";
                break;
            default:
                os << "Unknown";
        }
        return os;
    }

}
