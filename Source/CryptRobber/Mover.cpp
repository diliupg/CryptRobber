
// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover() :
	MoveTime(4.f ),
	ShouldMove(false ),
	MoveOffset { 0.0f, 0.0f, -800.f }



{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner( )->GetActorLocation( );
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector CurrentLocation = GetOwner( )->GetActorLocation( );
	FVector TargetLocation = OriginalLocation + MoveOffset;
	float Speed = FVector::Distance( OriginalLocation, TargetLocation ) / MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo( CurrentLocation, TargetLocation, DeltaTime, Speed );
	GetOwner( )->SetActorLocation( NewLocation );

	
	/*AActor* Owner = GetOwner( );
	FString Name = Owner->GetActorNameOrLabel( );
	FVector Location = Owner->GetActorLocation( );
	FString LocString = Location.ToCompactString( );
	UE_LOG( LogTemp, Warning, TEXT( "Mover Owner %s is at %s" ), *Name, *LocString );*/
}


