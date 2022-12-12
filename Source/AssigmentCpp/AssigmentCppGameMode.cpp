// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssigmentCppGameMode.h"
#include "AssigmentCppCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "BaseTimerTarget.h"

AAssigmentCppGameMode::AAssigmentCppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom Hud class
	HUDClass = AAssigmentCppGameMode::StaticClass();

	//ensure the game mode can tick
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);


	//define varibales with numbers
	WinningNumber = 5;
	ArbitraryNumToAdd = 10.0f;
	TargetsDestroyed = 0;
	TimerTime = 5.0f;
}

void AAssigmentCppGameMode::BeginPlay() {
	Super::BeginPlay();

	//crate countdown Timer
	GetWorldTimerManager().SetTimer(Timerhandle, this, &AAssigmentCppGameMode::loseGame, TimerTime, true);
	//Get all target actors
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseTimerTarget::StaticClass(), Targets);

	for (int i = 0; i < Targets.Num(); i++) {
		ABaseTimerTarget* target = Cast<class ABaseTimerTarget>(Targets[i]);
		target->TargetDestroyed.AddDynamic(this, &AAssigmentCppGameMode::AddTime);
	}
}

void AAssigmentCppGameMode::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	if (GetWorldTimerManager().TimerExists(Timerhandle)){
		TimeReminning = FString::SanitizeFloat(GetWorldTimerManager().GetTimerRemaining(Timerhandle));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TimeReminning);
		TimerTime -= DeltaTime;

	}
}

void AAssigmentCppGameMode::AddTime() {
	TargetsDestroyed++;
	if (GetWorldTimerManager().TimerExists(Timerhandle) ){
		GetWorldTimerManager().SetTimer(Timerhandle, this,
			&AAssigmentCppGameMode::loseGame,
			GetWorldTimerManager().GetTimerRemaining(Timerhandle) + ArbitraryNumToAdd);
	}
	CheckWin();

}


void AAssigmentCppGameMode::loseGame() {
	//lose game
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You Lose!"));
};

void AAssigmentCppGameMode::CheckWin() {
	if (TargetsDestroyed > WinningNumber) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, TEXT("You Won"));
	}
}