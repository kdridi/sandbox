#pragma once

#include <filesystem>
#include <optional>

namespace arykow {
    class PathSolver {
    private:
        std::optional<std::filesystem::path> m_execPath;

        PathSolver() = default;
        ~PathSolver();

    public:
        PathSolver(const PathSolver &) = delete;
        PathSolver &operator=(const PathSolver &) = delete;

        static PathSolver &GetInstance();

        void initialize(int argc, const char *argv[]);

        std::string solve(const std::string &_path);
    };
} // namespace arykow

#define PATH_SOLVER_INIT(argc, argv) arykow::PathSolver::GetInstance().initialize(argc, argv)
#define PATH_SOLVER_SOLVE(path) arykow::PathSolver::GetInstance().solve(path)
