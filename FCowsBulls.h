#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Too_Short,
	Too_Long
};

class FCowsBulls 
{
public:
	FCowsBulls();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);


private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool bIsIsogram(FString) const;
	bool bIsLowercase(FString) const;
};