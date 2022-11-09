#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>

namespace chessops {

    class log
    {
    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

} // namespace chessops

// Core log macros
#define CHESSOPS_CORE_TRACE(...)    ::chessops::log::GetCoreLogger()->trace(__VA_ARGS__)
#define CHESSOPS_CORE_INFO(...)     ::chessops::log::GetCoreLogger()->info(__VA_ARGS__)
#define CHESSOPS_CORE_WARN(...)     ::chessops::log::GetCoreLogger()->warn(__VA_ARGS__)
#define CHESSOPS_CORE_ERROR(...)    ::chessops::log::GetCoreLogger()->error(__VA_ARGS__)
#define CHESSOPS_CORE_CRITICAL(...)    ::chessops::log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define CHESSOPS_TRACE(...)	      ::chessops::log::GetClientLogger()->trace(__VA_ARGS__)
#define CHESSOPS_INFO(...)	      ::chessops::log::GetClientLogger()->info(__VA_ARGS__)
#define CHESSOPS_WARN(...)	      ::chessops::log::GetClientLogger()->warn(__VA_ARGS__)
#define CHESSOPS_ERROR(...)	      ::chessops::log::GetClientLogger()->error(__VA_ARGS__)
#define CHESSOPS_CRITICAL(...)	      ::chessops::log::GetClientLogger()->critical(__VA_ARGS__)
