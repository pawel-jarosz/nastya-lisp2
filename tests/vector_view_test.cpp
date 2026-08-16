/*
Feature: Access vectors and non-owning subvector views

  Scenario: Build an owning vector incrementally
    Given a default-constructed ObjectsVector
    When copyable and movable elements are pushed into it
    Then its size grows after each insertion
    And it stores the inserted values

  Scenario: Store and access objects in an owning vector
    Given an ObjectsVector containing 10, 20, and 30
    When it is accessed through the GenericObjectList interface
    Then its size is 3
    And its offset is 0
    And its elements retain their order

  Scenario: View a suffix of an object list
    Given an ObjectsVector containing 10, 20, 30, and 40
    When an ObjectsSubvectorView is created at offset 2
    Then its size is 2
    And its offset is 2
    And it refers to the original elements 30 and 40

  Scenario: View an empty suffix
    Given an ObjectsVector containing 10 and 20
    When an ObjectsSubvectorView is created at the vector size
    Then its size is 0
    And its offset is the vector size

  Scenario: Create a view from another view
    Given a view of 20, 30, and 40
    When another view is created from it at offset 1
    Then the nested view contains 30 and 40
    And its offset relative to its source is 1

  Scenario: Represent a list using a subvector view
    Given an owning object vector containing 10, 20, and 30
    When a ListObject is constructed from its subvector at offset 1
    Then the list contains 20 and 30 without copying the objects
*/

#include <gtest/gtest.h>

#include <nastya/vector_view.hpp>
#include <nastya/object.hpp>

#include <memory>
#include <vector>

namespace nastya::data_structures {

TEST(ObjectsVectorTest, DefaultConstructsAsEmpty)
{
    ObjectsVector<int> objects;

    EXPECT_EQ(objects.size(), 0U);
    EXPECT_EQ(objects.offset(), 0U);
}

TEST(ObjectsVectorTest, PushBackCopiesLvaluesAndMovesRvalues)
{
    ObjectsVector<int> copied_objects;
    const int value = 42;
    copied_objects.push_back(value);
    copied_objects.push_back(7);

    EXPECT_EQ(copied_objects.size(), 2U);
    EXPECT_EQ(copied_objects[0], 42);
    EXPECT_EQ(copied_objects[1], 7);

    ObjectsVector<std::unique_ptr<int>> moved_objects;
    auto pointer = std::make_unique<int>(99);
    const int* original_address = pointer.get();
    moved_objects.push_back(std::move(pointer));

    EXPECT_EQ(moved_objects.size(), 1U);
    EXPECT_EQ(pointer, nullptr);
    EXPECT_EQ(moved_objects[0].get(), original_address);
    EXPECT_EQ(*moved_objects[0], 99);
}

TEST(ObjectsVectorTest, StoresElementsAndImplementsGenericObjectList)
{
    ObjectsVector<int> objects(std::vector<int>{10, 20, 30});
    const GenericObjectList<int>& list = objects;

    EXPECT_EQ(list.size(), 3U);
    EXPECT_EQ(list.offset(), 0U);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 20);
    EXPECT_EQ(list[2], 30);
}

TEST(ObjectsSubvectorViewTest, ExposesSuffixWithoutCopyingElements)
{
    ObjectsVector<int> objects(std::vector<int>{10, 20, 30, 40});
    ObjectsSubvectorView<int> view(objects, 2);

    EXPECT_EQ(view.size(), 2U);
    EXPECT_EQ(view.offset(), 2U);
    EXPECT_EQ(view[0], 30);
    EXPECT_EQ(view[1], 40);
    EXPECT_EQ(&view[0], &objects[2]);
    EXPECT_EQ(&view[1], &objects[3]);
}

TEST(ObjectsSubvectorViewTest, SupportsEmptySuffix)
{
    ObjectsVector<int> objects(std::vector<int>{10, 20});
    ObjectsSubvectorView<int> view(objects, objects.size());

    EXPECT_EQ(view.size(), 0U);
    EXPECT_EQ(view.offset(), objects.size());
}

TEST(ObjectsSubvectorViewTest, SupportsNestedViews)
{
    ObjectsVector<int> objects(std::vector<int>{10, 20, 30, 40});
    ObjectsSubvectorView<int> first_view(objects, 1);
    ObjectsSubvectorView<int> nested_view(first_view, 1);

    EXPECT_EQ(nested_view.size(), 2U);
    EXPECT_EQ(nested_view.offset(), 1U);
    EXPECT_EQ(nested_view[0], 30);
    EXPECT_EQ(nested_view[1], 40);
    EXPECT_EQ(&nested_view[0], &objects[2]);
}

} // namespace nastya::data_structures

namespace nastya {

TEST(ListObjectTest, UsesOwningVectorByDefault)
{
    ListObject list;
    list.addElement(std::make_unique<IntegerObject>(1));
    list.addElement(std::make_unique<IntegerObject>(2));

    EXPECT_EQ(list.getElements().size(), 2U);
    EXPECT_EQ(list.toString(), "List => [Integer => 1, Integer => 2]");
}

TEST(ListObjectTest, UsesSubvectorViewWithoutCopyingObjects)
{
    std::vector<UObjectPtr> elements;
    elements.push_back(std::make_unique<IntegerObject>(10));
    elements.push_back(std::make_unique<IntegerObject>(20));
    elements.push_back(std::make_unique<IntegerObject>(30));
    data_structures::ObjectsVector<UObjectPtr> objects(std::move(elements));
    data_structures::ObjectsSubvectorView<UObjectPtr> suffix(objects, 1);

    ListObject list(suffix);

    EXPECT_EQ(list.getElements().size(), 2U);
    EXPECT_EQ(&list.getElements()[0], &objects[1]);
    EXPECT_EQ(&list.getElements()[1], &objects[2]);
    EXPECT_EQ(list.toString(), "List => [Integer => 20, Integer => 30]");
}

} // namespace nastya
