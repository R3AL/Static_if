#pragma once

#include <type_traits>

namespace si
{
	namespace internal
	{
		/*
			Perhaps a name change..
		*/
		struct _
		{
			template <typename T>
			T&& operator()(T&& value) const
			{
				return value;
			}
		};

		template <bool, typename TrueFunctor>
		struct static_if_internal;

		template <typename TrueFunctor>
		struct static_if_internal < true, TrueFunctor >
		{
			static_if_internal(TrueFunctor trueFunctor) :
				m_true(trueFunctor)
			{

			}

			template <typename FalseFunctor>
			void Else(FalseFunctor)
			{
				m_true(_());
			}

			template <bool Condition, typename Unused>
			auto Else_if(Unused)
			{
				return static_if_internal<true, TrueFunctor>(m_true);
			}

			TrueFunctor m_true;
		};

		template <typename TrueFunctor>
		struct static_if_internal < false, TrueFunctor >
		{
			static_if_internal(TrueFunctor)
			{

			}

			template <typename FalseFunctor>
			void Else(FalseFunctor falseFunctor)
			{
				falseFunctor(_());
			}

			template <bool Condition, typename ElseIfTrueFunctor>
			auto Else_if(ElseIfTrueFunctor elseIfTrueFunctor)
			{
				return static_if_internal<Condition, ElseIfTrueFunctor>(elseIfTrueFunctor);
			}
		};
	}

	template <bool Condition, typename TrueFunctor>
	auto Static_If(TrueFunctor trueFunctor)
	{
		return internal::static_if_internal<Condition, TrueFunctor>(trueFunctor);
	}
}
