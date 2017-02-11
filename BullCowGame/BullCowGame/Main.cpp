/*
This is the console executeable that makes use of the BullCow class
This acts as the view in an MVC pattern, and is repsonsible for all 
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"


// to make syntax Unreal compliant
using FText = std::string;
using int32 = int;


// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void RepeatGuess(FText Guess);
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

//using namespace std;


// the entry point for our application
int main()
{
    bool bPlayAgain = false;

    do
    {
        PrintIntro();
        PlayGame();
        // TODO add a game summary
        bPlayAgain = AskToPlayAgain();
    } 
    while (bPlayAgain);
    
    return 0;
}

void PrintIntro()
{
    // introduce the game
    std::cout << std::endl;
    std::cout << "*******************************************************************" << std::endl;
    std::cout << "**                                                               **" << std::endl;
    std::cout << "**       (____)                                       ^__^       **" << std::endl;
    std::cout << "**        (**)        WELCOME TO BULLS AND COWS       (OO)       **" << std::endl;
    std::cout << "**         ()              a fun word game            (__)       **" << std::endl;
    std::cout << "**                                                               **" << std::endl;
    std::cout << "**                                                               **" << std::endl;
    std::cout << "*******************************************************************" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "*******************************************************************" << std::endl;
    std::cout << "**                                                               **" << std::endl;
    std::cout << "**      Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?      **\n";
    std::cout << "**                                                               **" << std::endl;
    std::cout << "*******************************************************************" << std::endl;
    std::cout << std::endl;
    return;
}

// plays a singe game to completion
void PlayGame()
{
    BCGame.Reset();

    int32 MaxTries = BCGame.GetMaxTries();

    // Loop asking for guesses while the game is NOT won
    // and there are tries remaining
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();

        // submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }

    PrintGameSummary();

    return;
}

// Loop continually until the user gives a valid guess
FText GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;

    FText Guess = "";

    do
    {
        // get a guess from the player
        int32 CurrentTry = BCGame.GetCurrentTry();

        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, Guess);

        // Check status and give feedback
        Status = BCGame.IsGuessValid(Guess);

        switch (Status)
        {
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters.\n\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter all lowercase letters.\n\n";
            break;
        default:
            RepeatGuess(Guess);
            break;
        }
    } while (Status != EGuessStatus::OK); // keep looping until we get a valid input

    return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same word (y/n)? ";
    FText Response = "";
    std::getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void RepeatGuess(FText Guess)
{
    // repeat the guess back to the player
    std::cout << "Your guess was " << Guess << std::endl;

    std::cout << std::endl;

    return;
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n";
    }
    else
    {
        std::cout << "Better luck next time!\n";
    }
}
