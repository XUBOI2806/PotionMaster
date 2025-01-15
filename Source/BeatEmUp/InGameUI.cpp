// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "BeatEmUpCharacter.h"

void UInGameUI::UpdateValues()
{
	HealthBar->SetPercent((float)Player->CurrentHealth / Player->MaxHealth);
	CurrentHealthText->SetText(FText::FromString(FString::FromInt(Player->CurrentHealth)));
	float PunchTimePercentage = 0;
	if (GetWorld()->GetTimerManager().TimerExists(Player->PunchTimerHandle))
	{
		PunchTimePercentage = GetWorld()->GetTimerManager().GetTimerRemaining(Player->PunchTimerHandle) / Player->
			PunchCooldown;
	}
	float ThrowTimePercentage = 0;
	
	// Updating the Cooldown Display for InGame UI
	if (GetWorld()->GetTimerManager().TimerExists(Player->PotionTimerHandle))
	{
		ThrowTimePercentage = GetWorld()->GetTimerManager().GetTimerRemaining(Player->PotionTimerHandle) / Player->
			PotionCooldown;
	}
	
	PunchCooldown->SetPercent(1 - PunchTimePercentage);
	PotionCooldown->SetPercent(1 - ThrowTimePercentage);
	
	//Updating Potion Amount for InGame UI
	CurrentPotionAmountText->SetText(FText::FromString(FString::FromInt(Player->CurrentPotionAmount)));

	MaxHealthText->SetText(FText::FromString(FString::SanitizeFloat(Player->MaxHealth)));

	EXPBar->SetPercent((float)Player->CurrentEXP / Player->EXPToLevel);
}
