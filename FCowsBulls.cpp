#include "FCowsBulls.h"
#include <iostream>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FCowsBulls::FCowsBulls() { Reset(); }

int32 FCowsBulls::GetCurrentTry() const { return MyCurrentTry; }
int32 FCowsBulls::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FCowsBulls::GetHiddenWord() const { return MyHiddenWord; }
bool FCowsBulls::IsGameWon() const { return bIsGameWon; }

int32 FCowsBulls::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 7}, {5, 9}, {6, 10 } };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FCowsBulls::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

EGuessStatus FCowsBulls::CheckGuessValidity(FString Guess) const
{
	if (!bIsIsogram(Guess)) // if the guess is not an isogram, return error 
	{ 
		return EGuessStatus::Not_Isogram;
	} 
	else if (!bIsLowercase(Guess)) // if guess is not lowercase, return error
	{ 
		return EGuessStatus::Not_Lowercase;
	} 
	else if (Guess.length() > GetHiddenWordLength()) //if guess length is too long, return error
	{ 
		return EGuessStatus::Too_Long; 
	} 
	else if (Guess.length() < GetHiddenWordLength()) //if guess length is too short, return error
	{
		return EGuessStatus::Too_Short;
	} 
	else 
	{ 
		return EGuessStatus::OK; 
	}
}

// recieves a VALID guess, increments try number, and returns count
FBullCowCount FCowsBulls::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	// loop through all letters in the hiddenword
	for (int32 i = 0; i < WordLength; i++) {
		// compare letters against the hidden word
		for (int32 j = 0; j < WordLength; j++) {
			// if they match then
			if (MyHiddenWord[i] == Guess[j]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}			
	}
	
	// check if the game is won
	if (BullCowCount.Bulls == MyHiddenWord.length())
	{
		bIsGameWon = true;
	}

	return BullCowCount;
}

bool FCowsBulls::bIsIsogram(FString Guess) const
{
	if (Guess.length() < 2) { return true; } // treat 0 and 1 letter words as isogram

	TMap<char, bool> LetterSeen;	
	for (char Letter : Guess) // loop through the letters of the word
	{
		Letter = tolower(Letter); // check for all lowercase
		if (LetterSeen[Letter]) { return false; } // check if letter already exists in map
		else { LetterSeen[Letter] = true; } // add letter to map		
	}
	return true; // for example in cases where /0 is entered
}

bool FCowsBulls::bIsLowercase(FString Guess) const
{
	if (Guess.length() < 2) { return true; }

	for (auto Letter : Guess) {
		if (!islower(Letter)) 
		{
			return false;
		}
	}
	return true;
}
