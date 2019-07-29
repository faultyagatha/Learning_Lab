/*  FBullCowGame.hpp
 Simple guess the word game in terminal, only game logic
 Syntax comes from Unreal coding standards
 https://docs.unrealengine.com/en-US/Programming/Development/CodingStandard/index.html
 Created by @faulty_agatha on 24.07.19.
 based on https://github.com/UnrealCourse
 */

#pragma once
#include <iostream>
#include "FBullCowGame.hpp"

//unreal-friendly syntax
using FText = std::string;
using int32 = int;

FBullCowGame BCGame; //instantiate a new reusable across the points game

void GameIntro() {
    std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << "-letter isogram I'm thinking of?\n";
    return;
}

FText GetValidGuess() {
    EGuessStatus Status = EGuessStatus::Invalid_Status; // a good practice to initialise to invalid or false
    FText Guess = "";
    do {
    int32 CurrentTry = BCGame.GetCurrentTry();
    
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
    
    getline(std::cin, Guess);
    Status = BCGame.CheckGuessValidity(Guess);
    switch (Status) { //check the input validity
        case EGuessStatus::Not_Isogram:
            std::cout << "The word you entered is not an isogram. Try again.\n\n";
            break;
        case EGuessStatus::Wrong_Length:
            std::cout << "Wrong word length. Please enter the "<<
            BCGame.GetHiddenWordLength() << "-letter isogram.\n\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please use lowercase letters.\n\n";
            break;
        default: EGuessStatus::Ok;
            break;
        }
    } while(Status != EGuessStatus::Ok);
    return Guess;
}

void PrintGameSummary() {
    if(BCGame.IsGameWon()) std::cout << "You won!\n\n";
    else std::cout << "You lost!\n\n";
    return;
}

void PlayGame() {
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    // loop asking for guesses while the game
    // is not won and there are tries left
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() < MaxTries) {
        FText Guess = GetValidGuess();
        //submit valid guess and receive counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        //print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
        std::cout << "Cows = " << BullCowCount.Cows << std::endl;
    }
    PrintGameSummary();
    return;
}

bool IsPlayAgain() {
    std::cout << "Do you want to play again with the same word? (Y for Yes) \n";
    FText Response = "";
    getline(std::cin, Response);
    bool bResponse = false;
    if((Response[0] == 'y') || (Response[0] == 'Y')) { bResponse = true; }
    return bResponse;
}

int main() {
    bool bPlayAgain = false;
    do {
        GameIntro();
        PlayGame();
        bPlayAgain = IsPlayAgain();
    }
    while (bPlayAgain);
    std::cout << "See you around!\n";
    return 0; //exit the game
}
