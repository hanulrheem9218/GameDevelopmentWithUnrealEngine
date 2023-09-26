// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
// GetWorld axis
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("Sight Source"));
	SightSource->SetupAttachment(RootComponent);
	SightSource->SetWorldLocation(FVector(10,0,80));
}

bool AEnemyCharacter::LookAtActor(AActor* targetActor)
{
	if (targetActor == nullptr) return false;
	if (CanSeeActor(targetActor)) {
	FVector start = GetActorLocation();
	FVector end = targetActor->GetActorLocation();
	// start to end rotation calculation
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(start, end);
	// rotate to calculated rotation
	SetActorRotation(lookAtRotation);
	return true;
	}
	return false;
}

bool AEnemyCharacter::CanSeeActor(const AActor* targetActor) const
{
	if (targetActor == nullptr) {

	return false;
	}
	//line trace result
	FHitResult hit;
	//Line trace start to end
	FVector start = SightSource->GetComponentLocation();
	FVector end = targetActor->GetActorLocation();
	//evaluating the distinguishable trace channel.
	//ECollisionChannel channel = ECollisionChannel::ECC_Visibility;
	ECollisionChannel channel = ECollisionChannel::ECC_GameTraceChannel1;
	//execute line trace
//	GetWorld()->LineTraceSingleByChannel(hit, start, end, channel);

	FCollisionQueryParams QueryParams;
	//this method will ingore this agent
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(targetActor);
	//execute line trace
	//show the line trace

	//sweep trace
	FQuat rotation = FQuat::Identity;
	//a object that used for sweep trace
	FCollisionShape shape = FCollisionShape::MakeBox(FVector(20.0f, 20.0f, 20.0f));
	GetWorld()->LineTraceSingleByChannel(hit, start, end, channel, QueryParams);
	//GetWorld()->SweepSingleByChannel(hit, start, end, rotation, channel, shape);
	DrawDebugLine(GetWorld(), start, end, FColor::Red);

	return !hit.bBlockingHit;
}



// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//acquire controllable character
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	// check if the enemy is allowed to see from current frame
	LookAtActor(PlayerCharacter);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

