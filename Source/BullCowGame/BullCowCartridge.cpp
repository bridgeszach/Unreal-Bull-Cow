// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    //PrintLine(TEXT("The Hidden Word is: %s \n It is %i characters long."), *HiddenWord, HiddenWord.Len());  // Debug Line         
}


void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{    
    if(bGameOver){
        ClearScreen();        
        SetupGame();
    }
    else // Checking player guess
    {    
        ProcessGuess(Input);      
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

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord){
        PrintLine(TEXT("Congratulations, you've guessed it!!"));
        EndGame();       
    }
    else if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());            
    }   
    else
    {
        --Attempts; // Decrement attempt counter if wrong guess.
        PrintLine(TEXT("You have %i attempts remaining."), Attempts);
        if(Attempts == 0)
        {
            PrintLine(TEXT("You are out of attempts! \nThe hidden word was: %s"), *HiddenWord);
            EndGame();
        }                        
    }        
}