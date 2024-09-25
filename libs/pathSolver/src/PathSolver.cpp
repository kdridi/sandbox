#include <core/pathSolver/pathSolver.h>

#include <spdlog/spdlog.h>

#include <filesystem>
#include <optional>

namespace core {

    class PathSolverImpl : public PathSolver {
    private:
        std::optional<std::filesystem::path> m_execPath;

    public:
        PathSolverImpl() = default;
        ~PathSolverImpl();

        void init(int argc, const char *argv[], const char *envp[]) override final;

        std::filesystem::path solve(const std::filesystem::path &_path) override final;
    };

    PathSolverImpl::~PathSolverImpl()
    {
        if (m_execPath)
            m_execPath = {};
    }

    void PathSolverImpl::init(int argc, const char *argv[], const char *envp[])
    {
        (void)envp;

        auto parsePath = [=]() -> const char * {
            if (argc == 0)
                return nullptr;
            return *argv;
        };

        assert(!m_execPath && "Called twice");
        if (m_execPath) {
            spdlog::warn("PathSolver::initialize() Error -- Called twice");
            return;
        }

        const char *path = parsePath();
        assert(path != nullptr && "Bad Argument");
        if (path == nullptr) {

            spdlog::warn("PathSolver::initialize() Error -- Bad Argument");
            return;
        }

        m_execPath = std::filesystem::absolute(path).parent_path();
        spdlog::info("PathSolver::initialize() Executable path: {}", m_execPath->string());
    }

    std::filesystem::path PathSolverImpl::solve(const std::filesystem::path &_path)
    {
        assert(m_execPath && "Not initialized");
        if (!m_execPath) {
            spdlog::warn("PathSolver::solve() Error -- Not initialized");
            return {};
        }

        return *m_execPath / _path;
    }

    PathSolver &PathSolver::GetInstance()
    {
        static PathSolverImpl instance;
        return instance;
    }

    core::Module::Registerer<core::PathSolver> registerer;
} // namespace core
