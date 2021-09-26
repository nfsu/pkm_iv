#pragma once
#include "creature_headers.hpp"

namespace pkm_iv {

	//A helper for all headers combined

	static constexpr usz blockSize = sizeof(CreatureBlock);
	static constexpr usz blockOffsetStart = sizeof(CreatureHeader);
	static constexpr usz blockOffsetEnd = sizeof(CreatureHeader) + blockSize * 4;

	static constexpr usz boxCreatureSize = blockOffsetEnd;
	static constexpr usz partyCreatureSize = boxCreatureSize + sizeof(CreatureBattleStats);

	struct Creature : 
		CreatureHeader, 
		CreatureBlockA, CreatureBlockB, CreatureBlockC, CreatureBlockD,
		CreatureBattleStats
	{
		//Encryption/decryption
	
		static Creature decrypt(Buffer in, bool isInParty);
		void encrypt(Buffer out, bool isInParty) const;

		static inline Creature decrypt(const u8 (&in)[partyCreatureSize]) {
			return decrypt(Buffer(partyCreatureSize, (u8*) in), true);
		}

		static inline Creature decrypt(const u8 (&in)[boxCreatureSize]) {
			return decrypt(Buffer(boxCreatureSize, (u8*) in), false);
		}

		inline void encrypt(u8 (&in)[partyCreatureSize]) const {
			encrypt(Buffer(partyCreatureSize, in), true);
		}

		inline void encrypt(u8 (&in)[boxCreatureSize]) const {
			encrypt(Buffer(boxCreatureSize, in), false);
		}

		//Helper functions

		inline bool isShiny() const {
			return getSValue(owner, ownerSecret) < 8;
		}

		inline bool hasSquareSparkles() const {
			return !getSValue(owner, ownerSecret);
		}
	};
}