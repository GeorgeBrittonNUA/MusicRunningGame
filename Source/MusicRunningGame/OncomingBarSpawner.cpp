// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingBarSpawner.h"


// Sets default values
AOncomingBarSpawner::AOncomingBarSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the default objects and attaches to root
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->SpawnPointComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnPoint"));
	SpawnPointComponent->SetupAttachment(this->RootComponent);
	SpawnPointComponent->bHiddenInGame = true;
	SpawnPointComponent->SetWorldScale3D(FVector(0.2,0.2,0.2));

}

// Called every time a value is changed
void AOncomingBarSpawner::OnConstruction(const FTransform &trans)
{
	if (SpawnPoint){SpawnPointComponent->SetStaticMesh(SpawnPoint);}
}

// Called when the game starts or when spawned
void AOncomingBarSpawner::BeginPlay()
{
	Super::BeginPlay();

	if(BarActor && BarDetails.Num() > 0)
	{
		// Creates a timer delegate and uses it in a timed spawn event
		FTimerDelegate Delegate;
		Delegate.BindUObject(this, &AOncomingBarSpawner::Spawn);
		GetWorld()->GetTimerManager().SetTimer(SpawningTimer, Delegate, SpawnFrequencyInSeconds, true, SpawnFrequencyInSeconds);
	} else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, TEXT("Please assign a Bar class, and add at least one entry to 'Bar Details'"));
	}

}

// Called every frame
void AOncomingBarSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called every SpawnFrequencyInSeconds seconds
void AOncomingBarSpawner::Spawn()
{
	// Chooses a random point within the spawn box and spawns an obstacle there
	const FVector SpawnLoc = GetActorLocation();
	const FRotator SpawnRot(FQuat::Identity);
	FActorSpawnParameters SpawnParams;

	// Gets a reference to the new Obstacle and gives it the preset variables
	AOncomingBar* BarRef = GetWorld()->SpawnActor<AOncomingBar>(BarActor, SpawnLoc, SpawnRot, SpawnParams);
	int32 ChosenBar = FMath::RandRange(0, BarDetails.Num() - 1);
	BarRef->BarMesh = BarDetails[ChosenBar].BarMesh;
	BarRef->Key = BarDetails[ChosenBar].Key;
	BarRef->Damage = BarDetails[ChosenBar].Damage;
	BarRef->Speed = Speed;

}