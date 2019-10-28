// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController() {
    CrosshairXLocation = 0.5;
    CrosshairYLocation = 0.3333;
}

ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
    UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking"));
}

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank(); //pointer to a tank
    if(!ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller doesn't posses a tank"));
    } else {
        //* here is not a pointer, it's a weird syntax converting into string
    UE_LOG(LogTemp, Warning, TEXT("Player Controller posessing: %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::AimTowardsCrosshair() {
    if(!GetControlledTank()) { return; } //make sure you have something to aim at
    FVector HitLocation; //OUT parameter
    if(GetSightRayHitLocation(HitLocation)) {
        //line trace
//        UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
        //TODO: tell controlled tank to aim at this point
    }
}

//get world location of linetrace through crosshair, true if hits something
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
    //find the crosshair position in pixel coordinates
    int32 ViewportSizeX;
    int32 ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation,
                                    ViewportSizeY * CrosshairYLocation);
    UE_LOG(LogTemp, Warning, TEXT("Screen location: %s"), *ScreenLocation.ToString());
    
    //de-project the screen position of the crosshair to the world direction
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection)) {
        UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
    }
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(
                                   ScreenLocation.X, ScreenLocation.Y,
                                   CameraWorldLocation, LookDirection);
}
