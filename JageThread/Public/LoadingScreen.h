// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TickableObjectRenderThread.h"
#include "MoviePlayer.h"

/**
 * 
 */
class JAGETHREAD_API FLoadingScreen : public FTickableObjectRenderThread
	, public IGameMoviePlayer
	, public TSharedFromThis<FLoadingScreen>
{
public:
	FLoadingScreen();
	~FLoadingScreen();

	//FTickableObjectRenderThread interface
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;

	/*IGameMoviePlayer interface*/
	virtual void RegisterMovieStreamer(TSharedPtr<IMovieStreamer> InMovieStreamer) override;
	virtual void Initialize(class FSlateRenderer& InSlateRenderer, TSharedPtr<SWindow> RenderTarget = nullptr) override;
	virtual void Shutdown() override;
	virtual void PassLoadingScreenWindowBackToGame() const override;
	virtual void SetupLoadingScreen(const FLoadingScreenAttributes& InLoadingScreenAttributes) override;
	virtual FOnPrepareLoadingScreen& OnPrepareLoadingScreen() override { return OnPrepareLoadingScreenDelegate; }
	virtual bool HasEarlyStartupMovie() const override;
	virtual bool PlayEarlyStartupMovies() override;
	virtual bool PlayMovie() override;
	virtual void StopMovie() override;
	virtual void WaitForMovieToFinish(bool bAllowEngineTick = false) override;
	virtual bool IsLoadingFinished() const override;
	virtual bool IsMovieCurrentlyPlaying() const override;
	virtual bool LoadingScreenIsPrepared() const override;
	virtual void SetupLoadingScreenFromIni() override;
	virtual FString GetMovieName() override;
	virtual bool IsLastMovieInPlaylist() override;

	virtual FOnMoviePlaybackStarted& OnMoviePlaybackStarted() override { return OnMoviePlaybackStartedDelegate; }
	virtual FOnMoviePlaybackFinished& OnMoviePlaybackFinished() override { return OnMoviePlaybackFinishedDelegate; }
	virtual FOnMovieClipFinished& OnMovieClipFinished() override { return OnMovieClipFinishedDelegate; }


	virtual void SetSlateOverlayWidget(TSharedPtr<SWidget> NewOverlayWidget) override;
	virtual bool WillAutoCompleteWhenLoadFinishes() override;

protected:
	bool bTickable;

private:
	FOnPrepareLoadingScreen			OnPrepareLoadingScreenDelegate;
	FOnMoviePlaybackStarted			OnMoviePlaybackStartedDelegate;
	FOnMoviePlaybackFinished		OnMoviePlaybackFinishedDelegate;
	FOnMovieClipFinished			OnMovieClipFinishedDelegate;

	FLoadingScreenAttributes LoadingScreenAttributes;
};
