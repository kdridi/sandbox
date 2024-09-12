#include "assets/Loader.h"

#include <fmt/core.h>

int main(int argc, const char *argv[])
{
    ARYKOW_ASSETS_INIT(argc, argv);
    std::vector<uint8_t> data = ARYKOW_ASSETS_LOAD("assets/sample.txt");

    std::string str(data.begin(), data.end());
    fmt::print("'{}'\n", str);

    return EXIT_SUCCESS;
}
