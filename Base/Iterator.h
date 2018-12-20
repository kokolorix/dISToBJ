//---------------------------------------------------------------------------
#ifndef IteratorH
#define IteratorH
//---------------------------------------------------------------------------
/**
 * @brief Macro to simulate a container from a member
 * @code {.cpp}
 * class A
 * {
 *    std::vector<int> alist_;
 *    REDIRECT_STL_CONTAINER(std::vector<int> alist_);
 * };
 * @endcode
 */
#define REDIRECT_STL_CONTAINER(container_type, container) public: \
	typedef container_type::allocator_type allocator_type; \
	typedef container_type::size_type size_type; \
	typedef container_type::difference_type difference_type; \
	typedef container_type::pointer pointer; \
	typedef container_type::const_pointer const_pointer; \
	typedef container_type::reference reference; \
	typedef container_type::const_reference const_reference; \
	typedef container_type::iterator iterator; \
	typedef container_type::const_iterator const_iterator; \
	typedef container_type::reverse_iterator reverse_iterator; \
	typedef container_type::const_reverse_iterator const_reverse_iterator; \
	typedef container_type::value_type value_type; \
	inline iterator begin() {return container.begin();} \
	inline const_iterator begin() const {return container.begin();} \
	inline iterator end(){return container.end();} \
	inline const_iterator end() const {return container.end();} \
	inline reverse_iterator rbegin() {return (reverse_iterator(end()));} \
	inline const_reverse_iterator rbegin() const {return (const_reverse_iterator(end()));} \
	inline reverse_iterator rend() {return (reverse_iterator(begin()));} \
	inline const_reverse_iterator rend() const	{return (const_reverse_iterator(begin()));} \
	inline size_type size() const {return container.size();} \
	inline size_type max_size() const {return container.max_size();} \
	inline bool empty() const {return container.empty();} \
	inline iterator insert(const_iterator _where, const value_type& _val) {return container.insert(_where, _val);} \
	inline iterator insert(const_iterator _where, const value_type&& _val) {return container.insert(_where, _val);} \
	inline iterator erase(const_iterator _where) {return container.erase(_where);} \
	inline iterator erase(const_iterator _first, const_iterator _last) {return container.erase(_first, _last);} \
	inline reference front() {return *begin();} \
	inline const_reference front() const {return *begin();} \
	inline reference back() {return *rbegin();} \
	inline const_reference back() const {return *rbegin();} \
	inline void push_back(const value_type& _val) {insert(end(), _val);} \
	inline void push_back(const value_type&& _val) {insert(end(), _val);} \
/**
 * @brief class template to redirect a members container interface
 * 
 * @tparam OT the type of outer class
 * @tparam CT the type of the container
 * @tparam OT::*cnt the pointer to the member container
 */
template<typename OT, typename CT, CT OT::*cnt>
class redirect_stl_container
{
public:
	typedef typename CT::allocator_type allocator_type;
	typedef typename CT::size_type size_type;
	typedef typename CT::difference_type difference_type;
	typedef typename CT::pointer pointer;
	typedef typename CT::const_pointer const_pointer;
	typedef typename CT::reference reference;
	typedef typename CT::const_reference const_reference;
	typedef typename CT::iterator iterator;
	typedef typename CT::const_iterator const_iterator;
	typedef typename CT::reverse_iterator reverse_iterator;
	typedef typename CT::const_reverse_iterator const_reverse_iterator;
	typedef typename CT::value_type value_type;
	inline iterator begin() { return (*cnt).begin(); }
	inline const_iterator begin() const { return (*cnt).begin(); }
	inline iterator end() { return (*cnt).end(); }
	inline const_iterator end() const { return (*cnt).end(); }
	inline reverse_iterator rbegin() { return (reverse_iterator(end())); }
	inline const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
	inline reverse_iterator rend() { return (reverse_iterator(begin())); }
	inline const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }
	inline size_type size() const { return (*cnt).size(); }
	inline size_type max_size() const { return (*cnt).max_size(); }
	inline bool empty() const { return (*cnt).empty(); }
	inline iterator insert(const_iterator _where, const value_type& _val) { return (*cnt).insert(_where, _val); }
	inline iterator insert(const_iterator _where, const value_type&& _val) { return (*cnt).insert(_where, _val); }
	iterator erase(const_iterator _where) { return (*cnt).erase(_where); }
	iterator erase(const_iterator _first, const_iterator _last) { return (*cnt).erase(_first, _last); }
};

#endif
