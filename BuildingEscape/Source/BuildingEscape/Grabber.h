// MIT License

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
private:
    //how far ahead of the the player can we reach in cm
    float Reach;
    
    UPhysicsHandleComponent* PhysicsHandle;
    
    UInputComponent* InputComponent;
    
    //ray-cast and grab or release
    void Grab();
    void Release();
    
    //find (assumed) attached phyics handle
    void FindPhysicsHandleComponent();
    
    //setup (assumed) attached input component
    void SetupInputComponent();
    
    //return hit for first physics body in reach
    const FHitResult GetFirstPhysicsBodyInReach();
		
};
