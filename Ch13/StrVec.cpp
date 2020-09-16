#include <string>
#include <utility>

#include "StrVec.h"

using namespace std;

void StrVec::push_back(const string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

pair<string *, string *>
StrVec::alloc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if (elements)
    {
        for (auto p = first_free; p != elements;)
            alloc.destory(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &s)
{
    auto new_data = alloc_n_copy(s.begin, s.end);
    elements = new_data.first;
    first_free = cap = new_data.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto new_data = alloc_n_copy(rhs.begin, rhs.end);
    free();
    elements = new_data.first;
    first_free = cap = new_data.second;
    return *this;
}

void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i !=size(); ++i)
        alloc.construct(dest++, std::move(*element++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

