// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!PlayerPawn) {
        UE_LOG(LogTemp, Warning, TEXT("Player tank is a null pointer"));
        return nullptr;
    }
        return Cast<ATank>(PlayerPawn);
}

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    auto PlayerTank = GetPlayerTank(); //pointer to a tank
    if(!PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller can't find a player tank"));
    } else {
        //* here is not a pointer, it's a weird syntax converting into string
        UE_LOG(LogTemp, Warning, TEXT("AI Controller found player: %s"), *(PlayerTank->GetName()));
    }
}
