#include <vector>
#include <utility>

// A container that can be constructed with rvalue-references to its elements.
// All objects will be moved instead of copied like when using initializer lists.
template<typename T>
class Group
{
public:
    Group(T&& element)
    {
        v.push_back(std::move(element));
    }

    template<typename ... T2>
    Group(T&& element, T2&&... rest)
        : Group(std::forward<T2>(rest)...)
    {
        v.push_back(std::move(element));
    }

    ~Group() {}

    typename std::vector<T>::const_reverse_iterator begin() const
    {
        return v.crbegin();
    }
    typename std::vector<T>::const_reverse_iterator end() const
    {
        return v.crend();
    }

private:
    std::vector<T> v;
};
