// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DODGEBALL_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	//Dodgeball 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SightSource;
public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	//Looks at player 
	bool LookAtActor(AActor* targetActor);
	//Check if the enemy can see the player
	bool CanSeeActor(const AActor* targetActor) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Throw dodgeball


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

};
