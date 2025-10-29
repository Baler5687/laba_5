#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <limits>

static std::string trim(const std::string &s) {
    size_t i = 0, j = s.size();
    while (i < j && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    while (j > i && std::isspace(static_cast<unsigned char>(s[j-1]))) --j;
    return s.substr(i, j - i);
}

bool getBoolValue() {
    std::string line;
    while (true) {
        std::cout << u8"Введіть булеве (0 або 1): ";
        if (!std::getline(std::cin, line)) { std::cin.clear(); continue; }
        line = trim(line);
        if (line == "0") return false;
        if (line == "1") return true;
        std::cout << u8"Невірне значення. Допустимо лише '0' або '1'." << std::endl;
    }
}

char getCharValue() {
    std::string line;
    while (true) {
        std::cout << u8"Введіть символ (a-f, малі латинські): ";
        if (!std::getline(std::cin, line)) { std::cin.clear(); continue; }
        line = trim(line);
        if (line.size() == 1) {
            char c = line[0];
            if (c >= 'a' && c <= 'f') return c;
        }
        std::cout << u8"Невірний символ. Приймаються лише a..f." << std::endl;
    }
}

float getFloatValue() {
    std::string line;
    while (true) {
        std::cout << u8"Введіть дробове число (крапка): ";
        if (!std::getline(std::cin, line)) { std::cin.clear(); continue; }
        line = trim(line);
        if (line.empty()) { std::cout << u8"Порожній ввід заборонено." << std::endl; continue; }

        std::istringstream iss(line);
        float v;
        char extra;
        if (iss >> v) {
            if (!(iss >> extra)) return v;
        }
        std::cout << u8"Невірний формат. Використовуйте, наприклад, 3.14" << std::endl;
    }
}

short getShortValue() {
    const long MINV = -32767;
    const long MAXV =  32767;
    std::string line;
    while (true) {
        std::cout << u8"Введіть ціле (" << MINV << u8".." << MAXV << u8"): ";
        if (!std::getline(std::cin, line)) { std::cin.clear(); continue; }
        line = trim(line);
        if (line.empty()) { std::cout << u8"Порожній ввід заборонено." << std::endl; continue; }

        std::istringstream iss(line);
        long v;
        char extra;
        if (iss >> v) {
            if (iss >> extra) { std::cout << u8"Зайві символи в рядку." << std::endl; continue; }
            if (v < MINV || v > MAXV) { std::cout << u8"Значення поза діапазоном." << std::endl; continue; }
            return static_cast<short>(v);
        }
        std::cout << u8"Невірний формат цілого числа." << std::endl;
    }
}

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    bool b = getBoolValue();
    std::cout << u8"Отримано булеве: " << (b ? u8"true" : u8"false") << std::endl;

    char ch = getCharValue();
    std::cout << u8"Отримано символ: " << ch << std::endl;

    float f = getFloatValue();
    std::cout << u8"Отримано float: " << f << std::endl;

    short s = getShortValue();
    std::cout << u8"Отримано short: " << s << std::endl;

    return 0;
}
