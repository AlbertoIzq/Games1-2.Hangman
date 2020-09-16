// Description and draft code
/*
___Description___
Crate the program Hangman
Prompt the player to enter a phrase
That phrase will be hidden by a series of dashes (excluding spaces)
The player can then guess letters. If they guess correctly all the letters that match will be revealed
If they guess incorrectly, then 1 more body part will be added to the gallows
If they lose the gallows should look like this:

 +---+
 |   |
 |   O
 |  /|\
 |  / \
-+-

If the player loses, the word should be revealed
After the game is over the pkayer should be prompted if they want to play again

___How to solve it?___
We need a way of storing the secret phrase
We need a way of storing the hidden phrase (with dashes)
We need a variable that holds the number of guesses left (set to 6 initially)

___Step 1

do {
    playGame
} while (wantToPlayAgain)

 +---+
 |   |
 |
 |
 |
-+-

--e ----

___Step 2

-playGame

secret_phrase = getSecretPhrase()
hidden_phrase = makeHiddenPhrase(secret_phrase)
number_of_guesses_left = 6

do {
    guess = getGuess()
    updateBoard(guess, secret_phrase, hidden_phrase, number_of_guesses_left)
    drawBoard(hidden_phrase)
} while (!gameIsOver(number_of_guesses_left, hidden_phrase)

displayResult(secret_phrase, number_of_guesses_left)

Draw the game

___Step 3

-getSecretPhrase

Prompt the user for the secret phrase
Get the secret phrase

return secret phrase

-makeHiddenPhrase(secret_phrase)

hidden_phrase = Make new Cstring given the length of the secret phrase

for (length of the secret phrase) {
    hidden_phrase[i] = '-'
}

return hidden_phrase

-updateBoard

bool found = false;

for (length of the secret_phrase) {
    if (secret_phrase[i] == guess) {
        hidden_phrase[i] = guess;
    }
}
if (!found) {
    number_of_guesses_left--;
}

-isGameOver(number_of_guesses_left, hidden_phrase)

bool has_dash = false

for (length of the hidden_phrase) {
    if (hidden_phrase[i] == '-') {
        has_dash == true
    }
}

return numbeer_of_guesses_left == 0 || has_dash

___Functions___

*/

#include <iostream>
#include <vector>
#include "UtilsLib.h"

using std::cin;
using std::cout;
using std::endl;

void playGame();
bool wantToPlayAgain();

std::string getSecretPhrase();
std::string createHiddenPhrase(const std::string&);
char getGuess(const int&);
void updateBoard(const int&, const std::string&, std::string&, int&);
void drawBoard(const std::string&, const int&);
bool isGameOver(const std::string&, const std::string&, const int&);
void displayResult(const std::string&, const std::string&);

void clearScreen();

// I don't know why but I had errors if leaving in this function in "Utils.cpp"
template <typename T>
T inputValidatorSpecificValueAndLength(const std::vector<T>& v, const unsigned& len) {
    bool done{ false };
    T value{};
    do {
        value = inputValidator<T>(len);
        for (T element : v) {
            if (value == element) {
                done = true;
                break;
            }
        }
        if (!done) {
            std::cout << "Incorrect input, please try again: ";
        }
    } while (!done);
    return value;
}

int main()
{
    const std::string headline{ "Release date: 05/03/2020\nAuthor: Albertroll\nCopyright-All rights reserved" };
    cout << headline << endl << endl;
    cout << "Welcome to this stupid Hangman game!" << endl << endl;
    do {
        playGame();
    } while (wantToPlayAgain());

    return 0;
}

void playGame() {
    std::string secret_phrase = getSecretPhrase();
    clearScreen();
    std::string hidden_phrase = createHiddenPhrase(secret_phrase);
    int number_guesses_left{ 6 };
    do {
        char user_guess = getGuess(number_guesses_left);
        cout << endl;
        updateBoard(user_guess, secret_phrase, hidden_phrase, number_guesses_left);
        drawBoard(hidden_phrase, number_guesses_left);
        cout << endl;
    } while (!isGameOver(secret_phrase, hidden_phrase, number_guesses_left));
    displayResult(secret_phrase, hidden_phrase);
}

bool wantToPlayAgain() {
    cout << "Do you feel like playing again this mind-blowing game? (y/n): ";
    char user_answer = inputValidatorSpecificValueAndLength<char>(std::vector<char>{'Y', 'N', 'y', 'n'}, 1);
    user_answer = tolower(user_answer);
    bool play_again{ false };
    if (user_answer == 'y') {
        play_again = true;
        cout << endl;
    }
    return play_again;
}

std::string getSecretPhrase() {
    std::string secret_phrase{ "" };
    cout << "Write a dumb secret phrase to guess (only letters and spaces): ";
    secret_phrase = inputValidatorPhrase();
    return secret_phrase;
}

