// MIT License


#include "OpenDoor.h"

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
    //start searching for the player controller ("the mind of our pawn")
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//poll the trigger volume every frame
    if(PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        //if the ActoThatOpens is in the volume:
        OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    if(GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
    {
        CloseDoor();
    }
}

void UOpenDoor::OpenDoor()
{
    FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f); //create a rotator
    Owner->SetActorRotation(NewRotation); //set the rotation
}

void UOpenDoor::CloseDoor()
{
    //a shortcut withour creating the rotator
    Owner->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f)); //set the rotation
}

