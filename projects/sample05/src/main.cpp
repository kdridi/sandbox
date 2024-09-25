#include <core/pathSolver/pathSolver.h>

#include <fstream>
#include <spdlog/spdlog.h>

int main(int argc, const char *argv[], const char *envp[])
{
    MODULES_START(argc, argv, envp);

    std::filesystem::path filePath = PATH_SOLVER_SOLVE("assets/sample.txt");
    spdlog::info("File path: {}", filePath.string());

    std::ifstream file(filePath);
    if (!file.is_open()) {
        spdlog::info("Error while opening file '{}'", filePath.string());
        return EXIT_FAILURE;
    }

    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    spdlog::info("File content: {}", fileContent);

    return EXIT_SUCCESS;
}
