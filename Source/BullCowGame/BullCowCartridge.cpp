// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();

    PrintLine(TEXT("The number of valid words is %i"), GetValidWords(Words).Num());
    //PrintLine(TEXT("The Hidden Word is: %s \n It is %i characters long."), *HiddenWord, HiddenWord.Len());  // Debug Line


   
    
             
}


void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{    
    if(bGameOver){
        ClearScreen();        
        SetupGame();
    }
    else // Checking player guess
    {    
        ProcessGuess(PlayerInput);      
    }            
}


void UBullCowCartridge::SetupGame(){
    // Welcome Player
    PrintLine(TEXT("Welcome to Bull Cows!"));

    HiddenWord = TEXT("cake");    
    Attempts = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!!"), HiddenWord.Len()); 
    PrintLine(TEXT("You have %i attempts"), Attempts);
    PrintLine(TEXT("Type in your guess and \npress enter to continue."));  // Prompt player for guess      
}


void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    // Check for Isogram
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again."));
        return;
    }

    if (Guess == HiddenWord){
        PrintLine(TEXT("Congratulations, you've guessed it!!"));
        EndGame();       
    }
    else if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %i letters long, try again!"), HiddenWord.Len());            
    }   
    else
    {
        --Attempts; // Decrement attempt counter if wrong guess.
        PrintLine(TEXT("You have %i attempts remaining."), Attempts);
        if(Attempts == 0)
        {
            ClearScreen();
            PrintLine(TEXT("You are out of attempts! \nThe hidden word was: %s"), *HiddenWord);
            EndGame();
        }                        
    }        
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{    
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }            
        }        
    }

    return true;   
}


TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
     TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
       if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
       {           
            ValidWords.Emplace(Word);                        
       }       
    }
    return ValidWords;
}

  