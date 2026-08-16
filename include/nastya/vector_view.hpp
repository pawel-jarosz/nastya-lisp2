#pragma once

#include <vector>
#include <utility>

#include <cstdint>
#include <cstddef>

namespace nastya::data_structures {

template<typename T>
class GenericObjectList {
public:
    virtual ~GenericObjectList() = default;

    virtual size_t size() const = 0;
    virtual size_t offset() const = 0;
    virtual const T& operator[](size_t index) const = 0;
};

template<typename T>
class ObjectsVector : public GenericObjectList<T> {
public:
    ObjectsVector() = default;
    explicit ObjectsVector(std::vector<T> objects) : data_(std::move(objects)) {}
    size_t size() const override { return data_.size(); }
    size_t offset() const override { return 0; }
    const T& operator[](size_t index) const override { return data_[index]; }
    void push_back(const T& object) { data_.push_back(object); }
    void push_back(T&& object) { data_.push_back(std::move(object)); }
private:
    std::vector<T> data_;
};

template<typename T>
class ObjectsSubvectorView : public GenericObjectList<T> {
public:
    ObjectsSubvectorView(const GenericObjectList<T>& object_list, size_t offset)
        : object_list_(object_list), offset_(offset), size_(object_list.size() - offset) {}

    size_t size() const override { return size_; }
    size_t offset() const override { return offset_; }
    const T& operator[](size_t index) const override { return object_list_[offset_ + index]; }

private:
    const GenericObjectList<T>& object_list_;
    size_t offset_;
    size_t size_;
};

} // namespace nastya::data_structures