std::string createHiddenPhrase(const std::string& secret_phrase) {
    std::string hidden_phrase{ "" };
    for (char c : secret_phrase) {
        if (isalpha(c))
            hidden_phrase += '_';
        else if (isspace(c))
            hidden_phrase += ' ';
    }
    return hidden_phrase;
}

char getGuess(const int& number_guesses_left) {
    char guess_player{ 0 };
    cout << "Guess one fucking letter of the damn sentence (" << number_guesses_left << " guesses left): ";
    guess_player = inputValidatorLetter();
    return guess_player;
}

void updateBoard(const int& user_guess, const std::string& secret_phrase, std::string& hidden_phrase, int& number_guesses_left) {
    bool guess_OK{ false };
    for (unsigned i{ 0 }; i < secret_phrase.size(); ++i) {
        if (user_guess == secret_phrase.at(i)) {
            hidden_phrase.at(i) = user_guess;
            guess_OK = true;

        }
    }
    if (!guess_OK) {
        number_guesses_left--;
    }
}

void drawBoard(const std::string& hidden_phrase, const int& number_guesses_left) {
    const std::string drawing_6_left{ " +---+\n |   |\n |\n |\n |\n-+-" };
    const std::string drawing_5_left{ " +---+\n |   |\n |   O\n |\n |\n-+-" };
    const std::string drawing_4_left{ " +---+\n |   |\n |   O\n |   |\n |\n-+-" };
    const std::string drawing_3_left{ " +---+\n |   |\n |   O\n |  /|\n |\n-+-" };
    const std::string drawing_2_left{ " +---+\n |   |\n |   O\n |  /|\\\n |\n-+-" };
    const std::string drawing_1_left{ " +---+\n |   |\n |   O\n |  /|\\\n |  /\n-+-" };
    const std::string drawing_0_left{ " +---+\n |   |\n |   O\n |  /|\\\n |  / \\\n-+-" };
    switch (number_guesses_left) {
    case 6:
        cout << drawing_6_left;
        break;
    case 5:
        cout << drawing_5_left;
        break;
    case 4:
        cout << drawing_4_left;
        break;
    case 3:
        cout << drawing_3_left;
        break;
    case 2:
        cout << drawing_2_left;
        break;
    case 1:
        cout << drawing_1_left;
        break;
    case 0:
        cout << drawing_0_left;
        break;
    }
    cout << endl << endl
        << hidden_phrase << endl;
}

bool isGameOver(const std::string& secret_phrase, const std::string& hidden_phrase, const int& number_guesses_left) {
    return hidden_phrase == secret_phrase || number_guesses_left == 0;
}

void displayResult(const std::string& secret_phrase, const std::string& hidden_phrase) {
    if (secret_phrase == hidden_phrase) {
        cout << "You got it, damn it!";
    }
    else {
        cout << "You stupid, fuck off!";
    }
    cout << " The secret phrase was \"" << secret_phrase << "\"" << endl;
}

void clearScreen() {
    std::system("cls");
}

