#pragma once

#include <utility>
#include <memory>
#include <string>
#include <vector>

#include <nastya/object_type.hpp>
    
namespace nastya
{
    class Object;
    using UObjectPtr = std::unique_ptr<Object>;

    class Object {
    public:
        virtual ObjectType getType() const { return ObjectType::Object; }
        virtual ~Object() = default;

        virtual std::string toString() const = 0;
    };

    class AtomObject : public Object {
    public:
        AtomObject(const std::string& name, UObjectPtr value) : name_(name), value_(std::move(value)) {}
        ObjectType getType() const override { return ObjectType::Atom; }
        std::string toString() const override;
        const std::string getName() const { return name_; }
        const Object& getValue() const { return *value_; }
    private:
        std::string name_;
        const UObjectPtr value_;
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

    class ListObject : public Object {
    public:
        ListObject() = default;
        void addElement(UObjectPtr element) { elements_.emplace_back(std::move(element)); }
        ObjectType getType() const override { return ObjectType::List; }
        std::string toString() const override;
        std::vector<UObjectPtr>& getElements() { return elements_; }
    private:
        std::vector<UObjectPtr> elements_;
    };

    namespace lists {
        class ListBuilder {
        public:
            ListBuilder(ListObject& elements) : elements_(elements) {}
            ListBuilder& addElement(int value) { elements_.addElement(std::make_unique<IntegerObject>(value)); return *this; }
            ListBuilder& addElement(double value) { elements_.addElement(std::make_unique<FloatObject>(value)); return *this; }
            ListBuilder& addElement(const std::string& value) { elements_.addElement(std::make_unique<StringObject>(value)); return *this;}
            ListObject& build() { return elements_; }
            
        private:
            ListObject& elements_;
        };
    }
}
