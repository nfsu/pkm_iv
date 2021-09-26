#pragma once
#include "ntypes.hpp"

namespace pkm_iv {

	enum class LanguageId : u8 {
		Undefined,
		Japanese,
		English,
		French,
		Italian,
		German,
		Spanish,
		Korean
	};

	enum class GameId : u8 {

		Undefined0,

		Sapphire, Ruby, Emerald,
		FR, LG,

		Undefined1,

		HG, SS,

		Undefined2,

		Diamond, Pearl, Platinum,

		Undefined3, Undefined4,

		CXD,

		Undefined5, Undefined6, Undefined7, Undefined8,

		White, Black,
		White2, Black2,

		X, Y,

		AS, OR,

		Undefined9, Undefined10,

		Sun, Moon,

		US, UM,

		GO,

		Red, Blue, Green,
		Yellow,

		Gold, Silver,
		Crystal,

		LGP, LGE,

		Sword, Shield
	};

	static constexpr u32 gameCodeHG = 0x004b5049;
	static constexpr u32 gameCodeSS = 0x00475049;

	using BallId = u8;
	using BallExtId = u8;

	using AbilityId = u8;		//Up to 123

	using PtLocationId = u16;
	using DPLocationId = u16;
}