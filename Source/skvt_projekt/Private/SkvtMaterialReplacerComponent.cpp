// Fill out your copyright notice in the Description page of Project Settings.


#include "SkvtMaterialReplacerComponent.h"

// Sets default values for this component's properties
USkvtMaterialReplacerComponent::USkvtMaterialReplacerComponent()
{
	bWantsInitializeComponent = true;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USkvtMaterialReplacerComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	MeshComponent = GetMeshComponent();
	UMaterialInterface* NewMat = ReplacementMaterial.LoadSynchronous();

	if (!MeshComponent.IsValid())
	{
		SetActive(false);
		return;
	}

	if (NewMat == nullptr)
	{
		return;
	}

	ReplacedMaterial = MeshComponent->GetMaterial(MaterialToReplaceIndex);
	MeshComponent->SetMaterial(MaterialToReplaceIndex, NewMat);
}

void USkvtMaterialReplacerComponent::Deactivate()
{
	UMaterialInterface* OldMat = ReplacementMaterial.Get();
	if (MeshComponent.IsValid() && ReplacementMaterial.IsValid())
	// if (MeshComponent.IsValid() && OldMat != nullptr)
	{
		MeshComponent->SetMaterial(MaterialToReplaceIndex, ReplacedMaterial.Get());
	}

	ReplacedMaterial = nullptr;
	
	Super::Deactivate();
}

// Called when the game starts
void USkvtMaterialReplacerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USkvtMaterialReplacerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UMeshComponent* USkvtMaterialReplacerComponent::GetMeshComponent()
{
	if (MeshComponent.IsValid())
	{
		return MeshComponent.Get();
	}
	
	TArray<UActorComponent*> ActorComponents = GetOwner()->GetComponentsByTag(UMeshComponent::StaticClass(), FName("MaterialReplacer"));
	if (ActorComponents.IsEmpty())
	{
		return nullptr;
	}

	MeshComponent = Cast<UMeshComponent>(ActorComponents[0]);
	return MeshComponent.Get();
}

