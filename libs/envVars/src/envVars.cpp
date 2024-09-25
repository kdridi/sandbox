#include <core/envVars/envVars.h>

#include <spdlog/spdlog.h>

#include <cassert>
#include <map>

namespace core {
    class EnvVarsImpl : public EnvVars {
    public:
        virtual void init(int argc, const char *argv[], const char *envp[]) override final;
        std::optional<std::string> get(const std::string &_name) const override final;

    private:
        bool m_initialized{false};
        std::map<std::string, std::string> m_envMap{};
    };

    void EnvVarsImpl::init(int argc, const char *argv[], const char *envp[])
    {
        (void)argc;
        (void)argv;

        assert(!m_initialized && "Called twice");
        if (m_initialized) {
            spdlog::warn("EnvVars::initialize() Error -- Called twice");
            return;
        }

        for (int i = 0; envp[i] != nullptr; ++i) {
            std::string envStr{envp[i]};
            auto pos = envStr.find('=');
            if (pos == std::string::npos) {
                spdlog::warn("EnvVars::initialize() Error -- Bad Argument: {}", envStr);
                continue;
            }

            m_envMap.emplace(envStr.substr(0, pos), envStr.substr(pos + 1));
        }

        m_initialized = true;
    }

    std::optional<std::string> EnvVarsImpl::get(const std::string &_name) const
    {
        auto it = m_envMap.find(_name);
        if (it == m_envMap.end())
            return std::nullopt;

        return it->second;
    }

    EnvVars &EnvVars::GetInstance()
    {
        static EnvVarsImpl instance;
        return instance;
    }

    core::Module::Registerer<core::EnvVars> registerer;
} // namespace core
