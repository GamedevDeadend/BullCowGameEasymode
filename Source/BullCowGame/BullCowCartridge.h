// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString &Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(const FString& Guess,  int32& Chances);
	bool IsIsogram(const FString& Word)const;
	void GettBullCows (const FString &Guess, int32 &Bulls, int32 &Cows) const;
	TArray <FString> GetValidHW(const TArray <FString>& HWord) const;

	// Your declarations go below!
private:
	int32 Lives;
	FString HiddenWord;
	bool bGameOver;
	TArray <FString> Isograms;
};
