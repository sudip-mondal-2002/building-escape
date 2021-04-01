// Copyright Sudip Mondal

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	float InitialYaw, CurrentYaw;
	float DoorLastOpened = 0.f;
	float TotalMass=0.f;
//Exposed to editor
	
	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;
	UPROPERTY(EditAnyWhere)
	AActor *ActorThatOpens;
	UPROPERTY(EditAnyWhere)
	float DoorOpenDelay = 0.5f;
	UPROPERTY(EditAnyWhere)
	float DoorOpenSpeed = .8f;
	UPROPERTY(EditAnyWhere)
	float DoorCloseSpeed = 2.f;
};
