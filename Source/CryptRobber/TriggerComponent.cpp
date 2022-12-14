// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent() :
	AcceptableActorTag("Unlock1" )
{
	PrimaryComponentTick.bCanEverTick = true;
	//UE_LOG( LogTemp, Warning, TEXT( "Building..." ) ); 
}

// Called when the game starts
void UTriggerComponent::BeginPlay( )
{
	Super::BeginPlay( );

}

void UTriggerComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	AActor* Actor = GetAcceptableActor( );
	if ( Actor != nullptr )
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>( Actor->GetRootComponent( ) );
		if ( Component != nullptr )
		{
			Component->SetSimulatePhysics( false );
		}
		Actor->AttachToComponent( this, FAttachmentTransformRules::KeepWorldTransform );
		Mover->SetShouldMove( true );
	}
	else
	{
		Mover->SetShouldMove( false );
	}
#pragma region Unused Code Region

	/*TArray<AActor*> Actors;
	GetOverlappingActors( Actors );*/

	//method 1
	//--------
	/*if ( Actors.Num( ) > 0 )
	{
		FString ActorName = Actors [ index ]->GetActorNameOrLabel( );
		UE_LOG( LogTemp, Warning, TEXT( "Overlapping : %s" ), *ActorName );
	}*/

	//method 2
	//--------
	/*int32 index = 0;
	while ( index < Actors.Num() )
	{
		FString ActorName = Actors [ index ]->GetActorNameOrLabel( ); 
		UE_LOG( LogTemp, Warning, TEXT( "Overlapping : %s" ), *ActorName );
		++index;
	}*/

	//method 3
	 //--------
	/*for (int32 i = 0; i < Actors.Num(); i++)
	{
		FString ActorName = Actors [ i]->GetActorNameOrLabel( );
		UE_LOG( LogTemp, Warning, TEXT( "Overlapping : %s" ), *ActorName );
	}*/

	//method 4
	//--------
	/*for ( AActor* Actor : Actors )
	{
		FString ActorName = Actor->GetActorNameOrLabel( );
		UE_LOG( LogTemp, Warning, TEXT( "Overlapping : %s" ), *ActorName );
	}*/

	//method 5
	//--------
	/*for ( AActor* Actor : Actors )
	{
		if ( Actor->ActorHasTag( AcceptableActorTag ) )
		{
			UE_LOG( LogTemp, Warning, TEXT( "Unlocking.." ) );
		}	
	}*/
#pragma endregion
}

void UTriggerComponent::SetMover( UMover* NewMover )
{
	Mover = NewMover; 
}

AActor* UTriggerComponent::GetAcceptableActor( ) const
{
	TArray<AActor* > Actors;
	GetOverlappingActors( Actors );

	for ( AActor* Actor : Actors )
	{
		if ( Actor->ActorHasTag( AcceptableActorTag ) && !Actor->ActorHasTag(("Grabbed") ))
		{
			return Actor;
		}
	}
	return nullptr;
}

