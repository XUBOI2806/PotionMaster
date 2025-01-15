// Fill out your copyright notice in the Description page of Project Settings.


#include "Familiar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

#include "BrainComponent.h"
#include "FamiliarController.h"

// Sets default values
AFamiliar::AFamiliar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AFamiliar::BeginPlay()
{
	Super::BeginPlay();

	// Tag for Allies
	Tags.Add(FName("PlayerTeam"));

	// Orient the character to its movement direction
	GetCharacterMovement()->bOrientRotationToMovement = true; 
}

// Called every frame
void AFamiliar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFamiliar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Method to make the familiar attack enemies in the given direction
void AFamiliar::AttackEnemies(FVector ProjectileDirection)
{
	// Calculate spawn location and rotation, then spawn and launch the projectile
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 200;
	FRotator SpawnRotation = ProjectileDirection.Rotation();
	AFamiliarAttackProjectile* Projectile = Cast<AFamiliarAttackProjectile>(GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation));
	ProjectileDirection.Normalize();
	Projectile->MovementComponent->Velocity = ProjectileDirection * Projectile->MovementSpeed;
}

//Method for using a special ability
void AFamiliar::UseSpecialAbility()
{
	
}

// Method for resetting the special ability
void AFamiliar::ResetAbility()
{
	
}

