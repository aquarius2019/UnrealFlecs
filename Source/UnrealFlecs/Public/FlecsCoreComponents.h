﻿#pragma once

#include "FlecsTypeRegistry.h"
#include "FlecsCoreComponents.generated.h"

struct FFlecsAttachedTo;
struct FFlecsTransform;

struct UNREALFLECS_API FlecsTransformUtils
{
	using TransformQuery = flecs::query<const FFlecsTransform, const FFlecsAttachedTo, FFlecsTransform>;
	
	static void PropagateTransformUpdates(const TransformQuery& Query, const flecs::entity& Parent);

	static void SetLocalTransform(const TransformQuery& Query, const flecs::entity& Entity, const FTransform& NewTransform);
	static void SetGlobalLocation(const TransformQuery& Query, const flecs::entity& Entity, const FVector& NewLocation);
	static void SetGlobalLocation(const TransformQuery& Query, const flecs::entity& Entity, FFlecsTransform& Transform, const FVector& NewLocation);
	static void SetGlobalRotation(const TransformQuery& Query, const flecs::entity& Entity, const FQuat& NewRotation);
	static void SetGlobalRotation(const TransformQuery& Query, const flecs::entity& Entity, FFlecsTransform& Transform, const FQuat& NewRotation);
	static void SetGlobalTransform(const TransformQuery& Query, const flecs::entity& Entity, const FTransform& NewTransform);
	static void SetGlobalTransform(const TransformQuery& Query, const flecs::entity& Entity, FFlecsTransform& Transform, const FTransform& NewTransform);

	static void SetLocationAndRotation(const TransformQuery& Query, const flecs::entity& Entity, FFlecsTransform& Transform,
		const FVector& NewLocation, const FQuat& NewRotation);
	
	static void AddGlobalOffset(const TransformQuery& Query, const flecs::entity& Entity, FFlecsTransform& Transform, const FVector& Offset);
	
	static void AttachEntityTo(const TransformQuery& Query, const flecs::entity& Entity, const flecs::entity& Parent, const FTransform& RelativeTransform = FTransform::Identity);

	static void UpdateLocalTransform(const flecs::entity& Entity, const FTransform& Transform);
};


REG_FLECS_COMPONENT(FFlecsAttachedTo)
USTRUCT(BlueprintType)
struct FFlecsAttachedTo
{
	using TransformQuery = flecs::query<const FFlecsTransform, const FFlecsAttachedTo, FFlecsTransform>;
	
	GENERATED_BODY()

	const FTransform& get_relative_transform() const { return Value; }
	const FName& get_socket_name() const { return Socket; }
	
private:
	UPROPERTY(EditAnywhere)
	FName Socket = NAME_None;

	UPROPERTY(EditAnywhere)
	FTransform Value = FTransform::Identity;

	friend struct FFlecsTransform;
	friend struct FlecsTransformUtils;
};

REG_FLECS_COMPONENT(FFlecsTransform)
USTRUCT(BlueprintType)
struct FFlecsTransform
{
	using TransformQuery = flecs::query<const FFlecsTransform, const FFlecsAttachedTo, FFlecsTransform>;
	
	GENERATED_BODY()

	FFlecsTransform() = default;

	explicit FFlecsTransform(const FTransform& new_transform) : Value(new_transform) {}

	const FTransform& get() const { return Value; }
	FVector get_location() const { return Value.GetTranslation(); }
	FQuat get_rotation() const { return Value.GetRotation(); }
	FVector get_unit_axis(const EAxis::Type axis) const { return Value.GetUnitAxis(axis); }
	
private:
	UPROPERTY(EditAnywhere)
	FTransform Value = FTransform::Identity;

	friend struct FFlecsAttachedTo;
	friend struct FlecsTransformUtils;
};

UENUM(BlueprintType)
enum class EFlecsTransformUpdateMode : uint8
{
	FlecsToUWorld,
	UWorldToFlecs
};