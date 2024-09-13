#include <core/pathSolver/pathSolver.h>

#include <spdlog/spdlog.h>

namespace arykow {
    PathSolver::~PathSolver()
    {
        if (m_execPath)
            m_execPath = {};
    }

    PathSolver &PathSolver::GetInstance()
    {
        static PathSolver instance;
        return instance;
    }

    void PathSolver::initialize(int argc, const char *argv[])
    {
        const char *path = parsePath(argc, argv);

        assert(path != nullptr && "Loader::initialize() path is invalid");
        assert(!m_execPath && "PathSolver::initialize() called twice");
        if (m_execPath) {
            spdlog::warn("PathSolver::initialize() called twice");
            return;
        }

        m_execPath = std::filesystem::absolute(path).parent_path();
        spdlog::info("PathSolver::initialize() Executable path: {}", m_execPath->string());
    }

    std::string PathSolver::solve(const std::string &_path)
    {
        return (*m_execPath / _path).string();
    }

    const char *PathSolver::parsePath(int argc, const char *argv[])
    {
        if (argc == 0)
            return nullptr;
        return *argv;
    }
} // namespace arykow
