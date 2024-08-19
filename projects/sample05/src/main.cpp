#include "arykow/PathSolver.h"

#include <spdlog/spdlog.h>
#include <fstream>

int main(int argc, const char *argv[])
{
    ARYKOW_PATHSOLVER_INIT(argv[0]);

    std::string filePath = ARYKOW_PATHSOLVER_SOLVE("assets/sample.txt");
    spdlog::info("File path: {}", filePath);

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        spdlog::info("Error while opening file '{}'", filePath);
        return EXIT_FAILURE;
    }

    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    spdlog::info("File content: {}", fileContent);

    return EXIT_SUCCESS;
}
