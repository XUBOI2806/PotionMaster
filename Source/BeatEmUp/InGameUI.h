// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
class ABeatEmUpCharacter;
UCLASS()
class BEATEMUP_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CurrentHealthText;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* MaxHealthText;
	UPROPERTY(meta = (BindWidget))
		UProgressBar* PunchCooldown;
	//Widget for Potion Cooldown
	UPROPERTY(meta = (BindWidget))
		UProgressBar* PotionCooldown;
	//Widget for Current Potion Amount
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CurrentPotionAmountText;
	
	UPROPERTY()  
		ABeatEmUpCharacter* Player;
	
	void UpdateValues();

	UPROPERTY(meta = (BindWidget))
		UProgressBar* EXPBar;
};
