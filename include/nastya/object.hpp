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

    class StringObject : public Object {
    public:
        StringObject(const std::string& value) : value_(value) {}
        ObjectType getType() const override { return ObjectType::String; }
        std::string toString() const override;
    private:
        std::string value_;
    };

    class IntegerObject : public Object {
    public:
        IntegerObject(int value) : value_(value) {}
        ObjectType getType() const override { return ObjectType::Integer; }
        std::string toString() const override;
    private:
        int value_;
    };

    class FloatObject : public Object {
    public:
        FloatObject(double value) : value_(value) {}
        ObjectType getType() const override { return ObjectType::Float; }
        std::string toString() const override;
    private:
        double value_;
    };

}
