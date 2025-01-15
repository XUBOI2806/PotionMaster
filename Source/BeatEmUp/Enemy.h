// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DynamicSpotlight.h"
#include "HealthPack.h"
#include "NiagaraFunctionLibrary.h"
#include "Bullet.h"
#include "DamageTextUI.h"
#include "BeatEmUpCharacter.h"
#include "CoreMinimal.h"
#include "Trap.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class BEATEMUP_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY()
 		ABeatEmUpCharacter* Player;
	UPROPERTY(EditAnywhere)
 		float MaxHealth = 100;
	UPROPERTY(EditAnywhere)
 		float CurrentHealth = MaxHealth;

	UFUNCTION()
 		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector Normal, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float DamageToPlayer = 10;
	
	UPROPERTY(EditAnywhere)
	float RagdollTime = 5;
	
	FTimerHandle RagdollTimerHandle;
	
	void Ragdoll();
	
	UFUNCTION()
	 void StopRagdoll();

	// Function that freezes the enemy
	UFUNCTION()
		void Freeze();

	// Function that unfreezes the enemy
	UFUNCTION()
		void Unfreeze();

	UPROPERTY(EditAnywhere)
		TSubclassOf<UDamageTextUI> DamageTextClass;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABullet> BulletClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATrap> TrapClass;
	
	void Shoot(FVector Direction);

	void PlaceTrap();
	
	void FinishPlacingTrap();

	UPROPERTY(EditAnywhere)
		int EXPAmount = 20;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* DeathParticleClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Freeze Timer 
	FTimerHandle FreezeTimerHandle;
	
	// Place Trap Timer
	FTimerHandle PlaceTrapTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DealDamage(float Damage);
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AHealthPack> HealthPackClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ADynamicSpotlight> DynamicSpotlightClass;
	
	UPROPERTY()
		ADynamicSpotlight* Spotlight;

};
