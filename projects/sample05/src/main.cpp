#include <core/pathSolver/pathSolver.h>

#include <fstream>
#include <spdlog/spdlog.h>

int main(int argc, const char *argv[])
{
    PATH_SOLVER_INIT(argc, argv);

    std::string filePath = PATH_SOLVER_SOLVE("assets/sample.txt");
    spdlog::info("File path: {}", filePath);

    std::ifstream file(filePath);
    if (!file.is_open()) {
        spdlog::info("Error while opening file '{}'", filePath);
        return EXIT_FAILURE;
    }

    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    spdlog::info("File content: {}", fileContent);

    return EXIT_SUCCESS;
}
