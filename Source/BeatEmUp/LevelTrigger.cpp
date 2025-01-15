// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTrigger.h"

// Sets default values
ALevelTrigger::ALevelTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	RootComponent = TriggerVolume;

}

// Called when the game starts or when spawned
void ALevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ALevelTrigger::StartLevelStreaming);
	
}

void ALevelTrigger::StartLevelStreaming(UPrimitiveComponent* HitComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bSweep, const FHitResult& Hit)
{
	if(Cast<ABeatEmUpCharacter>(OtherActor))
	{
		if(bLoadLevel)
		{
			UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, FLatentActionInfo());
		}
		else
		{
			UGameplayStatics::UnloadStreamLevel(GetWorld(), LevelToLoad, FLatentActionInfo(), true);
		}
	}
}

