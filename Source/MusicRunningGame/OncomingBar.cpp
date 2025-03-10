// Fill out your copyright notice in the Description page of Project Settings.

#include "OncomingBar.h"


// Sets default values
AOncomingBar::AOncomingBar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the default objects and attaches to root
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->BarMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarMesh"));
	this->BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BarMeshComponent->SetupAttachment(this->RootComponent);
	BoxCollisionComponent->SetupAttachment(this->RootComponent);

	this->bGenerateOverlapEventsDuringLevelStreaming = true;
	BarMeshComponent->SetCollisionProfileName("OverlapAll");
}

// Called every time a value is changed
void AOncomingBar::OnConstruction(const FTransform &trans)
{
	if (BarMesh)
	{
		BarMeshComponent->SetStaticMesh(BarMesh);
		BoxCollisionComponent->SetWorldScale3D(FVector(BarMeshComponent->GetComponentScale()));
	}
}

// Called when the game starts or when spawned
void AOncomingBar::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AOncomingBar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BarMesh && !MeshSet)
	{
		BarMeshComponent->SetStaticMesh(BarMesh);
		MeshSet = true;
	}

	this->AddActorWorldOffset(FVector(-Speed, 0, 0), true, nullptr, ETeleportType::None);

}

// Called when the bar hits anything
void AOncomingBar::NotifyActorBeginOverlap(AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(1, 15.0f, FColor::Red, "I am being notified of a hit.");

	APlayerPawn* PlayerRef = Cast<APlayerPawn>(OtherActor);
	if (PlayerRef){	PlayerRef->HitByOncomingBar(this, Key, Damage); }
}