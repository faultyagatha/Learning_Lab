// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
    if(!Barrel) { return; }
    FVector OutLaunchVelocity(0.);
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    
    if(UGameplayStatics::SuggestProjectileVelocity(
                                                   this,
                                                   OutLaunchVelocity,
                                                   StartLocation,
                                                   HitLocation,
                                                   false)) {
        
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        auto TankName = GetOwner()->GetName();
        UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());
        MoveBarrel(AimDirection);
    }
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotaro = AimAsRotator - BarrelRotator;
    UE_LOG(LogTemp, Warning, TEXT("AimAsRotator is %s"), *AimAsRotator.ToString());
    
    Barrel->Elevate(5.);
}

