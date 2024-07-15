// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"  // �̰� generated.h���� ���� include�Ǿ����. 
#include "MyGameInstance.generated.h"

// TODO
USTRUCT()
struct FMyCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHP;
};

/**
 * 
 */
UCLASS()
class UE_PROJECT1_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

public:
	virtual void Init() override;	

public:
	FMyCharacterData* GetStatData(int32 Level);

private:
	UPROPERTY()
	class UDataTable* MyStats;
};
