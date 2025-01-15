// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FamiliarAttackProjectile.generated.h"

UCLASS()
class BEATEMUP_API AFamiliarAttackProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFamiliarAttackProjectile();
	// Projectile movement component
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* MovementComponent;

	// Mesh component for the projectile
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	// Speed of the projectile
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 1000;

	// Damage dealt by the projectile
	UPROPERTY(EditAnywhere)
	float Damage = 20;

	// Function called when the projectile hits something
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector Normal, const FHitResult& Hit);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
