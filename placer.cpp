#include <iostream>

int main(int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        std::iostream << argv[i] << std::endl;
    }
    std::cin.get()
}
