#pragma once

#include <filesystem>
#include <optional>

namespace core {
    class PathSolver {
    public:
        static PathSolver &GetInstance();

        virtual void initialize(int argc, const char *argv[]) = 0;
        virtual std::string solve(const std::string &_path) = 0;
    };
} // namespace core

#define PATH_SOLVER_INIT(argc, argv) core::PathSolver::GetInstance().initialize(argc, argv)
#define PATH_SOLVER_SOLVE(path) core::PathSolver::GetInstance().solve(path)
