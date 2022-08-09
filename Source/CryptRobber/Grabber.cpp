// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber() :
	MaxGrabDistance(500.f ),
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

	UPhysicsHandleComponent*PhysicsHandle = GetOwner( )->FindComponentByClass<UPhysicsHandleComponent>( );
	if ( PhysicsHandle != nullptr )
	{
		PhysicsHandle->GetName( );
		UE_LOG( LogTemp, Warning, TEXT( "Phy.Handel Name: %s" ), *PhysicsHandle->GetName( ) );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "NO PHYSICS HANDLE!" ) );
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}


void UGrabber::Grab( )
{
	FVector Start = GetComponentLocation( );
	FVector End = Start + GetForwardVector( ) * MaxGrabDistance;

	DrawDebugLine( GetWorld( ), Start, End, FColor::Red );
	DrawDebugSphere( GetWorld( ), End, 10, 10, FColor::Blue, false, 5);
	
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
		DrawDebugSphere( GetWorld( ), HitResult.Location, 10, 10, FColor::Green, false, 5 );
		DrawDebugSphere( GetWorld( ), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5 );
		AActor* HitActor = HitResult.GetActor( );

		UE_LOG( LogTemp, Warning, TEXT( "Hit Actor: %s" ), *HitResult.GetActor( )->GetActorNameOrLabel( ) );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "No Actor Hit." ) );
	}
}

void UGrabber::Release( )
{
	UE_LOG( LogTemp, Warning, TEXT( "Grabber released." ) );
}

