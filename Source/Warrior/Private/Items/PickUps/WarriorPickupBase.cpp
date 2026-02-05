// BY Zwx


#include "Items/PickUps/WarriorPickupBase.h"
#include "Components/SphereComponent.h"


// Sets default values
AWarriorPickupBase::AWarriorPickupBase()
{
	PrimaryActorTick.bCanEverTick = false;

	PickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Pick Up Collision Sphere"));
	SetRootComponent(PickUpCollisionSphere);
	PickUpCollisionSphere->InitSphereRadius(50.f);
	PickUpCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AWarriorPickupBase::OnPickUpCollisionSphereBeginOverlap);


}

void AWarriorPickupBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}



