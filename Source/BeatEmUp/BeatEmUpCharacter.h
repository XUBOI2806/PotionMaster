// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NiagaraFunctionLibrary.h"
#include "InGameUI.h"
#include "BluePotion.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PauseMenu.h"
#include "Logging/LogMacros.h"
#include "BeatEmUpCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ABeatEmUpCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ABeatEmUpCharacter();

	UPROPERTY
	(EditAnywhere)
	float MaxHealth = 100;
	
	UPROPERTY
	(EditAnywhere)
	int CurrentHealth = MaxHealth;
	
	UPROPERTY
	(EditAnywhere)
	UInputAction* PunchAction;
	
	UPROPERTY
	(EditAnywhere)
	float PunchDistance = 250;
	
	UPROPERTY
	(EditAnywhere)
	float PunchForce = 50000;
	
	UPROPERTY
	(EditAnywhere)
	float PunchDamage = 50;
	
	UPROPERTY
	(EditAnywhere)
	float PunchCooldown = 1;
	
	bool bPunchReady = true;
    FTimerHandle PunchTimerHandle;

	// Potion Cooldown Time
	UPROPERTY
	(EditAnywhere)
	float PotionCooldown = 1;

	// Potion Time Handler
	bool bPotionReady = true;

	// Potion Time Handler
	FTimerHandle PotionTimerHandle;

	// Speed Boost Time Handler
	FTimerHandle SpeedBoostTimerHandle;

	// Reset Potion for UI
	UFUNCTION()
	void ResetPotion();
	
	UFUNCTION()
		void Punch();
	
	UFUNCTION()
		void ResetPunch();
	
	void DealDamage(float Damage);

	UPROPERTY(EditAnywhere)
		UInputAction* UseAction;

	// Action to Throw Potions
	UPROPERTY(EditAnywhere)
	UInputAction* ThrowAction;

	// Action to Drink Potions
	UPROPERTY(EditAnywhere)
	UInputAction* DrinkAction;
	
	UPROPERTY(EditAnywhere)
		float UseDistance = 1000;

	// Current Potion Amount
	UPROPERTY(EditAnywhere)
	float CurrentPotionAmount = 10;

	// Max Potion Amount
	UPROPERTY(EditAnywhere)
	float MaxPotionAmount = 10;
	
	UFUNCTION()
		void Use();

	// Function for Throwing Potions
	UFUNCTION()
		void Throw();

	// Function for Drinking Potions
	UFUNCTION()
		void Drink();

	// Function for Drinking Potions
	UFUNCTION()
		void ResetSpeedToNormal();

	// BluePotionClass Blueprint
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABluePotion> BluePotionClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UInGameUI> InGameUIClass;
	
	UPROPERTY()
		UInGameUI* InGameUI;

	UPROPERTY(EditAnywhere)
	int CurrentEXP = 0;
	
	UPROPERTY(EditAnywhere)
	int EXPToLevel = 50;
	
	UPROPERTY(EditAnywhere)
	float IncreaseMultiplier = 1.5;

	void AddEXP(int EXPToAdd);

	UPROPERTY(EditAnywhere)
	UInputAction* PauseAction;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPauseMenu> PauseMenuClass;
	
	UFUNCTION()
	 void PauseGame();
	 
	UPROPERTY(EditAnywhere)
		UNiagaraSystem* PunchEffectClass;
	
	virtual void Tick(float DeltaSeconds) override;
	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	// Speed Boost Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedBoostAmount = 500;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//Add Potion
	void AddPotion();
};

