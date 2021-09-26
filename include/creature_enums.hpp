#pragma once
#include "ntypes.hpp"

namespace pkm_iv {

	enum class TypeId : u8 {
		Normal, Fight, Flying, Poison,
		Ground, Rock, Bug, Ghost,
		Steel, QQQorFairy, Fire, Water, 
		Grass, Electric, Psychic, Ice, 
		Dragon, Dark, Count
	};

	enum class CreatureFlags : u8 {
		None,
		SkipChecksum = 3,
		BadEgg = 4,
		Unused = u8(~7)
	};

	enum class CreatureStat : u8 {
		Hp, Atk, Def,
		Spd, SpAtk, SpDef,
		Count
	};

	template<typename T = u8>
	union CreatureStats {
		T stats[u8(CreatureStat::Count)];
		struct {
			T hp, atk, def;
			T spd, spAtk, spDef;
		};
	};

	enum class CreatureContestStat : u8 {
		Cool, Beauty, Cute,
		Smart, Tough, Sheen,
		Count
	};

	union CreatureContestStats {
		u8 contest[usz(CreatureContestStat::Count)];
		struct {
			u8 cool, beauty, cute;
			u8 smart, tough, sheen;
		};
	};

	enum class CreatureEffects : u8 {
		None,
		AsleepRounds	= 7,
		Poisoned		= 1 << 3,
		Burned			= 1 << 4,
		Frozen			= 1 << 5,
		Paralyzed		= 1 << 6,
		Toxic			= 1 << 7
	};
	
	enum class MoveId : u16 {
	
		First = 0,                              //TM01
		
		TMCount = 92,
		HMCount = 8,
		
		TMStart = First,
		HMStart = First + TMCount,
		TMHMCount = HMStart + HMCount,
		Mask = 31
	};

	enum class CreatureMarkingId : u8 {
		None,
		Circle		= 1 << 0,
		Triangle	= 1 << 1,
		Square		= 1 << 2,
		Heart		= 1 << 3,
		Star		= 1 << 4,
		Diamond		= 1 << 5
	};

	enum class CreatureMetInfo : u8 {
		Level = (1 << 7) - 1,
		FemaleOtGender = 1 << 7
	};

	enum class CreatureIVEggNick : u32 {
		Hp = (1 << 5) - 1,
		Atk = Hp << 5,
		Def = Atk << 5,
		Spd = Def << 5,
		SpAtk = Spd << 5,
		SpDef = SpAtk << 5,
		IsEgg = 1 << 30,
		IsNicknamed = 1_u32 << 31
	};

	enum class CreatureForm : u8 {

		None,

		FatefulEncounter	= 1 << 0,
		Female				= 1 << 1,
		Genderless			= 1 << 2,
		AlternateForms		= u8(~7),

		AlternateFormShift	= 3
	};

	enum class CreatureLeaves : u8 {
		LeavesAE = (1 << 5) - 1,
		LeafCrown = 1 << 5
	};

	enum class CreatureEncounterType : u8 {
		Normal,
		Undefined0,
		TallGrass,
		Undefined1,
		DPEvent, Cave,
		Undefined2,
		Water,
		Undefined3,
		Building,
		Safari,
		Undefined4,
		Gift
	};

	enum class CreatureNature : u8 {

		Hardy, Lonely, Brave, Adamant,
		Naughty, Bold, Docile, Relaxed,
		Impish, Lax, Timid, Hasty,
		Serious, Jolly, Naive, Modest,
		Mild, Quiet, Bashful, Rash,
		Calm, Gentle, Sassy, Careful,
		Quirky, 

		Count,
		Mask = 31
	};
}