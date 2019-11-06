// template<class T> class unique_ptr { T *dummy; operator T* () const {return dummy;} T* operator-> () const {return dummy;} T& operator* () const {return *dummy;} };
// template<class T> class shared_ptr { T *dummy; operator T* () const {return dummy;} T* operator-> () {const return dummy;} T& operator* () const {return *dummy;} };

