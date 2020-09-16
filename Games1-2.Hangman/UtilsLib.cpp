#include "UtilsLib.h"

template <typename T>
T inputValidator() {
    T value{};
    std::string user_entry;
    bool done{ false };
    do {
        std::cin >> user_entry;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards the input buffer
        std::istringstream iss{ user_entry };
        if (iss >> value) {
            done = true;
        }
        else {
            std::cout << "Incorrect input, please try again: ";
        }
    } while (!done);
    return value;
}

template <typename T>
T inputValidator(const unsigned& len) {
    T value{};
    std::string user_entry;
    bool done{ false };
    do {
        std::cin >> user_entry;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discards the input buffer
        std::istringstream iss{ user_entry };
        if (iss >> value && user_entry.size() == len) {
            done = true;
        }
        else {
            std::cout << "Incorrect input, please try again: ";
        }
    } while (!done);
    return value;
}

template <typename T>
T inputValidatorSpecific(const std::vector<T>& v) {
    bool done{ false };
    T value{};
    do {
        value = inputValidator<T>();
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

char inputValidatorLetter() {
    bool done{ false };
    char value{};
    do {
        value = inputValidator<char>(1);
        value = tolower(value);
        if (isalpha(value)) {
            done = true;
        }
        if (!done) {
            std::cout << "Incorrect input, please try again: ";
        }
    } while (!done);
    return value;
}

std::string inputValidatorPhrase() {
    bool done{ true };
    std::string phrase{ "" };
    do {
        done = true;
        std::getline(cin, phrase);
        for (char& c : phrase) {
            c = tolower(c);
            if (!isalpha(c) && !isspace(c)) {
                done = false;
                break;
            }
        }
        if (!done) {
            std::cout << "Incorrect input, please try again: ";
        }
    } while (!done);
    return phrase;
}