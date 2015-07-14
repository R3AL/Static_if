#pragma once

#include <type_traits>
#include <functional>

namespace si
{
	namespace internal
	{
		struct Ident
		{
			template <typename T>
			T&& operator()(T&& value) const
			{
				return value;
			}
		};

		template <bool Condition>
		struct static_if_internal;

		template <>
		struct static_if_internal<true>
		{
			template <typename TrueFunctor>
			constexpr auto& Then(TrueFunctor trueFunctor) const
			{
				trueFunctor( Ident{} );
				
				return *this;
			}

			template <typename Unused>
			constexpr auto& Else(Unused) const
			{
				return *this;
			}

			template <typename Unused>
			constexpr auto& Else_if(bool, Unused) const
			{
				return *this;
			}
		};

		template <>
		struct static_if_internal<false>
		{
			template <typename Unused>
			constexpr auto& Then(Unused) const
			{
				return *this;
			}

			template <typename ElseIfFunctor>
			constexpr auto& Else_if(bool condition, ElseIfFunctor elseIfFunctor) const
			{
				if(condition)
				{
					m_func = elseIfFunctor;
				}

				return *this;
			}

			template <typename FalseFunctor>
			constexpr auto& Else(FalseFunctor falseFunctor) const
			{
				if( m_func != nullptr )
				{
					m_func( Ident{} );
				}
				else
				{
					falseFunctor( Ident{} );
				}

				return *this;
			}

			mutable std::function<void(Ident)> m_func;
		};
	}

	template <bool Condition, typename TrueFunctor>
	constexpr auto Static_If(TrueFunctor trueFunctor)
	{
		auto sIf = internal::static_if_internal<Condition>{};
		sIf.Then(trueFunctor);
		
		return sIf;
	}
}

namespace stdx
{
	template <typename T>
	constexpr bool is_void_v = std::is_void<T>::value;

	template <typename T>
	constexpr bool is_null_pointer_v = std::is_null_pointer<T>::value;

	template <typename T>
	constexpr bool is_integral_v = std::is_integral<T>::value;

	template <typename T>
	constexpr bool is_floating_point_v = std::is_floating_point<T>::value;

	template <typename T>
	constexpr bool is_array_v = std::is_array<T>::value;

	template <typename T>
	constexpr bool is_enum_v = std::is_enum<T>::value;

	template <typename T>
	constexpr bool is_union_v = std::is_union<T>::value;

	template <typename T>
	constexpr bool is_class_v = std::is_class<T>::value;

	template <typename T>
	constexpr bool is_function_v = std::is_function<T>::value;

	template <typename T>
	constexpr bool is_pointer_v = std::is_pointer<T>::value;

	template <typename T>
	constexpr bool is_lvalue_reference_v = std::is_lvalue_reference<T>::value;

	template <typename T>
	constexpr bool is_rvalue_reference_v = std::is_rvalue_reference<T>::value;

	template <typename T>
	constexpr bool is_member_object_pointer_v = std::is_member_object_pointer<T>::value;

	template <typename T>
	constexpr bool is_member_function_pointer_v = std::is_member_function_pointer<T>::value;

	template <typename T>
	constexpr bool is_fundamental_v = std::is_fundamental<T>::value;

	template <typename T>
	constexpr bool is_arithmetic_v = std::is_arithmetic<T>::value;

	template <typename T>
	constexpr bool is_scalar_v = std::is_scalar<T>::value;

	template <typename T>
	constexpr bool is_object_v = std::is_object<T>::value;

	template <typename T>
	constexpr bool is_compound_v = std::is_compound<T>::value;

	template <typename T>
	constexpr bool is_reference_v = std::is_reference<T>::value;

	template <typename T>
	constexpr bool is_member_pointer_v = std::is_member_pointer<T>::value;

	template <typename T>
	constexpr bool is_const_v = std::is_const<T>::value;

	template <typename T>
	constexpr bool is_volatile_v = std::is_volatile<T>::value;

	template <typename T>
	constexpr bool is_trivial_v = std::is_trivial<T>::value;

	template <typename T>
	constexpr bool is_trivially_copyable_v = std::is_trivially_copyable<T>::value;

