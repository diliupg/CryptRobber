// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber() :
	MaxGrabberDistance(400.f ),
	GrabRadius(100.f ),
	HoldDistance(200.f )
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

	UPhysicsHandleComponent* PhysicsHandle = GetOwner( )->FindComponentByClass<UPhysicsHandleComponent>( );
	/*if ( PhysicsHandle != nullptr )
	{
		UE_LOG( LogTemp, Warning, TEXT( "Physics HandleF O U N D !!!: %s" ), *PhysicsHandle->GetName( ) );
	}
	else
	{
		UE_LOG( LogTemp, Warning, TEXT( "NOTHING FOUND" ) );
	}*/
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetOwner( )->FindComponentByClass<UPhysicsHandleComponent>( );
	if ( PhysicsHandle == nullptr ) return;

	FVector TargetLocation = GetComponentLocation( ) + GetForwardVector( ) + HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation( TargetLocation, GetComponentRotation( ) );
}

void UGrabber::Grab( )
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner( )->FindComponentByClass<UPhysicsHandleComponent>( );
	if ( PhysicsHandle == nullptr ) return;

	FVector Start = GetComponentLocation( );
	FVector End = Start + GetForwardVector( ) * MaxGrabberDistance;

	//DrawDebugLine( GetWorld( ), Start, End, FColor::Red );
	//DrawDebugSphere( GetWorld( ), End, 10, 10,  FColor::Blue, false, 5 );

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
		//DrawDebugSphere( GetWorld( ), HitResult.Location, 10, 10, FColor::Green, false, 5 );
		//DrawDebugSphere( GetWorld( ), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5 );
		UE_LOG( LogTemp, Warning, TEXT( "Hit Actor: %s" ), *HitResult.GetActor( )->GetActorNameOrLabel( ) );
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent( ),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation( ) );
	}

}

void UGrabber::Release( )
{
	UE_LOG( LogTemp, Warning, TEXT( "Released Grabber!" ) );
}

