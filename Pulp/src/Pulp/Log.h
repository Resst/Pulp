#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Pulp {
	class PULP_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define PLP_CORE_ERROR(...)		::Pulp::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PLP_CORE_INFO(...)		::Pulp::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PLP_CORE_WARN(...)		::Pulp::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PLP_CORE_TRACE(...)		::Pulp::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PLP_CORE_FATAL(...)		::Pulp::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define PLP_ERROR(...)			::Pulp::Log::GetClientLogger()->error(__VA_ARGS__)
#define PLP_INFO(...)			::Pulp::Log::GetClientLogger()->info(__VA_ARGS__)
#define PLP_WARN(...)			::Pulp::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PLP_TRACE(...)			::Pulp::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PLP_FATAL(...)			::Pulp::Log::GetClientLogger()->fatal(__VA_ARGS__)
