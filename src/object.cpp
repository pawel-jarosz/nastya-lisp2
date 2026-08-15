#include <nastya/object.hpp>

#include <sstream>

namespace nastya
{
    std::string stringify_object(ObjectType type, std::string value) {
        std::stringstream ss;
        ss << type << " => " << value;
        return ss.str();
    }

    std::string StringObject::toString() const {
        return stringify_object(getType(), "\"" + value_ + "\"");
    }

    std::string IntegerObject::toString() const {
        return stringify_object(getType(), std::to_string(value_));
    }

    std::string FloatObject::toString() const {
        return stringify_object(getType(), std::to_string(value_));
    }
}
