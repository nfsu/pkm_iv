#pragma once
#include "gen_iv_base.hpp"
#include "species.hpp"
#include "item.hpp"
#include "ribbons.hpp"
#include "personality_value.hpp"
#include "creature_forms.hpp"

namespace pkm {

	struct CreatureHeader : PersonalityValue {

		CreatureFlags flag;
		u8 pad;
		u16 checksum;

		inline usz shiftValue() const {
			return ((personality & 0x3E000) >> 0xD) % 24;
		}
	};

	//This is post shuffling and encryption

	struct CreatureBlock {
		u8 dat[32];
	};

	struct CreatureBlockA {

		SpeciesId speciesId;
		ItemId heldItem;

		u16 owner;
		u16 ownerSecret;

		u32 xp;

		u8 happinessOrEggSteps;
		AbilityId ability;
		CreatureMarkingId markings;
		LanguageId originLanguage;

		CreatureStats<u8> effort;

		union {
			u8 contest[usz(CreatureContestStat::Count)];
			struct {
				u8 cool, beauty, cute;
				u8 smart, tough, sheen;
			};
		};

		Ribbons1 ribbons1;
	};

	struct CreatureBlockB {

		MoveId moveset[4];

		u8 pp[4];

		u8 ppUps[4];

		CreatureIVEggNick ivEggNick;

		Ribbons0 ribbons0;

		CreatureForm formInfo;
		CreatureLeaves leaves;
		u16 padding;

		PtLocationId eggLocation;
		PtLocationId metLocation;
	};

	struct CreatureBlockC {

		u16 nickname[(0x5E - 0x48) / 2];

		u8 unused;
		GameId gameId;

		Ribbons2 ribbons2;

		u32 pad0;
	};

	struct CreatureBlockD {

		u16 otName[(0x78 - 0x68) / 2];

		c8 dateEggReceived[3];
		c8 dateMet[3];

		DPLocationId eggLocation;
		DPLocationId metLocation;

		u8 pkrs;
		BallId ball;
		CreatureMetInfo metFemaleTrainer;
		CreatureEncounterType encounterType;

		BallExtId ballExt;
		u8 performance;
	};

	struct CreatureBattleStats {

		CreatureEffects effects;
		u8 flags;
		u16 pad0;

		u8 level;
		CapsuleId capsuleId;
		u16 currentHp;

		CreatureStats<u16> stats;

		u8 pad1[0xD4 - 0x9C];
		u8 sealCoordinates[0xEC - 0xD4];
	};
}