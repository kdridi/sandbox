#include "arykow/assets/Loader.h"

#include <fmt/core.h>
#include <iostream>

#include <physfs.h>
#include <iostream>
#include <filesystem>

int main(int argc, const char *argv[])
{
    ARYKOW_ASSETS_INIT(argv[0]);
    std::vector<uint8_t> data = ARYKOW_ASSETS_LOAD("sample.txt");

    std::string str(data.begin(), data.end());
    fmt::print("'{}'\n", str);

    return EXIT_SUCCESS;
}
