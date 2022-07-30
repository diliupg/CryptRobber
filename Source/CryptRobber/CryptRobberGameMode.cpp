// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptRobberGameMode.h"
#include "CryptRobberCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACryptRobberGameMode::ACryptRobberGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
