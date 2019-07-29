/*  FBullCowGame.hpp
 Simple guess the word game in terminal, only game logic
 Syntax comes from Unreal coding standards
 https://docs.unrealengine.com/en-US/Programming/Development/CodingStandard/index.html
 Created by @faulty_agatha on 24.07.19.
 based on https://github.com/UnrealCourse
 */

#pragma once
#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame()
    : MaxTries{8}, CurrentTry{1} {
        Reset();
}

//getters
int FBullCowGame::GetMaxTries() const { return MaxTries; }
int FBullCowGame::GetCurrentTry() const { return CurrentTry; }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }
int FBullCowGame::GetHiddenWordLength() const { return static_cast<int>(HiddenWord.length()); }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) {
    if(!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }
    else if(!IsLowerCase(Guess)) { return EGuessStatus::Not_Lowercase; }
    else if(Guess.length() != GetHiddenWordLength()) { return EGuessStatus::Wrong_Length; }
    else { return EGuessStatus::Ok; }
}

void FBullCowGame::Reset() {
    constexpr int32 MAX_TRIES = 8;
    MaxTries = MAX_TRIES;
    
    const FString HIDDEN_WORD = "playground";
    HiddenWord = HIDDEN_WORD;
    bIsGameWon = false;
    return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString PlayerWord) {
    CurrentTry++; //increment the turn number
    FBullCowCount BullCowCount; //setup a return variable of type struct
    for(int32 i = 0; i < HiddenWord.length(); i++) { //loop through all letters in the guess
        for(int32 j = 0; j < PlayerWord.length(); j++) {
            //compare letters against a hidden word
            //if they match:
            if(PlayerWord[j] == HiddenWord[i]) {
                if(j == i) BullCowCount.Bulls++; //increment bulls if they are in the same place
                else BullCowCount.Cows++; //increment cows if they are not
            }
        }
    }
    if(BullCowCount.Bulls == GetHiddenWordLength()) bIsGameWon = true;
    else bIsGameWon = false;
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString PlayerWord) const {
    //treat 1- and 0-letter word as isogram
    if(PlayerWord.length() <= 1) return true;
    TMap<char, bool> LetterSeen; //setup our map
    for(auto Letter : PlayerWord) { //loop through the letters
        Letter = tolower(Letter); //all upper- and lowercase letters
        //if the letter is in the map
        if(LetterSeen[Letter]) return false;
        else LetterSeen[Letter] = true;
        }
    return true;
}

bool FBullCowGame::IsLowerCase(FString PlayerWord) const {
    for(auto Letter : PlayerWord) {
        if(!islower(Letter)) return false;
    }
    return true;
}


