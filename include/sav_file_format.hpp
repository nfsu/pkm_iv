#pragma once
#include "gen_iv_base.hpp"
#include "item.hpp"
#include "creature.hpp"

namespace pkm {

	//Thanks to PPRE for their spec
	//Also thanks to PKHeX for a more clear example

	//Enums and constants

	using SecondsSince2000 = u32;

	enum class Badges : u8 {

		None,

		G4Coal		= 1 << 0,
		G4Forest	= 1 << 1,
		G4Cobble	= 1 << 2,
		G4Fen		= 1 << 3,
		G4Relic		= 1 << 4,
		G4Mine		= 1 << 5,
		G4Icicle	= 1 << 6,
		G4Beacon	= 1 << 7,
		
		G2Zephyr	= 1 << 0,
		G2Hive		= 1 << 1,
		G2Plain		= 1 << 2,
		G2Fog		= 1 << 3,
		G2Storm		= 1 << 4,
		G2Mineral	= 1 << 5,
		G2Glacier	= 1 << 6,
		G2Rising	= 1 << 7,
		
		G1Boulder	= 1 << 0,
		G1Cascade	= 1 << 1,
		G1Thunder	= 1 << 2,
		G1Rainbow	= 1 << 3,
		G1Soul		= 1 << 4,
		G1Marsh		= 1 << 5,
		G1Volcano	= 1 << 6,
		G1Earth		= 1 << 7
	};

	static constexpr time_t unixEpoch2000 = 946684800;
	static constexpr u32 maxMoney = 999'999;

	//Headers

	struct ItemCount {
		ItemId id;
		u16 count;
	};

	static constexpr usz boxCount = 18, creaturesPerBox = 6 * 5, totalCreatures = boxCount * creaturesPerBox;

	struct BoxData {
		u8 creatures[creaturesPerBox][136];
		u8 pad[16];
	};

	union BoxName {
		u16 name[20];
	};

	struct SavFile {

		u8 unknown0[0x34];

		SecondsSince2000 adventureStart;

		u32 unknown1;

		SecondsSince2000 champDate;

		u8 unknown2[0x24];

		u16 trainerName[0x8];

		u16 trainerId, secretId;

		u32 money;

		bool isFemale;
		LanguageId lang;
		Badges badgesG4OrG2;
		u8 avatar;

		u16 unknown3;
		u8 unknown4;
		Badges badgesG1;

		u16 unknown5;
		u16 playTimeHours;

		u8 playTimeMinutes;
		u8 playTimeSeconds;
		u16 unknown6;

		u8 unknown7[8];

		u8 partySize;
		u8 unknown8;
		u16 unknown9;

		u8 party[6][236];

		u8 unknown10[0x644 - 0x620];

		ItemCount items[165];

		ItemCount keyItems[43];
		u8 unknown11[0x20];

		ItemCount tmHms[100];
		ItemCount mail[12];
		ItemCount medicine[40];
		ItemCount berries[64];
		ItemCount balls[24];
		ItemCount battleItems[31];

		u16 registeredItems[2];

		u8 unknown13[0xE44 - 0xDE4];

		SpeciesId starter;
		u8 unknown14[0x1234 - 0xE46];

		u16 mapId;			//0x1234
		u16 unknown27;

		u8 unknown28[0x12B8 - 0x1238];

		u8 dex[(SpeciesId::IEnd + 7) >> 3];
		
		u8 unknown15[0x236E - (0x12B8 + sizeof(dex))];

		u16 posX;
		u16 unknown16;

		u16 posY;
		u16 unknown17;

		u16 posZ;
		u16 unknown18;

		u8 unknown19[0x23BE - 0x237A];

		u16 followerX;
		u16 unknown20;

		u16 followerY;
		u16 unknown21;

		u16 followerZ;
		u16 unknown22;

		u8 unknown23[0xC0D8 - 0x23CA];

		u16 moneyHeldByMom;
		u16 unknown24;

		u8 unknown25[0xF700 - 0xC0DC];

		BoxData boxes[boxCount];
		u8 unknown26[0x21708 - (0xF700 + 4096 * 18)];

		BoxName boxNames[boxCount];
		u8 boxWallpapers[boxCount];

		inline u8 boxWallpaper(u8 i) const {
			u8 b = boxWallpapers[i];
			return b >= 0x10 ? b - 0x10 : b;
		}

		//TODO: Walker, gear, mystery gift, wonderguard flags, daycare, swarm
	};

	static constexpr auto s = sizeof(SavFile::boxes);

	//Helper functions

	inline time_t convertTime(SecondsSince2000 t) {
		return unixEpoch2000 + t;
	}

	inline SecondsSince2000 convertTime(time_t t) {

		if (t < unixEpoch2000 || (t - unixEpoch2000) > u32_MAX)
			EXCEPTION("Invalid time");

		return SecondsSince2000(t - unixEpoch2000);
	}

	WString stringifyEncoded(const u16 *ptr, usz N);

	template<usz N>
	inline WString stringifyEncoded(const u16 (&name)[N]) {
		return stringifyEncoded(name, N);
	}
}