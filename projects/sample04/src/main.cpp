#include <fmt/core.h>

#include <filesystem>
#include <fstream>

int main(int argc, const char *argv[])
{
    if (argc == 0)
        return EXIT_FAILURE;

    std::filesystem::path execPath = std::filesystem::absolute(argv[0]).parent_path();
    fmt::print("Executable path: {}\n", execPath.string());

    std::string filePath = (execPath / "assets/sample.txt").string();
    fmt::print("File path: {}\n", filePath);

    std::ifstream file(filePath);
    if (!file.is_open()) {
        fmt::print("Error while opening file '{}'\n", filePath);
        return EXIT_FAILURE;
    }

    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    fmt::print("File content: {}\n", fileContent);

    return EXIT_SUCCESS;
}
