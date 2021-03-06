// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTPickup.h"
#include "PaperSpriteComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/BoxComponent.h"
#include "ENTCharacter.h"

// Sets default values
AENTPickup::AENTPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	RootComponent = BoxComponent;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite Component");
	SpriteComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	SpriteComponent->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AENTPickup::OnPickup);
}

// Called when the game starts or when spawned
void AENTPickup::BeginPlay()
{
	Super::BeginPlay();
	SetRandomPickupClass();
	SetOrientation();
}

// Called every frame
void AENTPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AENTPickup::SetOrientation()
{
	FVector NewVector = GetActorLocation();
	NewVector.Z = -1;
	SetActorLocation(NewVector);
	SpriteComponent->SetRelativeRotation(FRotator(0, -90, 90));
	SpriteComponent->SetRelativeScale3D(FVector(0.8, 0.8, 0.8));
}

void AENTPickup::SetPickupClass(ENTCharacterClass ENTClass)
{
	PickupClass = ENTClass;
	if (DataTable) 
	{
		FName className = EnumToFName("ENTCharacterClass", ENTClass);
		FPickupSpriteData* row = DataTable->FindRow<FPickupSpriteData>(className, TEXT(""));
		if (row) 
		{
			SpriteComponent->SetSprite(row->BlueSprite);
		}
	}
}

void AENTPickup::SetRandomPickupClass()
{
	SetPickupClass((ENTCharacterClass) FMath::RandRange(0, 3));
}

void AENTPickup::OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AENTCharacter::StaticClass())) 
	{
		AENTCharacter* CharRef = Cast<AENTCharacter>(OtherActor);
		if (CharRef)
		{
			FName OtherClass = EnumToFName("ENTCharacterClass", CharRef->GetCharacterClass());
			FName ThisClass = EnumToFName("ENTCharacterClass", PickupClass);
			FString PrintStr = OtherClass.ToString() + " picked up a " + ThisClass.ToString() + " pickup.";
			UKismetSystemLibrary::PrintString(this, PrintStr);
			CharRef->ApplyPickup(PickupClass);
			Destroy();
		}
	}
}
