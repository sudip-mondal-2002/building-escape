// Copyright Sudip Mondal

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnyWhere)
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;	
	UInputComponent* InputComponent= nullptr;
	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetUpInputComponent();
	FHitResult FirstPhysicsBodyInReach() const;
};
