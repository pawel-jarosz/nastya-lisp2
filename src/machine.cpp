#include <nastya/machine.hpp>

#include <stdexcept>

namespace nastya
{
    const Object& Machine::compute(const Object& obj)
    {
        if (is_list(obj.getType())) {
            // TODO: Implement list computation logic here
            throw std::runtime_error("List computation not implemented yet.");
        }
        else if (is_primitive(obj.getType())) {
            return obj;
        }
        else if (is_atomic(obj.getType())) {

            return dynamic_cast<const AtomObject&>(obj).getValue();
        }
        else {
            throw std::runtime_error("Unhandled object type.");
        }
    }
}
