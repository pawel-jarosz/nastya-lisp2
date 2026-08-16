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

    std::string AtomObject::toString() const {
        return stringify_object(value_->getType(), name_ + " => " + value_->toString());
    }

    std::string ListObject::toString() const {
        std::stringstream ss;
        ss << "List => [";
        const auto& elements = getElements();
        for (size_t i = 0; i < elements.size(); ++i) {
            ss << elements[i]->toString();
            if (i < elements.size() - 1) {
                ss << ", ";
            }
        }
        ss << "]";
        return ss.str();
    }
}