// Teacher solution
/*
const int IGNORE_CHARS = 256;

const char* INPUT_ERROR_STRING = "Input error! Please try again...";

void playGame();
bool wantToPlayAgain();

int getSecretPhrase(char secret_phrase[], int max_length);
char* makeHiddenPhrase(const char* secret_phrase, int secret_phrase_length);
void drawBoard(int number_of_guesses_left, const char* noptr_hidden_phrase);
// We put the parameter as noptr... because the function doesn't own the pointer

char getGuess();

void updateBoard(char guess, char* noptr_hidden_phrase, const char secret_phrase[], int secret_phrase_length, int& number_of_guesses_left);
bool isGameOver(int number_of_guesses_left, const char* noptr_hidden_phrase, int secret_phrase_length);
void displayResult(const char* secret_phrase, int number_of_guesses_left);
char getCharacter(const char* prompt, const char* error);
char getCharacter(const char* prompt, const char* error, const char valid_input[], int valid_input_length);

int main() {
    do {
        playGame();
    } while (wantToPlayAgain());
    return 0;
}

void playGame() {
    const int MAX_LENGTH_OF_SECRET_PHRASE = 256;
    const int MAX_NUMBER_OF_GUESSES = 6;

    char secret_phrase[MAX_LENGTH_OF_SECRET_PHRASE];
    char* optr_hidden_phrase{ nullptr };
    int number_of_guesses_left{ MAX_NUMBER_OF_GUESSES };

    int secret_phrase_length = getSecretPhrase(secret_phrase, MAX_LENGTH_OF_SECRET_PHRASE);
    optr_hidden_phrase = makeHiddenPhrase(secret_phrase, secret_phrase_length);

    drawBoard(number_of_guesses_left, optr_hidden_phrase);

    char guess;

    do {
        guess = getGuess();
        updateBoard(guess, optr_hidden_phrase, secret_phrase, secret_phrase_length, number_of_guesses_left);
        drawBoard(number_of_guesses_left, optr_hidden_phrase);
    } while (!isGameOver(number_of_guesses_left, optr_hidden_phrase, secret_phrase_length));
    displayResult(secret_phrase, number_of_guesses_left);
    delete[] optr_hidden_phrase;


}

char getGuess() {
    return getCharacter("Please input your guess: ", INPUT_ERROR_STRING);
}

void updateBoard(char guess, char* noptr_hidden_phrase, const char secret_phrase[], int secret_phrase_length, int& number_of_guesses_left) {
    bool found = false;
    for (int i{ 0 }; i < secret_phrase_length; ++i) {
        if (tolower(secret_phrase[i]) == guess) {
            noptr_hidden_phrase[i] = secret_phrase[i];
            found = true;
        }
    }
    if (!found) {
        number_of_guesses_left--;
    }
}

bool isGameOver(int number_of_guesses_left, const char* noptr_hidden_phrase, int secret_phrase_length) {
    bool has_dash = false;
    for (int i{ 0 }; i < secret_phrase_length; ++i) {
        if (noptr_hidden_phrase[i] == '-') {
            has_dash = true;
            break;
        }
    }
    return number_of_guesses_left == 0 || !has_dash;
}

void displayResult(const char* secret_phrase, int number_of_guesses_left) {
    if (number_of_guesses_left > 0) {
        cout << "You got it! The phrase was: " << secret_phrase << endl;
    }
    else {
        cout << "You didn't get it... The phrase was: " << secret_phrase << endl;
    }
}

bool wantToPlayAgain() {
    const char valid_inputs[] = {'y', 'n'};
    char response = getCharacter("Would you like to play again? (y/n) ", INPUT_ERROR_STRING);

}

int getSecretPhrase(char secret_phrase[], int max_length) {
    bool failure;
    int length;
    do {
        failure = false;
        cout << "Please enter the secret phrase: ";
        cin.get(secret_phrase, max_length);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(IGNORE_CHARS, '\n');
            cout << INPUT_ERROR_STRING << endl;
            failure = true;
        }
        else {
            length = strlen(secret_phrase);
            if (length == 0) {
                cout << "You must enter a word that's longer than 0 characters! Please try again." << endl;
                failure = true;
            }
        }
    } while (failure);
    return length;
}

char* makeHiddenPhrase(const char* secret_phrase, int secret_phrase_length) {
    char* hidden_phrase = new char[secret_phrase_length + 1];

    for (int i{ 0 }; i < secret_phrase_length; ++i) {
        if (secret_phrase[i] != ' ') {
            hidden_phrase[i] = '-';
        } else {
            hidden_phrase[i] = ' ';
        }
    }
    hidden_phrase[secret_phrase_length] = '\0';
    return hidden_phrase;
}

void drawBoard(int number_of_guesses_left, const char* noptr_hidden_phrase) {
    switch (number_of_guesses_left) {
    case 0:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |  /|\\" << endl;
        cout << " |  / \\" << endl;
        cout << "-+-" << endl;
        break;
    case 1:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |  /|\\" << endl;
        cout << " |  /" << endl;
        cout << "-+-" << endl;
        break;
    case 2:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |  /|\\" << endl;
        cout << " |" << endl;
        cout << "-+-" << endl;
        break;
    case 3:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |  /|" << endl;
        cout << " |" << endl;
        cout << "-+-" << endl;
        break;
    case 4:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |  /" << endl;
        cout << " |" << endl;
        cout << "-+-" << endl;
        break;
    case 5:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |   O" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << "-+-" << endl;
        break;
    case 6:
        cout << " +---+" << endl;
        cout << " |   |" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << "-+-" << endl;
        break;
    default:
        break;
    }
    cout << endl;
    cout << "Secret Phrase: " << noptr_hidden_phrase << endl << endl;
}

char getCharacter(const char* prompt, const char* error) {
    char input;
    bool failure;

    do {
        failure = false;
        cout << prompt;
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(IGNORE_CHARS, '\n');
            cout << error << endl;
            failure = true;
        }
        else {
            cin.ignore(IGNORE_CHARS, '\n');
            if (isalpha(input)) {
                input = tolower(input);
            }
            else {
                cout << error << endl;
                failure = true;
            }
        }
    } while (failure);
    return input;
}

char getCharacter(const char* prompt, const char* error, const char valid_input[], int valid_input_length) {
    char input;
    bool failure;

    do {
        failure = false;
        cout << prompt;
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(IGNORE_CHARS, '\n');
            cout << error << endl;
            failure = true;
        }
        else {
            cin.ignore(IGNORE_CHARS, '\n');
            if (isalpha(input)) {
                input = tolower(input);
                for (int i{ 0 }; i < valid_input_length; ++i) {
                    if (input == valid_input[i]) {
                        return input;
                    }
                }
            }
            cout << error << endl;
            failure = true;
        }
    } while (failure);
    return input;
}
*/
