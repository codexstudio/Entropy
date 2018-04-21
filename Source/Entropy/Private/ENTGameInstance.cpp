// Fill out your copyright notice in the Description page of Project Settings.

#include "ENTGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ENTSharedCamera.h"
#include "EntropyGameModeBase.h"
#include "GameFramework/Actor.h"
#include "ENTCharacter.h"
#include "ENTPlayerController.h"


void UENTGameInstance::SetLastSessionScore(int value)
{
	SessionScore = value;
	UpdateLeaderBoard();
}

void UENTGameInstance::UpdateLeaderBoard()
{
	FString PlayerGamerTags = "";

	AEntropyGameModeBase* GameMode = Cast<AEntropyGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode)
	{
		for (AActor* Player : GameMode->GetSharedCamera()->GetPlayers())
		{
			AENTCharacter* ENTChar = Cast<AENTCharacter>(Player);
			if (ENTChar)
			{
				AENTPlayerController* PlayCont = Cast<AENTPlayerController>(ENTChar->GetController());
				if (PlayCont)
				{
					if (PlayerGamerTags == "")
					{
						PlayerGamerTags += PlayCont->GetGamerTag();
					}
					else
					{
						PlayerGamerTags += FString(", " + PlayCont->GetGamerTag());
					}
				}
			}
		}

		LeaderBoard.Add(FLeaderBoardEntry(PlayerGamerTags, SessionScore));
		SeverLeaderBoard(MaxLeaderBoardSlots);
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, "ERROR!!! Was not able to find Game Mode before updating leaderboard.");
	}
	
}

void UENTGameInstance::SortLeaderBoard()
{
	LeaderBoard.Sort([](const FLeaderBoardEntry& LHS, const FLeaderBoardEntry& RHS)
	{
		return LHS.Score > RHS.Score;
	});
}

void UENTGameInstance::SeverLeaderBoard(int CutOffIndice)
{
	SortLeaderBoard();
	
	for (int i = LeaderBoard.Num(); i > CutOffIndice; i--)
	{
		LeaderBoard.Pop(true);
	}

	/*for (int i = 0; i < LeaderBoard.Num(); i++)
	{
		FString PrintString = LeaderBoard[i].Team + " : " + FString::FromInt(LeaderBoard[i].Score);
		UKismetSystemLibrary::PrintString(this, PrintString);
	}*/
}
