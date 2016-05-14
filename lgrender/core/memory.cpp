
#include "lgrender/core/memory.h"

ReferenceCounted::ReferenceCounted()
    :_ref_count(0)
{}

void ReferenceCounted::increase()
{
    _ref_count++;
}

unsigned int ReferenceCounted::release()
{
    _ref_count--;
}

template<typename T>
Reference<T>::Reference(T *p = NULL)
{
    _ptr = p;
    if (_ptr) _ptr->increase();
}


template<typename T>
Reference<T>::Reference(const Reference<T> &r)
{
    _ptr = r._ptr;
    if (_ptr) _ptr->increase();
}

template<typename T>
Reference<T>& Reference::operator=(const Reference<T> &r)
{
    if (r._ptr) r._ptr->increase();
    if (_ptr && !_ptr->release()) delete _ptr;
    _ptr = r._ptr;
    return *this;
}

template<typename T>
Reference<T>& Reference::operator=(T *p)
{
    if (p) p->increase();
    if (_ptr && !_ptr->release()) delete _ptr;
    _ptr = p;
    return *this;
}

template<typename T>
Reference<T>::~Reference()
{
    if (_ptr && !_ptr->release())
        delete _ptr;
}

template <typename T>
T* Reference::operator->()
{
    return _ptr;
}

template <typename T>
const T * Reference::operator->() const
{
    return _ptr;
}

template <typename T>
Reference::operator bool() const
{
    return _ptr != nullptr;
}

template <typename T>
const T* Reference::get() const
{
    return _ptr;
}

