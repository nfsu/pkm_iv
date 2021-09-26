#pragma once

namespace pkm_iv {

	enum class Ribbons0 : u32 {

		None,

		Cool			= 1 << 0,
		SuperCool		= 1 << 1,
		HyperCool		= 1 << 2,
		MasterCool		= 1 << 3,

		Beauty			= 1 << 4,
		SuperBeauty		= 1 << 5,
		HyperBeauty		= 1 << 6,
		MasterBeauty	= 1 << 7,

		Cute			= 1 << 8,
		SuperCute		= 1 << 9,
		HyperCute		= 1 << 10,
		MasterCute		= 1 << 11,

		Smart			= 1 << 12,
		SuperSmart		= 1 << 13,
		HyperSmart		= 1 << 14,
		MasterSmart		= 1 << 15,

		Tough			= 1 << 16,
		SuperTough		= 1 << 17,
		HyperTough		= 1 << 18,
		MasterTough		= 1 << 19,

		Champion		= 1 << 20,
		Winning			= 1 << 21,
		Victory			= 1 << 22,
		Artist			= 1 << 23,
		Effort			= 1 << 24,

		Marine			= 1 << 25,
		Land			= 1 << 26,
		Sky				= 1 << 27,
		Country			= 1 << 28,
		National		= 1 << 29,
		Earth			= 1 << 30,
		World			= 1_u32 << 31
	};

	enum class Ribbons1 : u32 {

		None,

		SinnohChampion	= 1 << 0,

		Ability			= 1 << 1,
		GreatAbility	= 1 << 2,
		DoubleAbility	= 1 << 3,
		MultiAbility	= 1 << 4,
		PairAbility		= 1 << 5,
		WorldAbility	= 1 << 6,

		Alert			= 1 << 7,
		Shock			= 1 << 8,
		Downcast		= 1 << 9,
		Careless		= 1 << 10,
		Relax			= 1 << 11,
		Snooze			= 1 << 12,
		Smile			= 1 << 13,
		Gorgeous		= 1 << 14,
		Royal			= 1 << 15,
		GorgeousRoyal	= 1 << 16,

		Footprint		= 1 << 17,
		Record			= 1 << 18,
		History			= 1 << 19,
		Legend			= 1 << 20,

		Red				= 1 << 21,
		Green			= 1 << 22,
		Blue			= 1 << 23,

		Festival		= 1 << 24,
		Carnival		= 1 << 25,
		Classic			= 1 << 26,
		Premier			= 1 << 27
	};

	enum class Ribbons2 : u32 {

		None,

		Cool			= 1 << 0,
		GreatCool		= 1 << 1,
		UltraCool		= 1 << 2,
		MasterCool		= 1 << 3,

		Beauty			= 1 << 4,
		GreatBeauty		= 1 << 5,
		UltraBeauty		= 1 << 6,
		MasterBeauty	= 1 << 7,

		Cute			= 1 << 8,
		GreatCute		= 1 << 9,
		UltraCute		= 1 << 10,
		MasterCute		= 1 << 11,

		Smart			= 1 << 12,
		GreatSmart		= 1 << 13,
		UltraSmart		= 1 << 14,
		MasterSmart		= 1 << 15,

		Tough			= 1 << 16,
		GreatTough		= 1 << 17,
		UltraTough		= 1 << 18,
		MasterTough		= 1 << 19
	};
}