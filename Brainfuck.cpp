#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>

#define IDI_APP_ICON 101

void runBrainfuck(const std::string& code) {
    std::vector<unsigned char> memory(30000, 0); // 30.000 Zellen
    size_t ptr = 0; // Datenzeiger
    std::stack<size_t> loopStack;

    for (size_t i = 0; i < code.length(); ++i) {
        switch (code[i]) {
        case '>': ++ptr; break;
        case '<': --ptr; break;
        case '+': ++memory[ptr]; break;
        case '-': --memory[ptr]; break;
        case '.': std::cout << memory[ptr]; break;
        case ',': std::cin >> memory[ptr]; break;

        case '[':
            if (memory[ptr] == 0) {
                int openBrackets = 1;
                while (openBrackets > 0 && ++i < code.length()) {
                    if (code[i] == '[') ++openBrackets;
                    else if (code[i] == ']') --openBrackets;
                }
            }
            else {
                loopStack.push(i);
            }
            break;

        case ']':
            if (memory[ptr] != 0) {
                i = loopStack.top();
            }
            else {
                loopStack.pop();
            }
            break;

        default:
            // Ignoriere alle anderen Zeichen (z. B. Kommentare)
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: bf <file.bf>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << "\n";
        return 1;
    }

    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    runBrainfuck(code);

    std::cout << "\n\n[Program ended] Press Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // für vorherige Eingabe
    std::string pause;
    std::getline(std::cin, pause);
    return 0;
}

