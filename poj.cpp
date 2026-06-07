#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cctype>

using namespace std;

class HangmanGame
{
private:
    string word;
    string hint;
    string category;
    string guessedWord;
    vector<char> guessedLetters;

    int attempts;
    int score;
    int highScore;

public:
    HangmanGame()
    {
        score = 0;
        highScore = 0;
        attempts = 7;
    }

    void chooseDifficulty()
    {
        int choice;

        cout << "\n===== Difficulty Level =====\n";
        cout << "1. Easy\n";
        cout << "2. Medium\n";
        cout << "3. Hard\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1)
            attempts = 10;
        else if(choice == 2)
            attempts = 7;
        else if(choice == 3)
            attempts = 5;
        else
        {
            attempts = 7;
            cout << "Invalid choice. Medium selected.\n";
        }
    }

    void selectWord()
    {
        string words[10] =
        {
            "football",
            "ronaldo",
            "kathmandu",
            "avatar",
            "computer",
            "python",
            "tokyo",
            "cricket",
            "einstein",
            "inception"
        };

        string categories[10] =
        {
            "Sports",
            "Personality",
            "City",
            "Movie",
            "Technology",
            "Technology",
            "City",
            "Sports",
            "Personality",
            "Movie"
        };

        string hints[10] =
        {
            "Most popular sport",
            "Famous football player",
            "Capital of Nepal",
            "Highest grossing movie",
            "Electronic machine",
            "Programming language",
            "Capital of Japan",
            "Bat and ball game",
            "Theory of relativity",
            "Dream based movie"
        };

        srand((unsigned)time(NULL));

        int index = rand() % 10;

        word = words[index];
        category = categories[index];
        hint = hints[index];

        guessedWord = "";

        int i;
        for(i = 0; i < word.length(); i++)
        {
            guessedWord += "_";
        }

        cout << "\nCategory: " << category << endl;
    }

    bool alreadyGuessed(char letter)
    {
        int i;

        for(i = 0; i < guessedLetters.size(); i++)
        {
            if(guessedLetters[i] == letter)
                return true;
        }

        return false;
    }

    void displayGame()
    {
        int i;

        cout << "\n-----------------------------\n";
        cout << "Word: ";

        for(i = 0; i < guessedWord.length(); i++)
        {
            cout << guessedWord[i] << " ";
        }

        cout << "\nAttempts Left: " << attempts;
        cout << "\nScore: " << score;

        cout << "\nGuessed Letters: ";

        for(i = 0; i < guessedLetters.size(); i++)
        {
            cout << guessedLetters[i] << " ";
        }

        cout << "\n-----------------------------\n";
    }

    void showHint()
    {
        cout << "\nHint: " << hint << endl;
    }

    void guessLetter()
    {
        char letter;
        bool found = false;

        cout << "Enter a letter: ";
        cin >> letter;

        letter = tolower(letter);

        if(alreadyGuessed(letter))
        {
            cout << "You already guessed that letter.\n";
            return;
        }

        guessedLetters.push_back(letter);

        int i;
        for(i = 0; i < word.length(); i++)
        {
            if(word[i] == letter)
            {
                guessedWord[i] = letter;
                found = true;
            }
        }

        if(found)
        {
            cout << "Correct Guess!\n";
            score += 10;
        }
        else
        {
            cout << "Wrong Guess!\n";
            attempts--;
        }
    }

    bool won()
    {
        return guessedWord == word;
    }

    bool lost()
    {
        return attempts <= 0;
    }

    void result()
    {
        cout << "\n=============================\n";

        if(won())
        {
            score += attempts * 5;

            cout << "CONGRATULATIONS!\n";
            cout << "You Won!\n";
        }
        else
        {
            cout << "Game Over!\n";
            cout << "You Lost!\n";
        }

        cout << "Correct Word: " << word << endl;
        cout << "Final Score : " << score << endl;

        if(score > highScore)
            highScore = score;

        cout << "High Score  : " << highScore << endl;

        cout << "=============================\n";
    }

    void play()
    {
        chooseDifficulty();
        selectWord();

        char hintChoice;

        while(!won() && !lost())
        {
            displayGame();

            cout << "Need Hint? (y/n): ";
            cin >> hintChoice;

            if(hintChoice == 'y' || hintChoice == 'Y')
            {
                showHint();
            }

            guessLetter();
        }

        result();
    }
};

int main()
{
    char again;

    cout << "=====================================\n";
    cout << "       HANGMAN GAME SYSTEM\n";
    cout << "=====================================\n";

    do
    {
        HangmanGame game;
        game.play();

        cout << "\nPlay Again? (y/n): ";
        cin >> again;

    } while(again == 'y' || again == 'Y');

    cout << "\nThank You For Playing!\n";

    return 0;
}