	template <typename T>
	constexpr bool is_standard_layout_v = std::is_standard_layout<T>::value;

	template <typename T>
	constexpr bool is_pod_v = std::is_pod<T>::value;

	template <typename T>
	constexpr bool is_literal_type_v = std::is_literal_type<T>::value;

	template <typename T>
	constexpr bool is_empty_v = std::is_empty<T>::value;

	template <typename T>
	constexpr bool is_polymorphic_v = std::is_polymorphic<T>::value;

	template <typename T>
	constexpr bool is_final_v = std::is_final<T>::value;

	template <typename T>
	constexpr bool is_abstract_v = std::is_abstract<T>::value;

	template <typename T>
	constexpr bool is_signed_v = std::is_signed<T>::value;

	template <typename T>
	constexpr bool is_unsigned_v = std::is_unsigned<T>::value;

	template <typename T>
	constexpr bool is_constructible_v = std::is_constructible<T>::value;

	template <typename T>
	constexpr bool is_trivially_constructible_v = std::is_trivially_constructible<T>::value;

	template <typename T>
	constexpr bool is_nothrow_constructible_v = std::is_nothrow_constructible<T>::value;

	template <typename T>
	constexpr bool is_default_constructible_v = std::is_default_constructible<T>::value;

	template <typename T>
	constexpr bool is_trivially_default_constructible_v = std::is_trivially_default_constructible<T>::value;

	template <typename T>
	constexpr bool is_nothrow_default_constructible_v = std::is_nothrow_default_constructible<T>::value;

	template <typename T>
	constexpr bool is_copy_constructible_v = std::is_copy_constructible<T>::value;

	template <typename T>
	constexpr bool is_trivially_copy_constructible_v = std::is_trivially_copy_constructible<T>::value;

	template <typename T>
	constexpr bool is_nothrow_copy_constructible_v = std::is_nothrow_copy_constructible<T>::value;

	template <typename T>
	constexpr bool is_move_constructible_v = std::is_move_constructible<T>::value;

	template <typename T>
	constexpr bool is_trivially_move_constructible_v = std::is_trivially_move_constructible<T>::value;

	template <typename T>
	constexpr bool is_nothrow_move_constructible_v = std::is_nothrow_move_constructible<T>::value;

	template <typename T1, typename T2>
	constexpr bool is_assignable_v = std::is_assignable<T1, T2>::value;

	template <typename T1, typename T2>
	constexpr bool is_trivially_assignable_v = std::is_trivially_assignable<T1, T2>::value;

	template <typename T1, typename T2>
	constexpr bool is_nothrow_assignable_v = std::is_nothrow_assignable<T1, T2>::value;

	template <typename T>
	constexpr bool is_copy_assignable_v = std::is_copy_assignable<T>::value;

	template <typename T>
	constexpr bool is_trivially_copy_assignable_v = std::is_trivially_copy_assignable<T>::value;

	template <typename T>
	constexpr bool is_nothrow_copy_assignable_v = std::is_nothrow_copy_assignable<T>::value;

	template <typename T>
	constexpr bool is_move_assignable_v = std::is_move_assignable<T>::value;

	template <typename T>
	constexpr bool is_trivially_move_assignable_v = std::is_trivially_move_assignable<T>::value;

	template <typename T>
	constexpr bool is_nothrow_move_assignable_v = std::is_nothrow_move_assignable<T>::value;

	template <typename T>
	constexpr bool is_destructible_v = std::is_destructible<T>::value;

	template <typename T>
	constexpr bool is_trivially_destructible_v = std::is_trivially_destructible<T>::value;

	template <typename T>
	constexpr bool is_nothrow_destructible_v = std::is_nothrow_destructible<T>::value;

	template <typename T1, typename T2>
	constexpr bool is_base_of_v = std::is_base_of<T1, T2>::value;

	template <typename T1, typename T2>
	constexpr bool is_same_v = std::is_same<T1, T2>::value;

	template <typename T1, typename T2>
	constexpr bool is_convertible_v = std::is_convertible<T1, T2>::value;

	template <typename T>
	constexpr bool has_virtual_destructor_v = std::has_virtual_destructor<T>::value;
}
