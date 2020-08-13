// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "Engine/GameInstance.h"

#include "Carla/Game/CarlaEngine.h"
#include "Carla/Server/CarlaServer.h"

#include "CarlaGameInstance.generated.h"

class UCarlaSettings;

/// The game instance contains elements that must be kept alive in between
/// levels. It is instantiate once per game.
UCLASS()
class CARLA_API UCarlaGameInstance : public UGameInstance
{
  GENERATED_BODY()

public:

  UCarlaGameInstance();

  ~UCarlaGameInstance();

  UCarlaSettings &GetCarlaSettings()
  {
    check(CarlaSettings != nullptr);
    return *CarlaSettings;
  }

  const UCarlaSettings &GetCarlaSettings() const
  {
    check(CarlaSettings != nullptr);
    return *CarlaSettings;
  }

  // Extra overload just for blueprints.
  UFUNCTION(BlueprintCallable)
  UCarlaSettings *GetCARLASettings()
  {
    return CarlaSettings;
  }

  UFUNCTION(BlueprintCallable)
  UCarlaEpisode *GetCarlaEpisode()
  {
    return CarlaEngine.GetCurrentEpisode();
  }

  void NotifyInitGame()
  {
    CarlaEngine.NotifyInitGame(GetCarlaSettings());
  }

  void NotifyBeginEpisode(UCarlaEpisode &Episode)
  {
    CarlaEngine.NotifyBeginEpisode(Episode);
  }

  void NotifyEndEpisode()
  {
    CarlaEngine.NotifyEndEpisode();
  }

  const FCarlaServer &GetServer() const
  {
    return CarlaEngine.GetServer();
  }

  void SetOpendriveGenerationParameters(
      const carla::rpc::OpendriveGenerationParameters & Parameters) {
    GenerationParameters = Parameters;
  }

  const carla::rpc::OpendriveGenerationParameters&
      GetOpendriveGenerationParameters() const {
    return GenerationParameters;
  }

  void SetMapToLoad(const FString MapName);

  void CheckAndLoadMap(UWorld *world, UCarlaEpisode &Episode);

  bool IsLevelPendingLoad() const {
    return bShouldLoadLevel;
  }

private:

  UPROPERTY(Category = "CARLA Settings", EditAnywhere)
  UCarlaSettings *CarlaSettings = nullptr;

  FCarlaEngine CarlaEngine;

  carla::rpc::OpendriveGenerationParameters GenerationParameters;

  UPROPERTY()
  bool bShouldLoadLevel = false;

  UPROPERTY()
  FString MapToLoad;
};
