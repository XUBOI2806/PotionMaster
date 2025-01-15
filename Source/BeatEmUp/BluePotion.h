// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraFunctionLibrary.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BluePotion.generated.h"

UCLASS()
class BEATEMUP_API ABluePotion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABluePotion();

	// Editable projectile movement component
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* MovementComponent;

	// Editable projectile mesh for visual representation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ProjectileMesh;

	// Speed at which the projectile moves
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 500;
	
	// Movement component visible in the editor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;

	// Create area effect on impact
	void CreateAOEEffect(const FVector& ImpactPoint);

	// Handle collision events
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* SnowParticleClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
