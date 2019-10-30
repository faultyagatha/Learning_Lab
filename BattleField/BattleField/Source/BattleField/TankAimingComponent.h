// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

//holds barrel's properties and elevate method

//forward declaration. Beware: if we need to use the methods of the included class, we need to do #include in .cpp file
class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLEFIELD_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
    void AimAt(FVector HitLocation, float LaunchSpeed);
    
    //setter
    void SetBarrelReference(UTankBarrel* BarrelToSet);
	

private:
    UTankBarrel* Barrel = nullptr;
    
    void MoveBarrel(FVector AimDirection);
    
		
};
