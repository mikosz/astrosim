#pragma once
#include <imgui.h>

namespace AstroSim
{

template <class EnumType>
TEnableIf<TIsUEnumClass<EnumType>::Value, bool> EnumCombo(EnumType& Enum, const char* Label);

// --

template <class EnumType>
TEnableIf<TIsUEnumClass<EnumType>::Value, bool> EnumCombo(EnumType& Enum, const char* Label)
{
	bool bChanged = false;

	if (ImGui::BeginCombo(Label, TCHAR_TO_ANSI(*UEnum::GetValueAsString(Enum))))
	{
		UEnum* EnumClass = StaticEnum<EnumType>();
		if (!IsValid(EnumClass))
		{
			return false;
		}

		for (int32 EnumIdx = 0; EnumIdx < EnumClass->NumEnums(); ++EnumIdx)
		{
			const auto Value = static_cast<EnumType>(EnumClass->GetValueByIndex(EnumIdx));
			if (ImGui::Selectable(TCHAR_TO_ANSI(*EnumClass->GetNameStringByIndex(EnumIdx))))
			{
				Enum = Value;
				bChanged = true;
			}

			if (Value == Enum)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	return bChanged;
}

}  // namespace AstroSim
