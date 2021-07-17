// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingScreen.h"

FLoadingScreen::FLoadingScreen()
{
}

FLoadingScreen::~FLoadingScreen()
{
}

void FLoadingScreen::Tick(float DeltaTime)
{
	
}

TStatId FLoadingScreen::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FLoadingScreen, STATGROUP_Tickables);
}

bool FLoadingScreen::IsTickable() const
{
	return bTickable;
}

void FLoadingScreen::RegisterMovieStreamer(TSharedPtr<IMovieStreamer> InMovieStreamer)
{
	
}

void FLoadingScreen::Initialize(class FSlateRenderer& InSlateRenderer, TSharedPtr<SWindow> RenderTarget /*= nullptr*/)
{
	
}

void FLoadingScreen::Shutdown()
{
	
}

void FLoadingScreen::PassLoadingScreenWindowBackToGame() const
{
	
}

void FLoadingScreen::SetupLoadingScreen(const FLoadingScreenAttributes& InLoadingScreenAttributes)
{
	
}

bool FLoadingScreen::HasEarlyStartupMovie() const
{
#if PLATFORM_SUPPORTS_EARLY_MOVIE_PLAYBACK
	return LoadingScreenAttributes.bAllowInEarlyStartup = true;
#else
	return false;
#endif //PLATFORM_SUPPORTS_EARLY_MOVIE_PLAYBACK
}

bool FLoadingScreen::PlayEarlyStartupMovies()
{
	if (true == HasEarlyStartupMovie())
	{
		return true;
	}
	return false;
}

bool FLoadingScreen::PlayMovie()
{
	return true;
}

void FLoadingScreen::StopMovie()
{
	
}

void FLoadingScreen::WaitForMovieToFinish(bool bAllowEngineTick /*= false*/)
{
	
}

bool FLoadingScreen::IsLoadingFinished() const
{
	return true;
}

bool FLoadingScreen::IsMovieCurrentlyPlaying() const
{
	return true;
}

bool FLoadingScreen::LoadingScreenIsPrepared() const
{
	return true;
}

void FLoadingScreen::SetupLoadingScreenFromIni()
{
	
}

FString FLoadingScreen::GetMovieName()
{
	return FString();
}

bool FLoadingScreen::IsLastMovieInPlaylist()
{
	return false;
}

void FLoadingScreen::SetSlateOverlayWidget(TSharedPtr<SWidget> NewOverlayWidget)
{
	
}

bool FLoadingScreen::WillAutoCompleteWhenLoadFinishes()
{
	return false;
}
