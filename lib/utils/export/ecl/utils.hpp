//! \file
//! \brief General the Core utilities library.
#ifndef ECL_UTILS_HPP_
#define ECL_UTILS_HPP_

#include <tuple>
#include <utility>

namespace ecl
{

//------------------------------------------------------------------------------

// Proudly taken from stackoverflow :)
// http://stackoverflow.com/questions/1198260/iterate-over-tuple

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
for_each(std::tuple<Tp...> &, FuncT)
{ }

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
for_each(std::tuple<Tp...>& t, FuncT f)
{
    f(std::get<I>(t));
    for_each<I + 1, FuncT, Tp...>(t, f);
}

//------------------------------------------------------------------------------

//! Obtains offset of the given member within given type.
template<typename T1, typename T2>
inline constexpr size_t offset_of(T1 T2::*member) {
    std::aligned_storage<sizeof(T2), alignof(T2)> object;
    T2 *ptr = reinterpret_cast<T2 *>(&object);
    return reinterpret_cast<uint8_t *>(&(ptr->*member)) - reinterpret_cast<uint8_t *>(ptr);
}

//------------------------------------------------------------------------------

//! Safe storage wrapper to avoid static initialization fiasco
//! \tparam T non-POD type to protect against implicit constructor call during static initialization
template<class T>
class safe_storage
{
public:
    //! Initializes storage.
    //! \tparam Args Types of the constructor args.
    //! \param  args T's ctor arguments.
    //! \pre  Storage not yet initialized, i.e. ctor wasn't called yet.
    //! \post Storage initialized and object is ready to work.
    //! \note Violating pre-conditions leads to undefined behaviour.
    template<class ...Args>
    static void init(Args ...args)
    {
        new (&m_stor) T{args...};
    }

    //! Gets object reference.
    //! \pre Storage initialized, i.e. init() was called once.
    static T& get()
    {
        return reinterpret_cast<T&>(m_stor);
    }

private:
    //! Storage for the T object.
    static std::aligned_storage_t<sizeof(T), alignof(T)> m_stor;
};

template<class T>
std::aligned_storage_t<sizeof(T), alignof(T)> safe_storage<T>::m_stor;

//------------------------------------------------------------------------------

//! Extracts value from enumerator element of given type.
//! \tparam Enum Enumerator type.
//! \param[in] val Value of the enumerator type.
//! \return Integer representation of the enum value.
template<typename Enum>
constexpr auto extract_value(Enum val)
{
    static_assert(std::is_enum<Enum>::value, "Given type is not enumeration.");

    return static_cast<std::underlying_type_t<Enum>>(val);
}


} // namespace ecl

#endif // ECL_UTILS_HPP_
