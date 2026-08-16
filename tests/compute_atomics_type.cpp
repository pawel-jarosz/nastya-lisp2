#include <gtest/gtest.h>

#include <nastya/machine.hpp>
#include <nastya/object.hpp>

namespace nastya
{

/*
Feature: Represent atomic objects

  Scenario: Represent an atom with a primitive value
    Given an atomic object with name "x" and value 42
    Then its type is Atom
    And its representation includes the name and value

  Scenario: Represent an atom with a list value
    Given an atomic object with name "items" containing [1, 2, 3]
    Then its type is Atom
    And its representation includes the name and list

  Scenario: Compute an atom with a primitive value
    Given an atomic object with name "x" and value 42
    When the atom is computed
    Then the result is the same atom object
    And its value remains unchanged

  Scenario: Compute an atom with a list value
    Given an atomic object with name "items" containing ["a", 1, 2.0]
    When the atom is computed
    Then the result is the same atom object
    And its list value is computed unchanged
*/

    TEST(ComputeAtomic, RepresentsAtomWithPrimitiveValue)
    {
        auto primitiveValue = std::make_unique<IntegerObject>(42);
        AtomObject input("x", std::move(primitiveValue));

        EXPECT_EQ(input.getType(), ObjectType::Atom);
        EXPECT_EQ(input.getName(), "x");
        EXPECT_EQ(input.getValue().getType(), ObjectType::Integer);
    }

    TEST(ComputeAtomic, RepresentsAtomWithListValue)
    {
        auto list = std::make_unique<ListObject>();
        lists::ListBuilder(*list)
            .addElement(1)
            .addElement(2)
            .addElement(3);
        
        AtomObject input("items", std::move(list));

        EXPECT_EQ(input.getType(), ObjectType::Atom);
        EXPECT_EQ(input.getName(), "items");
        EXPECT_EQ(input.getValue().getType(), ObjectType::List);
    }

    TEST(ComputeAtomic, RepresentsAtomWithListOfPrimitives)
    {
        auto list = std::make_unique<ListObject>();
        lists::ListBuilder(*list)
            .addElement(std::string("a"))
            .addElement(1)
            .addElement(2.0);
        
        AtomObject input("values", std::move(list));

        EXPECT_EQ(input.getType(), ObjectType::Atom);
        EXPECT_EQ(input.getName(), "values");
    }

    TEST(ComputeAtomic, ComputesAtomWithPrimitiveValue)
    {
        Machine machine;
        auto primitiveValue = std::make_unique<IntegerObject>(42);
        AtomObject input("x", std::move(primitiveValue));

        const Object& result = machine.compute(input);

        // Computing an atom returns its value
        EXPECT_EQ(result.getType(), ObjectType::Integer);
    }

    TEST(ComputeAtomic, ComputesAtomWithListValue)
    {
        Machine machine;
        auto list = std::make_unique<ListObject>();
        lists::ListBuilder(*list)
            .addElement(1)
            .addElement(2)
            .addElement(3);
        
        AtomObject input("items", std::move(list));

        const Object& result = machine.compute(input);

        // Computing an atom returns its value
        EXPECT_EQ(result.getType(), ObjectType::List);
        EXPECT_EQ(result.toString(), "List => [Integer => 1, Integer => 2, Integer => 3]");
    }

    TEST(ComputeAtomic, ComputesAtomWithListOfMixedTypes)
    {
        Machine machine;
        auto list = std::make_unique<ListObject>();
        lists::ListBuilder(*list)
            .addElement(std::string("abc"))
            .addElement(2)
            .addElement(2.0);
        
        AtomObject input("values", std::move(list));

        const Object& result = machine.compute(input);

        // Computing an atom returns its value
        EXPECT_EQ(result.getType(), ObjectType::List);
        EXPECT_EQ(
            result.toString(),
            "List => [String => \"abc\", Integer => 2, Float => 2.000000]");
    }
    
}
