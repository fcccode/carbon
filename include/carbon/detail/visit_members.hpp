#ifndef CARBON_VISIT_MEMBERS_HPP
#define CARBON_VISIT_MEMBERS_HPP

#include "traits.hpp"
#include <tuple>

namespace carbon { namespace detail {

    template<class T, class Archive, std::size_t N, std::size_t I = 0>
    struct members_visitor_t {
        static void visit(T& this_ref, Archive& archive)
        {
            constexpr auto mptr = std::get<I>(T::template carbon_type<T>::target_members);
            visit_members(this_ref.*mptr);
            members_visitor_t<T, Archive, N, I + 1>::visit(this_ref, archive);
        }
    };

    template<class T, class Archive, std::size_t N>
    struct members_visitor_t<T, Archive, N, N> {
        constexpr static void visit(T&, Archive&) noexcept {}
    };

    template<class T, class Archive>
    void visit_members(T& this_ref, Archive& archive)
    {
        if constexpr (traits::has_carbon_type<T>::value) {
            constexpr auto size =
                std::tuple_size<T::template carbon_type<T>::target_members>::value;
            members_visitor_t<T, Archive, size>::visit(this_ref, archive);
        }
        else
            archive.copy(this_);
    }
}} // namespace carbon::detail

#endif // !CARBON_VISIT_MEMBERS_HPP