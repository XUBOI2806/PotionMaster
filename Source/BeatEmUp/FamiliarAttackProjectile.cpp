// Fill out your copyright notice in the Description page of Project Settings.


#include "FamiliarAttackProjectile.h"

#include "Enemy.h"

// Sets default values
AFamiliarAttackProjectile::AFamiliarAttackProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up the mesh component as the root component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	// Create and set up the projectile movement component
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->bSweepCollision = true;
	MovementComponent->InitialSpeed = MovementSpeed;
	MovementComponent->UpdatedComponent = Mesh;
	MovementComponent->ProjectileGravityScale = 0;
}


// Called when the game starts or when spawned
void AFamiliarAttackProjectile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &AFamiliarAttackProjectile::OnHit);
	Mesh->SetNotifyRigidBodyCollision(true);
}

// Called every frame
void AFamiliarAttackProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFamiliarAttackProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector Normal, const FHitResult& Hit)
{
	// Check if the other actor is valid, not this actor, and not tagged as "PlayerTeam"
	if (OtherActor && OtherActor != this && !OtherActor->ActorHasTag("PlayerTeam"))
	{
		// Cast the other actor to an enemy
		AEnemy* HitEnemy = Cast<AEnemy>(OtherActor);
    
		// If the cast is successful, deal damage to the enemy and destroy this actor
		if (HitEnemy)
		{
			HitEnemy->DealDamage(Damage);
			Destroy();
		}
	}
}
