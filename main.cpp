#include <iostream>
#include <string>
#include "FCowsBulls.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FCowsBulls BCGame; // instantiate a new game (new class)

int main() 
{
	do {
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());
	
	std::cout << "\n\n\n\n\n\n\n";
	return 0;
}

void PrintIntro()
{
	constexpr int32 WORD_LENGTH = 5;
	std::cout << "*******************************************************\n";
	std::cout << "*                                                     *\n";
	std::cout << "*      Welcome to Bulls and Cows, a fun word game.    *\n";
	std::cout << "* Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of? *\n";
	std::cout << "*                                                     *\n";
	std::cout << "*******************************************************\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	BCGame.Reset();

	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 
		
		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop until user gives valid guess
FText GetValidGuess()
{	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;

	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();	
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << " . Enter your guess: ";
		std::getline(std::cin, Guess);

		// Check the validity of the guess and handle response code
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Too_Long:
			std::cout << "Your word was too long. Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Too_Short:
			std::cout << "Your word was too short. Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Your word contained uppercase letters. Please use lowercase only.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

void PrintGameSummary()
{
	int32 NumberOfTries = BCGame.GetCurrentTry() - 1;
	if (BCGame.IsGameWon()) {
		std::cout << "You won the game in " << NumberOfTries << (NumberOfTries == 1 ? " try!" : " tries!") << "\n\n\n";
	}
	else {
		std::cout << "You lost the game. Better luck next time!\n\n\n";
	}
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	return (Response[0] == 'y' || Response[0] == 'Y');
}