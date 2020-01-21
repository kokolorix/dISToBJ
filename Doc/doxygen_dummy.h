
namespace std
{
    template<class T>
    class shared_ptr {T* operator->()const{return nullptr;}};
}

namespace srdev
{
    class PropertyPtr { public: Property *operator->() const { return nullptr; } };
}