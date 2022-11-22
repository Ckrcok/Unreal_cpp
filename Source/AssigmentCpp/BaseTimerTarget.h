// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTimerTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetDestroyed);

UCLASS()
class ASSIGMENTCPP_API ABaseTimerTarget : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseTimerTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	class USphereComponent* Sphere;

	UFUNCTION()
			void OnBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers");
	FTargetDestroyed TargetDestroyed;
};
