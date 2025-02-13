#pragma once
#include "DKUtil/Hook.hpp"

namespace ModernStaggerLock
{
	using namespace DKUtil::Alias;

	class StaggeredStateCheckPatch
	{
		static constexpr OpCode NOP = 0x90;
		static constexpr OpCode StaggeredCheckNop[6]{ NOP, NOP, NOP, NOP, NOP, NOP };

		// 1-5-97-0 1405FA205
		static constexpr std::uint64_t FuncID = 36700;  //1405fa1b0
		static constexpr std::uint64_t FuncIDAE = 37710;
		static constexpr std::ptrdiff_t Offset = 0x55;
		static constexpr std::ptrdiff_t OffsetAE = 0x54;

	public:
		static void Install()
		{
			const auto funcAddr = REL::RelocationID(FuncID, FuncIDAE).address();
			DKUtil::Hook::WriteData(funcAddr + REL::Relocate(Offset, OffsetAE), &StaggeredCheckNop, sizeof(StaggeredCheckNop), false);
			INFO("{} Done!", __FUNCTION__);
		}

	private:
		StaggeredStateCheckPatch() = delete;
		~StaggeredStateCheckPatch() = delete;
	};
}