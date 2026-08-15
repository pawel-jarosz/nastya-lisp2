#pragma once

#include <string>

#include <nastya/object_type.hpp>
    
namespace nastya
{
    class Object {
    public:
        virtual ObjectType getType() const { return ObjectType::Object; }
        virtual ~Object() = default;

        virtual std::string toString() const = 0;
    };
}
