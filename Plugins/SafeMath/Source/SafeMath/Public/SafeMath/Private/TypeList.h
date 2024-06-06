#pragma once

namespace SafeMath::Private
{

class TTypeListNil
{
};

template <class T>
constexpr bool IsTypeListNil(T)
{
	return false;
}

constexpr bool IsTypeListNil(TTypeListNil)
{
	return true;
}

template <class... T>
class TTypeList
{
public:
	template <class ElementType>
	constexpr auto Add() const
	{
		return TTypeList<ElementType, T...>{};
	}

	template <template <class> class PredicateType>
	constexpr auto Find() const
	{
		return FindImpl<PredicateType, T...>();
	}

	template <template <class> class PredicateType>
	constexpr auto Filter() const
	{
		return FilterImpl<PredicateType, T...>();
	}

private:
	template <template <class> class PredicateType, class HeadType, class... TailTypes>
	static auto FindImpl()
	{
		if constexpr (PredicateType<HeadType>::Value)
		{
			return HeadType{};
		}
		else
		{
			return FindImpl<PredicateType, TailTypes>();
		}
	}

	template <template <class> class PredicateType>
	static auto FindImpl()
	{
		return TTypeListNil{};
	}

	template <template <class> class PredicateType, class HeadType, class... TailTypes>
	static auto FilterImpl()
	{
		constexpr auto FilteredTail = FilterImpl<PredicateType, TailTypes...>();
		if constexpr (!PredicateType<HeadType>::Value)
		{
			return FilteredTail.Add(HeadType{});
		}
		else
		{
			return FilteredTail;
		}
	}

	template <template <class> class PredicateType>
	static auto FilterImpl()
	{
		return TTypeList{};
	}
};

}  // namespace SafeMath::Private
