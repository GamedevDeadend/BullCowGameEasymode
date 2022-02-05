// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWord.h"
#include <iostream>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    GetValidHW( HiddenWordLst);
    Isograms = GetValidHW( HiddenWordLst);

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString &PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }

    else // Checking player guess
    {
        ProcessGuess(PlayerInput, Lives);
    }
}

void UBullCowCartridge ::SetupGame()
{
    int32 difficulty;
    PrintLine(TEXT("The Hidden Word was: %s "), *HiddenWord); // DEBUG PURPOSE ONLY
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Select difficlutly level between 1 to 4."));
    PrintLine(TEXT("**Important Rules and instructions**"));
    PrintLine(TEXT("Press tab key to type in terminal"));
    PrintLine(TEXT("For each guess you will get bulls and cows"));
    PrintLine(TEXT("*Make sure you don't run out of chances\n"));


    HiddenWord = Isograms [FMath :: RandRange( 0, Isograms.Num() - 1 )];
    Lives = HiddenWord.Len()*3;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i length word"), HiddenWord.Len());
    // PrintLine(FString ::Printf(TEXT("The Hidden Word is *%s*."), *HiddenWord)); // DEBUG PURPOSE ONLY
    PrintLine(TEXT("You have %i lives to Guess the word"), Lives);
    PrintLine(TEXT("Type your Guess.\nPress enter to continue"));
}

void UBullCowCartridge ::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again!"));
}

void UBullCowCartridge ::ProcessGuess( const FString& Guess,  int32& Chances)
{
    if (Guess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("You have Won :)"));
        PrintLine(TEXT("The Hidden Word is %s"), *HiddenWord);
        EndGame();
        return;
    }

    

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("You have entered wrong length guess.\nHidden word is %i characters long"), HiddenWord.Len());
        PrintLine(TEXT("\nYou have %i Lives left"), Chances);
        return;
    }

    if (!IsIsogram(Guess)) // Check If Isogram
    {
        PrintLine(TEXT("No repeating letters allowed, Guess again."));
        return;
    }

    PrintLine(TEXT("You have lost a life."));
    --Chances;

    if (Chances <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("\nYou have no lives left!"));
        PrintLine(TEXT("The Hidden Word was: %s "), *HiddenWord);
        PrintLine(TEXT("BetterLuck next time :("));
        EndGame();
        return;
    }

    int32 Bulls,Cows;
    GettBullCows(Guess , Bulls , Cows);
    PrintLine(TEXT("You have %i bulls and %i cows."),Bulls,Cows);// Show bulls and cows
    PrintLine(TEXT("You have %i lives left\n"),Chances);

}

bool UBullCowCartridge ::IsIsogram(const FString& Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 j = i + 1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])
                return false;
        }
    }

    return true;
}

TArray <FString> UBullCowCartridge :: GetValidHW (const TArray <FString>& HWord) const
{
    TArray <FString> ValidWords;
    
    for (FString LVWord : HiddenWordLst) 
    {
        if (( LVWord.Len() >= 4 ) && IsIsogram( LVWord ))
            {
                ValidWords.Emplace(LVWord);
            }

    }
    return ValidWords;
    
}

void UBullCowCartridge :: GettBullCows ( const FString& Guess,int32& BullCount, int32 &CowCount ) const
{
    BullCount = 0;
    CowCount = 0;
    for (int32 i = 0; i < HiddenWord.Len(); i++)
    {
        if(Guess[i] == HiddenWord[i])
            {
                BullCount++;
                PrintLine(TEXT("'%c' is bull"),Guess[i]);
                continue;
            }    

        else
            {
                for (int32 j = 0; j < HiddenWord.Len(); j++)
                {
                    if (Guess[i] == HiddenWord[j])

                        {   CowCount++;
                            PrintLine(TEXT("'%c' is cow"),Guess[i]);    
                            break;
                        }
                }
                
            }
    }
    
}
