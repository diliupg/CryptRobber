// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber() :
	MaxGrabberDistance(500.f ),
	GrabRadius(100.f )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Start = GetComponentLocation( );
	FVector End = Start + GetForwardVector( ) * MaxGrabberDistance;

	DrawDebugLine( GetWorld( ), Start, End, FColor::Red );

	FCollisionShape Sphere = FCollisionShape::MakeSphere( GrabRadius );
	FHitResult HitResult;
	bool Hashit = GetWorld( )->SweepSingleByChannel(
		HitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere );
	if ( Hashit )
	{
		//AActor* HitActor = HitResult.GetActor( );

		UE_LOG( LogTemp, Warning, TEXT( "Hit Actor: %s" ), *HitResult.GetActor( )->GetActorNameOrLabel( ) );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "No Actor Hit." ) );
	}
}

