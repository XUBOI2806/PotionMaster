// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FamiliarAttackProjectile.h"
#include "DamageTextUI.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Familiar.generated.h"

UCLASS()
class BEATEMUP_API AFamiliar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFamiliar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Mesh component for the familiar
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	// Damage dealt by the familiar's attack
	UPROPERTY(EditAnywhere)
	float AttackDamage = 20;

	// Cooldown time for the familiar's special ability
	UPROPERTY(EditAnywhere)
	float AbilityCooldown = 10;

	// Flag to check if the ability can be used
	UPROPERTY(EditAnywhere)
	bool bCanUseAbility = true;

	// Timer handle for the ability cooldown
	FTimerHandle AbilityTimerHandle;

	// Class for the damage text UI
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageTextUI> DamageTextClass;

	// Class for the attack projectile
	UPROPERTY(EditAnywhere)
	TSubclassOf<AFamiliarAttackProjectile> ProjectileClass;

	// Function to make the familiar attack enemies
	UFUNCTION()
	void AttackEnemies(FVector ProjectileDirection);

	// Function to use the special ability
	UFUNCTION()
	void UseSpecialAbility();

	// Function to reset the ability
	UFUNCTION()
	void ResetAbility();
	
};
