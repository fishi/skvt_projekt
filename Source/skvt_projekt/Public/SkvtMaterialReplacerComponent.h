// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkvtMaterialReplacerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKVTPROJEKT_API USkvtMaterialReplacerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UMaterialInterface> ReplacementMaterial;

	UPROPERTY(EditDefaultsOnly)
	int32 MaterialToReplaceIndex;

public:	
	// Sets default values for this component's properties
	USkvtMaterialReplacerComponent();

public:
	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UMeshComponent* GetMeshComponent();
	
private:
	UPROPERTY()
	TWeakObjectPtr<UMeshComponent> MeshComponent;
	
	UPROPERTY()
	TWeakObjectPtr<UMaterialInterface> ReplacedMaterial;
};
