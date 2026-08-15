#pragma once

#include <nastya/object.hpp>

namespace nastya
{
    class Machine {
    public:
        virtual ~Machine() = default;
        const Object& compute(const Object& obj);
    };
}
