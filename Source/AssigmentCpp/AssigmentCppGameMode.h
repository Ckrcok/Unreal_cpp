// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AssigmentCppGameMode.generated.h"

UCLASS(minimalapi)
class AAssigmentCppGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAssigmentCppGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Rules");
	int TargetsDestroyed;


	UPROPERTY(EditDefaultsOnly, Category = "Rules");
	int WinningNumber;

	UPROPERTY(EditDefaultsOnly, Category = "Rules");
	float TimerTime;

	UPROPERTY(EditDefaultsOnly, Category = "Rules");
	float ArbitraryNumToAdd;

	UPROPERTY(EditDefaultsOnly, Category = "Rules");
	FTimerHandle Timerhandle;

	UPROPERTY(EditDefaultsOnly, Category = "Rules");
	FString	TimeReminning;

	TArray <class AActor*> Targets;

	UFUNCTION()
		void loseGame();


	UFUNCTION()
		void AddTime();

	UFUNCTION()
		void CheckWin();

};



