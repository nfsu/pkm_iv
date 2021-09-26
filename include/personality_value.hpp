#pragma once
#include "creature_enums.hpp"
#include "species.hpp"

namespace pkm_iv {

	using u8x2x4 = Array<Array<u8, 2>, 4>;
	using u16x4 = Array<u16, 4>;

	//Unencrypted header data

	struct PersonalityValue {

		union {
			u32 personality;
			u16 p16[2];
			u8 p8[4];
		};

		inline bool isMale(const Species &species) const {

			if (species.notMaleOnly())
				return false;

			if (species.isMaleOnly())
				return true;

			return p8[0] >= u8(species.gender);
		}

		inline bool hasSecondSpeciesAbility() const {
			return personality & 1;
		}

		inline CreatureNature getNature() const {
			return CreatureNature(personality % u8(CreatureNature::Count));
		}

		inline u16 getSValue(u16 trainerId, u16 trainerSecret) const {
			return trainerId ^ trainerSecret ^ p16[1] ^ p16[0];
		}

		inline CreatureStat tieBreaker() const {
			return CreatureStat(personality % u8(CreatureStat::Count));
		}

		inline u8x2x4 spots() const {

			u8x2x4 spots;

			for (u8 i = 0; i < 4; ++i) {
				spots[i][0] = p8[i] & 0xF;
				spots[i][1] = p8[i] >> 4;
			}

			return spots;
		}

		inline bool hasEvolutionConstant() const {
			return p16[1] % 10 < 4;
		}

		//Height in mms
		inline u16 getSize(const CreatureStats<u8> &stats, u32 heightInDms) const {

			CreatureStats sder;
			u8 i{};

			for (const u8 &stat : stats.stats)
				sder.stats[i++] = stat & 0xF;

			static constexpr u16x4 xyzTable[] = {
				{ 9, 290, 1, 0 },
				{ 109, 300, 1, 10 },
				{ 309, 400, 2, 110 },
				{ 709, 500, 4, 310 },
				{ 2709, 600, 20, 710 },
				{ 7709, 700, 50, 2710 },
				{ 17709, 800, 100, 7710 },
				{ 32709, 900, 150, 17710 },
				{ 47709, 1000, 150, 32710 },
				{ 57709, 1100, 100, 47710 },
				{ 62709, 1200, 50, 57710 },
				{ 64709, 1300, 20, 62710 },
				{ 65209, 1400, 5, 64710 },
				{ 65409, 1500, 2, 65210 },
				{ 65535, 1700, 1, 65510 }
			};

			static constexpr usz lastIndex = sizeof(xyzTable) / sizeof(xyzTable[0]) - 1;

			u8 statLine0 = sder.hp * (sder.atk ^ sder.def);
			u8 statLine1 = sder.spd * (sder.spAtk ^ sder.spDef);

			//This can overflow, but that might be intended
			u16 s = 256 * (u16(p8[0] ^ statLine0) + (p8[1] ^ statLine1));

			const u16x4* res = xyzTable + lastIndex;

			for(usz j = 0; j < lastIndex; ++j)
				if (s < xyzTable[j][0]) {
					res = xyzTable + j;
					break;
				}

			const u16x4& xyz = *res;

			u32 h = heightInDms;

			return u16((h * ((s - xyz[3]) / xyz[2] + xyz[1])) / 10);
		}
	};
}