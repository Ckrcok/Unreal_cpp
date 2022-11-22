// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTimerTarget.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ABaseTimerTarget::ABaseTimerTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = Sphere;
	Sphere->InitSphereRadius(100.0f);
	Sphere->BodyInstance.SetCollisionProfileName(TEXT("WorldDynamic"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseTimerTarget::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseTimerTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseTimerTarget::OnBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	OtherActor->Destroy();
	TargetDestroyed.Broadcast();
	this->Destroy();
}