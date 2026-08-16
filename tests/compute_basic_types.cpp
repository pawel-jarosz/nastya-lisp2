#include <gtest/gtest.h>

#include <nastya/machine.hpp>
#include <nastya/object.hpp>

namespace nastya
{

/*
Feature: Compute primitive objects

  Scenario Outline: Computing a primitive returns the primitive unchanged
    Given a primitive object with value <value>
    When the object is computed
    Then the result is <expected>

    Examples:
      | value | expected          |
      | "abc" | String => "abc"   |
      | 2     | Integer => 2      |
      | 2.0   | Float => 2.000000 |
*/  
    TEST(ComputePrimitives, ComputesString)
    {
        Machine machine;
        StringObject input("abc");

        const Object& result = machine.compute(input);

        EXPECT_EQ(&result, &input);
        EXPECT_EQ(result.getType(), ObjectType::String);
        EXPECT_EQ(result.toString(), "String => \"abc\"");
    }

    TEST(ComputePrimitives, ComputesInteger)
    {
        Machine machine;
        IntegerObject input(2);

        const Object& result = machine.compute(input);

        EXPECT_EQ(&result, &input);
        EXPECT_EQ(result.getType(), ObjectType::Integer);
        EXPECT_EQ(result.toString(), "Integer => 2");
    }

    TEST(ComputePrimitives, ComputesFloat)
    {
        Machine machine;
        FloatObject input(2.0);

        const Object& result = machine.compute(input);

        EXPECT_EQ(&result, &input);
        EXPECT_EQ(result.getType(), ObjectType::Float);
        EXPECT_EQ(result.toString(), "Float => 2.000000");
    }
    
}
