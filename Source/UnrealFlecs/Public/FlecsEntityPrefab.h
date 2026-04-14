// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "flecs.h"
#include "FlecsEntityHandle.h"
#include "FlecsEntityPrefab.generated.h"

struct FFlecsPrefabRegistry;

UCLASS(Abstract, BlueprintType)
class UNREALFLECS_API UFlecsEntityPrefab : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual void SetInstanceComponents(flecs::entity& Entity) const {}
	
	flecs::entity CreateInstance(const flecs::world& World, FFlecsPrefabRegistry& Registry) const;

	TArray<flecs::entity> BatchCreateInstances(const flecs::world& FlecsWorld, FFlecsPrefabRegistry& Registry, int32 Count) const;

	TArray<FFlecsEntityHandle> BatchCreateInstanceHandles(const flecs::world& FlecsWorld, FFlecsPrefabRegistry& Registry, const int32 Count) const;
	
protected:
	virtual flecs::entity CreatePrefab(const flecs::world& FlecsWorld) const
	{
		return FlecsWorld.prefab();
	}
	
	friend struct FFlecsPrefabRegistry;
};

struct FFlecsPrefabRegistry
{
	explicit FFlecsPrefabRegistry(const int32 ReserveAmount)
	{
		Prefabs.Reserve(ReserveAmount);
	}
	
	flecs::entity GetOrCreate(const flecs::world& FlecsWorld, const UFlecsEntityPrefab* Asset);
	
private:
	TMap<FPrimaryAssetId, flecs::entity> Prefabs;
};