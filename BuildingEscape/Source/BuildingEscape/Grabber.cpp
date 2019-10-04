// MIT License


#include "Grabber.h"
#include "DrawDebugHelpers.h"

#define OUT //this macro does nothing but reminds us that we're changing the variable

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
    if(PhysicsHandle == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("%s no PhysicsHandle is found "), *GetOwner()->GetName());
    }
}

void UGrabber::SetupInputComponent() {
    //look for attached input component (only appears at run time)
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if(InputComponent) {
        UE_LOG(LogTemp, Warning, TEXT("Grabber component is found"));
        //bind the input action (we operate on the same object with Grab in the input settings)
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    } else {
        UE_LOG(LogTemp, Error, TEXT("%s no InputComponent is found "), *GetOwner()->GetName());
    }
}

void UGrabber::Grab() {
    //line trace and see if we reach any actors with physics body collision channel set
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    if(ActorHit) {
    //if we hit something, attach physics
        if(!PhysicsHandle) { return; } //check for null pointers
        PhysicsHandle->GrabComponentAtLocation(
                        ComponentToGrab,
                        NAME_None,
                        ComponentToGrab->GetOwner()->GetActorLocation());
    }
}

void UGrabber::Release() {
    UE_LOG(LogTemp, Warning, TEXT("Releasing"));
    if(!PhysicsHandle) { return; } //check for null pointers
    PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
    // if the physics handle is attached
    // move the object that we're holding
    //line-trace(raycasting) out to reach the distance
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
                                            OUT Hit,
                                            GetReachLineStart(),
                                            GetReachLineEnd(),
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            TraceParameters
                                            );

    return Hit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if(!PhysicsHandle) { return; } //check for null pointers
    if(PhysicsHandle->GrabbedComponent) {
        //move the object we're holding
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
}

FVector UGrabber::GetReachLineStart() {
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    
    //getPlayerViewPoint changes the parameters! See the documentation: &out hints at that!
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                OUT PlayerViewPointLocation,
                                                OUT PlayerViewPointRotation);
    
    return PlayerViewPointLocation;
}
    
FVector UGrabber::GetReachLineEnd() {
        FVector PlayerViewPointLocation;
        FRotator PlayerViewPointRotation;
        
        //getPlayerViewPoint changes the parameters! See the documentation: &out hints at that!
        GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                OUT PlayerViewPointLocation,
                                                OUT PlayerViewPointRotation);
        
        return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}



