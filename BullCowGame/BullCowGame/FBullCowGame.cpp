/*
The game logic ( no vies code or direct interaction )
the game is a simple guess the word game based on Mastermind
*/

#pragma once

#include "FBullCowGame.h"

// to make syntax Unreal compliant
#include <map>
#define TMap std::map

using int32 = int;


FBullCowGame::FBullCowGame()
{ // default constructor
    Reset();
    return;
}

int FBullCowGame::GetCurrentTry() const
{
    return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
    return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
    return bIsGameWon;
}

int FBullCowGame::GetMaxTries() const
{
    return ( MyHiddenWord.length() + 1 + ( MyHiddenWord.length() * .25 ) );
}

void FBullCowGame::Reset()
{
    // planet, artichokes, juxtaposed, pathfinder, plandrome, aftershock, quadriceps, formidable, volkswagen

    const FString HIDDEN_WORD = "artichokes";
    MyHiddenWord = HIDDEN_WORD;

    MyCurrentTry = 1;
    bIsGameWon = false;

    return;
}

EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const
{
    if (!IsIsogram(Guess)) // if the Guess is not an isogram
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}

// recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    // increment the try number
    MyCurrentTry++;

    // setup a return variable
    FBullCowCount BullCowCount;

    // loop through all letters in the hidden word
    int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

    for (int32 i = 0; i < WordLength; i++)
    {
        // compare letters against the guess
        for (int32 j = 0; j < WordLength; j++)
        {
            // if they match then
            if (Guess[j] == MyHiddenWord[i])
            {
                if (i == j) // if they're int the same place
                {
                    BullCowCount.Bulls++; // increment bulls
                }
                else // if they're not
                {
                    BullCowCount.Cows++; // increment cows 
                }
            }
        }
    }

    if (BullCowCount.Bulls == WordLength)
    {
        bIsGameWon = true;
    }
    else
    {
        bIsGameWon = false;
    }

    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    // treat 0 and 1 letter words as isograms
    if (Word.length() <= 1) { return true; }

    TMap<char, bool> LetterSeen; // setup our map
    for (auto Letter : Word) // for all letters of the word
    {
        Letter = tolower(Letter); // handle mixed case

        if (LetterSeen[Letter]) 
        {
            return false;
        }
        else
        {
            LetterSeen[Letter] = true;
        }
    }

    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    for (auto Letter : Word) 
    {
        if (!islower(Letter))
        {
            return false;
        }
    }
    return true;
}
