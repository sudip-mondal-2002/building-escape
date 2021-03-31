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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:
	float InitialYaw, CurrentYaw;
	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;
	UPROPERTY(EditAnyWhere)
	AActor *ActorThatOpens;
	float DoorLastOpened = 0.f;
	UPROPERTY(EditAnyWhere)
	float DoorOpenDelay = 2.f;
	UPROPERTY(EditAnyWhere)
	float DoorOpenspeed = .8f;
	UPROPERTY(EditAnyWhere)
	float DoorCloseSpeed = 2.f;

};
