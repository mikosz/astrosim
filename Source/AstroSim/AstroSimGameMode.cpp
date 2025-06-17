// Copyright 2025 Mikołaj Radwan, All Rights Reserved.

#include "AstroSimGameMode.h"

#include "AstroSimCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAstroSimGameMode::AAstroSimGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
