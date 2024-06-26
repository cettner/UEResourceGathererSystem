// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Resource.generated.h"

USTRUCT()
struct FReplicationResourceMap
{
	GENERATED_BODY()
public:
	void Emplace(const TSubclassOf<UResource>& Key, int Value)
	{
		int index = Keys.IndexOfByKey(Key);

		if (index == INDEX_NONE)
		{
			Keys.Emplace(Key);
			Values.Emplace(Value);
		}
		else
		{
			Values[index] = Value;
		}
	}

	bool Remove(const TSubclassOf<UResource>& Key)
	{
		bool retval = false;
		int index = Keys.IndexOfByKey(Key);

		if (index != INDEX_NONE)
		{
			Keys.RemoveAt(index);
			Values.RemoveAt(index);
			retval = true;
		}

		return retval;
	}

	bool Increment(const TSubclassOf<UResource>& Key, int Value)
	{
		//todo return the new value instead
		bool retval = false;

		if (const int* curval = Find(Key))
		{
			const int newval = *curval + Value;
			Emplace(Key, newval);
			retval = true;
		}
		else
		{
			Emplace(Key, Value);
			retval = true;
		}

		return retval;
	}

	bool Decrement(const TSubclassOf<UResource>& Key, int Value)
	{
		bool retval = false;
		//todo return the new value instead
		if (const int* curval = Find(Key))
		{
			int newval = *curval - Value;
			if (newval < 0)
			{
				newval = 0;
			}
			Emplace(Key, newval);
			retval = true;
		}
		else
		{
			Emplace(Key, 0);
			retval = true;
		}

		return retval;
	}

	const int* Find(const TSubclassOf<UResource>& Key) const
	{
		int index = Keys.IndexOfByKey(Key);

		if (index != INDEX_NONE)
		{
			const int* retval = &Values[index];
			return(retval);
		}

		return(nullptr);
	}

	int Num() const
	{
		return(Keys.Num());
	}

	const TArray<TSubclassOf<UResource>>& GetKeys() const
	{
		return Keys;
	}

	TMap<TSubclassOf<UResource>, int> GetMap() const
	{
		TMap<TSubclassOf<UResource>, int> Map = TMap<TSubclassOf<UResource>, int>();
		checkf(IsValid(), TEXT("FReplicationResourceMap::GetMap"));

		for (int i = 0; i < Keys.Num(); i++)
		{
			Map.Emplace(Keys[i], Values[i]);
		}

		return(Map);
	}

	bool IsValid() const
	{
		return(Keys.Num() == Values.Num());
	}

	/*Allows Pair Iteration*/
	TPair<TSubclassOf<UResource>, int > operator[](int Index) const
	{
		return TPair<TSubclassOf<UResource>, int >(Keys[Index], Values[Index]);
	}
protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<int> Values;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UResource>> Keys;
};

UCLASS(BluePrintable)
class RESOURCEGATHERERSYSTEM_API UResource : public UObject
{
	GENERATED_BODY()

	public:
		uint32 GetResourceWeight() const;
		FName GetResourceName() const;
		FORCEINLINE bool IsWeightedResource() const { return IsWeighted; }

		/*Helper Static Function for purchasing Things With Resources*/
		static bool CanAfford(FReplicationResourceMap BuyerResources, FReplicationResourceMap SellerCost);

	protected:
		UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		bool IsWeighted = true;

		UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		uint32 ResourceWeight = 1U;

		UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		FName ResourceName = "Default Resource";
	
};
