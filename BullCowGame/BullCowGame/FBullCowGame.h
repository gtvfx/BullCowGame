#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all values initialised to zero
struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame
{
public:
    FBullCowGame(); // constructor

    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus IsGuessValid(FString) const; // TODO more rich return value

    void Reset(); // TODO make a more rich return back
    

    FBullCowCount SubmitValidGuess(FString);

    


private:
    int32 MyCurrentTry;
    FString MyHiddenWord;

    //std::array<std::string, 2> threeLetterWords = {"the", "ink"};

    bool bIsGameWon;
    
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};