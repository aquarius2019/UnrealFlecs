// Copyright © 2025 ClownWare Games. All Rights Reserved.

#pragma once

#include "FlecsArchetypeBase.h"
#include "FlecsEntityPrefab.h"
#include "FlecsInventoryComponents.h"
#include "GameplayTagContainer.h"
#include "FlecsInventoryItemPrefab.generated.h"

/**
 * 
 */
UCLASS()
class FLECSINVENTORY_API UFlecsInventoryItemPrefab : public UFlecsEntityPrefab
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag Tag = FGameplayTag::EmptyTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Name = "";

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Description = "";

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> Thumbnail = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FFlecsInventoryItemSize Size  = 1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 MaxStackAmount = 1;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(ShowOnlyInnerProperties))
	FFlecsArchetypeBundle Archetypes = {};

	virtual void SetInstanceComponents(flecs::entity& Entity) const override;
};