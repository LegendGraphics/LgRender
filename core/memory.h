
#ifndef LGRENDER_CORE_MEMORY_H
#define LGRENDER_CORE_MEMORY_H


class ReferenceCounted 
{
public:
    ReferenceCounted();
    void increase();
    unsigned int release();
private:
    unsigned int _ref_count;

private:
    ReferenceCounted(const ReferenceCounted &);
    ReferenceCounted &operator=(const ReferenceCounted &);
};


template <typename T> 
class Reference 
{
public:
    Reference(T *p = NULL);
    Reference(const Reference<T> &r);
    Reference& operator=(const Reference<T> &r);
    Reference& operator=(T *p);
    ~Reference();

    T *operator->();
    const T *operator->() const;
    operator bool() const;
    const T *get() const;
private:
    T*  _ptr;
};


#endif // LGRENDER_CORE_MEMORY_H
