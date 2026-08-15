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
        else if (is_numeric(obj.getType())) {
            return obj;
        }
        else {
            throw std::runtime_error("Unhandled object type.");
        }
    }
}