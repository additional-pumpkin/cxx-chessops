#include "log.hxx"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace chessops
{
    std::shared_ptr<spdlog::logger> log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> log::s_ClientLogger;

    void log::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("CHESSOPS");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
    
} // namespace chessops
