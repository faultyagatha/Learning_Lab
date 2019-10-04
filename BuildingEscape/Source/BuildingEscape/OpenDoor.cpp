// MIT License


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    Owner = GetOwner(); //find the owning actor
    if(!PressurePlate) {
        UE_LOG(LogTemp, Error, TEXT("% missing  pressure plate"), *GetOwner()->GetName());
    }
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//poll the trigger volume every frame
    if(GetTotalMassOfActorOnPlate() > 120.f) { //TODO: parametirise
        //if the ActoThatOpens is in the volume:
        OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    if(GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
    {
        CloseDoor();
    }
}

float UOpenDoor::GetTotalMassOfActorOnPlate() {
    float TotalMass = 0.f;
    //find all the overlapping actors
    TArray<AActor*> OverlappingActors;
    if(!PressurePlate) { return TotalMass; }
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    //iterate over overlapping actors
    for(const auto* Actor : OverlappingActors) { //use * instead of &
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
        return TotalMass;
}

void UOpenDoor::OpenDoor()
{
//    FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f); //create a rotator
//    Owner->SetActorRotation(NewRotation); //set the rotation
    OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
    //a shortcut withour creating the rotator
    Owner->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f)); //set the rotation
}

