#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include "JetApplication.hpp"


int main() {
    JetApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
