// MIT License


#include "Grabber.h"
#include "DrawDebugHelpers.h"

#define OUT //this macro does nothing but reminds us that we change the variable

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
    // You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    Reach = 100.f;
    PhysicsHandle = nullptr;
    InputComponent = nullptr;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetupInputComponent();
 
}

void UGrabber::FindPhysicsHandleComponent() {
    //look for attached physics handle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(PhysicsHandle) {
        //
    } else {
        UE_LOG(LogTemp, Error, TEXT("%s no PhysicsHandle is found "), *GetOwner()->GetName());
    }
}

void UGrabber::SetupInputComponent() {
    //look for attached input component (only appears at run time)
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if(InputComponent) {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent is found "));
        //bind the input action (we operate on the same object with Grab in the input settings)
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    } else {
        UE_LOG(LogTemp, Error, TEXT("%s no InputComponent is found "), *GetOwner()->GetName());
    }
}

void UGrabber::Grab() {
    UE_LOG(LogTemp, Warning, TEXT("Grabbing"));
    //line trace and see if we reach any actors with physics body collision channel set
    GetFirstPhysicsBodyInReach();
    //if we hit something, attach physics
}

void UGrabber::Release() {
    UE_LOG(LogTemp, Warning, TEXT("Releasing"));
    //TODO: release physics
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
    // if the physics handle is attached
    // move the object that we're holding
    
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    
    //getPlayerViewPoint changes the parameters! See the documentation: &out hints at that!
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation);
    
    UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
           *PlayerViewPointLocation.ToString(),
           *PlayerViewPointRotation.ToString());
    
    
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
    //draw a red debug line to visualise the trace
    DrawDebugLine(
                  GetWorld(),
                  PlayerViewPointLocation,
                  LineTraceEnd,
                  FColor(255, 0, 0),
                  false,
                  0.f,
                  0.f,
                  10.f
                  );
    
    //line-trace(raycasting) out to reach the distance
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
                                            OUT Hit,
                                            PlayerViewPointLocation,
                                            LineTraceEnd,
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters
                                            );
    //see what we hit
    AActor* ActorHit = Hit.GetActor();
    if(ActorHit) {
        UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *ActorHit->GetName());
    }
    return Hit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
}

