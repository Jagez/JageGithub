#include "JageLoadingScreen/Public/JageLoadingScreen.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
//#include "MoviePlayer.h"
#include "SThrobber.h"
#include "Slate.h"
#include "MoviePlayer/Public/MoviePlayer.h"
#include "Blueprint/UserWidget.h"


struct FJageLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	//绘制图片
	FJageLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		//ResourceObject 不可访问，应使用SetResourceObject()
		SetResourceObject(LoadObject<UObject>(nullptr, *InTextureName.ToString()));
	}
	//添加定义
	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (UObject* CacheResourceObect = GetResourceObject())
		{
			Collector.AddReferencedObject(CacheResourceObect);
		}
	}
};


class SJageLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SJageLoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		static const FName LoadingScreenName(TEXT("/Game/G_UI/Pyrrha_Nikos"));

		//just load one image
		LoadingScreenBrush = MakeShareable(new FJageLoadingScreenBrush(LoadingScreenName, FVector2D(1024, 256)));
		
	}
private:
	//加载时的图像刷
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

class FJageLoadingScreenModule : public IJageLoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		LoadObject<UObject>(nullptr, TEXT("/Game/G_UI/Pyrrha_Nikos"));

		if (IsMoviePlayerEnabled())
		{
			//InitScreen();
			//StartInGameLoadingScreen(false, 10.f);
		}
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}
	//开始动画
	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) override
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.bAllowEngineTick = false;
		LoadingScreen.bWaitForManualStop = false;
		LoadingScreen.MinimumLoadingScreenDisplayTime = PlayTime;

// 		static ConstructorHelpers::FClassFinder<UUserWidget> LoadingScreenClass(TEXT("/Game/G_Widget/LoadingScreen"));
// 		UserWidgetClass = LoadingScreenClass.Class;
// 		LoadingScreenWidget = CreateWidget<UUserWidget>(GetWorld(), UserWidgetClass);
// 		TSharedPtr<SWidget> LoadingScreenWidgetPtr = LoadingScreenWidget->TakeWidget();

		LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();			////SNew(SJageLoadingScreen);
		LoadingScreen.MoviePaths.Add("myMp4");
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);


	}

	virtual void StopInGameLoadingScreen() override
	{
		GetMoviePlayer()->StopMovie();
	}

	void InitScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 10.f;
		LoadingScreen.WidgetLoadingScreen = SNew(SJageLoadingScreen);

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
};

IMPLEMENT_GAME_MODULE(FJageLoadingScreenModule, JageLoadingScreen)
