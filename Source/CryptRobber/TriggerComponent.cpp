// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG( LogTemp, Warning, TEXT( "Building..." ) ); 
}

// Called when the game starts
void UTriggerComponent::BeginPlay( )
{
	Super::BeginPlay( );

}

void UTriggerComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	TArray<AActor*> Actors;
	GetOverlappingActors( Actors );

	if ( Actors.Num( ) > 0 )
	{
		FString ActorName = Actors [ 0 ]->GetActorNameOrLabel( );
		UE_LOG( LogTemp, Warning, TEXT( "Overlapping : %s" ), *ActorName );
	}
}
