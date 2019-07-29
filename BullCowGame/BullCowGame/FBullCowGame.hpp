
/*  FBullCowGame.hpp
    Simple guess the word game in terminal, only game logic
    Syntax comes from Unreal coding standards
    https://docs.unrealengine.com/en-US/Programming/Development/CodingStandard/index.html
    Created by @faulty_agatha on 24.07.19.
    based on https://github.com/UnrealCourse
*/

#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <iostream>

//unreal-friendly syntax
using FString = std::string;
using int32 = int;

struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    Invalid_Status,
    Ok,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame(); //constructor
    
    //const getters
    int GetMaxTries() const;
    int GetCurrentTry() const;
    int GetHiddenWordLength() const;
    
    EGuessStatus CheckGuessValidity(FString Guess);
    bool IsGameWon() const;
    
    void Reset();
    
    FBullCowCount SubmitValidGuess(FString PlayerWord); //counts bulls and cows and increases try
    
private:
    int32 MaxTries;
    int32 CurrentTry;
    FString HiddenWord;
    bool bIsGameWon;
    
    bool IsIsogram(FString PlayerWord) const;
    bool IsLowerCase(FString PlayerWord) const;
};


#endif /* FBullCowGame_hpp */
