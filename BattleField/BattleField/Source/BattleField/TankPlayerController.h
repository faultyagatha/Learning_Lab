// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEFIELD_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
    
public:
    ATankPlayerController();
    
protected:
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;
    
private:
    ATank* GetControlledTank() const;

    void AimTowardsCrosshair(); //start the tank moving the barrel so that the shot would hit where the crosshair intersects the world
    
    UPROPERTY(EditAnywhere)
    float CrosshairXLocation;
    
    UPROPERTY(EditAnywhere)
    float CrosshairYLocation;
    
    UPROPERTY(EditAnywhere)
    float LineTraceRange;
    
    //return an OUT parameter. True if hit anything in the world
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
    
	
};
