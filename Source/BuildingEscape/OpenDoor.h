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
	void FindAudioComponent();
	void FindPressurePlate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Pointers
	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate = nullptr;

	UPROPERTY()
	UAudioComponent *AudioComponent = nullptr;

private:
	float InitialYaw, CurrentYaw;
	float DoorLastOpened = 0.f;
	float TotalMass=0.f;
	bool OpenDoorSound=false;
	bool CloseDoorSound=true;
//Exposed to editor
	
	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;
	UPROPERTY(EditAnyWhere)
	float DoorOpenDelay = 0.2f;
	UPROPERTY(EditAnyWhere)
	float DoorOpenSpeed = .8f;
	UPROPERTY(EditAnyWhere)
	float DoorCloseSpeed = 2.f;
	UPROPERTY(EditAnyWhere)
	float MassToOpen = 60.f;
};
