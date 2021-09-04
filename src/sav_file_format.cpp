#include "sav_file_format.hpp"

//Some validation

namespace pkm {
	static_assert(offsetof(SavFile, adventureStart) == 0x34);
	static_assert(offsetof(SavFile, champDate) == 0x3C);
	static_assert(offsetof(SavFile, trainerName) == 0x64);
	static_assert(offsetof(SavFile, trainerId) == 0x74);
	static_assert(offsetof(SavFile, secretId) == 0x76);
	static_assert(offsetof(SavFile, money) == 0x78);
	static_assert(offsetof(SavFile, isFemale) == 0x7C);
	static_assert(offsetof(SavFile, lang) == 0x7D);
	static_assert(offsetof(SavFile, badgesG4OrG2) == 0x7E);
	static_assert(offsetof(SavFile, avatar) == 0x7F);
	static_assert(offsetof(SavFile, badgesG1) == 0x83);
	static_assert(offsetof(SavFile, playTimeHours) == 0x86);
	static_assert(offsetof(SavFile, partySize) == 0x94);
	static_assert(offsetof(SavFile, party) == 0x98);
	static_assert(offsetof(SavFile, party) + sizeof(SavFile::party[0]) == 0x98 + 236);
	static_assert(offsetof(SavFile, items) == 0x644);
	static_assert(offsetof(SavFile, keyItems) == 0x8D8);
	static_assert(offsetof(SavFile, tmHms) == 0x9A4);
	static_assert(offsetof(SavFile, mail) == 0xB34);
	static_assert(offsetof(SavFile, medicine) == 0xB64);
	static_assert(offsetof(SavFile, berries) == 0xC04);
	static_assert(offsetof(SavFile, balls) == 0xD04);
	static_assert(offsetof(SavFile, battleItems) == 0xD64);
	static_assert(offsetof(SavFile, registeredItems) == 0xDE0);
	static_assert(offsetof(SavFile, starter) == 0xE44);
	static_assert(offsetof(SavFile, mapId) == 0x1234);
	static_assert(offsetof(SavFile, dex) == 0x12B8);
	static_assert(offsetof(SavFile, posX) == 0x236E);
	static_assert(offsetof(SavFile, posY) == 0x2372);
	static_assert(offsetof(SavFile, posZ) == 0x2376);
	static_assert(offsetof(SavFile, followerX) == 0x23BE);
	static_assert(offsetof(SavFile, followerY) == 0x23C2);
	static_assert(offsetof(SavFile, followerZ) == 0x23C6);
	static_assert(offsetof(SavFile, moneyHeldByMom) == 0xC0D8);
	static_assert(offsetof(SavFile, boxes) == 0xF700);
	static_assert(offsetof(SavFile, boxNames) == 0x21708);
	static_assert(offsetof(SavFile, boxWallpapers) == 0x219D8);
}