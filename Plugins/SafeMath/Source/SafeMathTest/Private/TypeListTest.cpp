#include "Misc/AutomationTest.h"
#include "SafeMath/Private/TypeList.h"

namespace SafeMath::Private
{

template <class T>
struct IsDouble
{
	static constexpr auto Value = std::is_same_v<T, double>;
};

IMPLEMENT_COMPLEX_AUTOMATION_TEST(
	TypeListTest,
	"SafeMath.Private.TypeListTest",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

void TypeListTest::GetTests(TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands) const
{
	OutBeautifiedNames.Emplace(TEXT("Add"));
	OutTestCommands.Emplace(TEXT("Add"));
	OutBeautifiedNames.Emplace(TEXT("Remove"));
	OutTestCommands.Emplace(TEXT("Remove"));
	OutBeautifiedNames.Emplace(TEXT("Find"));
	OutTestCommands.Emplace(TEXT("Find"));
}

bool TypeListTest::RunTest(const FString& Parameters)
{
	if (Parameters == TEXT("Add"))
	{
		constexpr auto IntChar = TTypeList<int, char>{};
		constexpr auto DoubleIntChar = IntChar.Add<double>();
		constexpr auto Expected = TTypeList<double, int, char>{};
		static_assert(std::is_same_v<decltype(DoubleIntChar), decltype(Expected)>);
	}
	else if (Parameters == TEXT("Filter"))
	{
		constexpr auto DoubleIntChar = TTypeList<double, int, char>{};
		constexpr auto IntChar = DoubleIntChar.Filter<IsDouble>();
		constexpr auto Expected = TTypeList<int, char>{};
		static_assert(std::is_same_v<decltype(IntChar), decltype(Expected)>);
	}
	else if (Parameters == TEXT("Find"))
	{
		{
			constexpr auto DoubleIntChar = TTypeList<double, int, char>{};
			constexpr auto Double = DoubleIntChar.Find<IsDouble>();
			constexpr auto Expected = 1.23;
			static_assert(std::is_same_v<decltype(Double), decltype(Expected)>);
		}
		{
			constexpr auto FloatIntChar = TTypeList<float, int, char>{};
			constexpr auto Nil = FloatIntChar.Find<IsDouble>();
			constexpr auto Expected = TTypeListNil{};
			static_assert(std::is_same_v<decltype(Nil), decltype(Expected)>);
		}
	}

	return true;
}

}  // namespace SafeMath::Private
