// Copyright Sudip Mondal

#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	FindPressurePlate();
	FindAudioComponent();
	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlate)
	{
		return;
	}
	if (PressurePlate && TotalMassOfActors() > MassToOpen)
	{
		DoorLastOpened = GetWorld()->GetTimeSeconds();
		OpenDoor(DeltaTime);
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() > DoorLastOpened + DoorOpenDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	if (!AudioComponent) {return;}
	if (!OpenDoorSound){
		AudioComponent->Play();
		OpenDoorSound=true;
		CloseDoorSound=false;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	if (!AudioComponent) {return;}
	if (!CloseDoorSound){
		UE_LOG(LogTemp,Warning,TEXT("Playing CloseDoor"))
		AudioComponent->Play();
		OpenDoorSound=false;
		CloseDoorSound=true;
	}
}

float UOpenDoor::TotalMassOfActors()
{
	TotalMass = 0.f;
	TArray<AActor *> ObjectsThatOpen;
	PressurePlate->GetOverlappingActors(OUT ObjectsThatOpen);
	for (AActor *Actor : ObjectsThatOpen)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

void UOpenDoor::FindPressurePlate()
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has OpenDoor component but no Pressureplate selected"), *GetOwner()->GetName())
	}
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has OpenDoor component but no AudioComponent selected"), *GetOwner()->GetName())
	}
}