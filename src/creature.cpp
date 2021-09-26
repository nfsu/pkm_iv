#include "creature.hpp"
#include "compression_helper.hpp"

namespace pkm_iv {

	static constexpr u16 blockOrder[] = {
		00123, 00132, 00213, 00231, 00312, 00321,
		01023, 01032, 01203, 01230, 01302, 01320,
		02013, 02031, 02103, 02130, 02301, 02310,
		03012, 03021, 03102, 03120, 03201, 03210
	};

	static constexpr u16 blockOrderReverse[] = {
		00123, 00132, 00213, 00312, 00231, 00321,
		01023, 01032, 02013, 03012, 02031, 03021,
		01203, 01302, 02103, 03102, 02301, 03201,
		01230, 01320, 02130, 03120, 02310, 03210
	};

	static constexpr usz creatureSize[] = {
		sizeof(Creature) - sizeof(CreatureBattleStats),
		sizeof(Creature)
	};

	static_assert(
		blockSize == sizeof(CreatureBlockA) && 
		blockSize == sizeof(CreatureBlockB) && 
		blockSize == sizeof(CreatureBlockC) && 
		blockSize == sizeof(CreatureBlockD)
	);

	Creature Creature::decrypt(Buffer in, bool isInParty) {

		in.requireSize(creatureSize[isInParty]);

		//TODO: Fix

		//Decrypt

		Creature creature{};
		std::memcpy(&creature, in.add(), creatureSize[isInParty]);
		in = Buffer(sizeof(creature), (u8*) &creature);

		auto header = in.at<CreatureHeader>();

		CreatureHeader emptyHeader{};

		if (std::memcmp(&header, &emptyHeader, sizeof(emptyHeader)) == 0)
			return {};

		u32 seed = header.checksum;

		for (usz i = blockOffsetStart; i < blockOffsetEnd; i += 2) {
			seed = nfs::CompressionHelper::generateRandom(seed);
			in.at<u16>(i) ^= u16(seed >> 16);
		}

		if (isInParty) {

			seed = header.personality;

			for (usz i = blockOffsetEnd; i < sizeof(Creature); i += 2) {
				seed = nfs::CompressionHelper::generateRandom(seed);
				in.at<u16>(i) ^= u16(seed >> 16);
			}
		}

		//Unshuffle

		Creature creatureOut{};
		Buffer out = Buffer(sizeof(creatureOut), (u8*) &creatureOut);

		u16 bo = blockOrderReverse[header.shiftValue()];

		out.append(header);
		out.append(in.at<CreatureBlock>(blockOffsetStart + blockSize * ((bo >> 9) & 7)));
		out.append(in.at<CreatureBlock>(blockOffsetStart + blockSize * ((bo >> 6) & 7)));
		out.append(in.at<CreatureBlock>(blockOffsetStart + blockSize * ((bo >> 3) & 7)));
		out.append(in.at<CreatureBlock>(blockOffsetStart + blockSize * ((bo >> 0) & 7)));

		if (isInParty)
			out.append(in.at<CreatureBattleStats>(blockOffsetEnd));

		if (creatureOut.speciesId >= SpeciesId::IEnd)
			EXCEPTION("Invalid creature");

		return creatureOut;
	}

	void Creature::encrypt(Buffer out, bool isInParty) const {

		out.requireSize(creatureSize[isInParty]);

		Buffer outOrigin = out;

		Buffer in = Buffer(sizeof(*this), (u8*) this);	//I promise I won't modify

		//Generate checksum (this data is unencrypted, yay!)

		u16 checkSum = 0;

		for (usz i = blockOffsetStart; i < blockOffsetEnd; i += 2)
			checkSum += out.at<u16>(i);

		out.append(CreatureHeader{
			{ .personality = personality },
			flag,
			pad,
			checksum
		});

		//We shuffle the data

		u16 bo = blockOrder[shiftValue()];

		out.append(in.at<CreatureBlock>(blockOffsetStart + blockSize * ((bo >> 9) & 7)));
		out.append(in.at<CreatureBlock>(blockOffsetStart + blockSize * ((bo >> 6) & 7)));
		out.append(in.at<CreatureBlock>(blockOffsetStart + blockSize * ((bo >> 3) & 7)));
		out.append(in.at<CreatureBlock>(blockOffsetStart + blockSize * ((bo >> 0) & 7)));

		if(isInParty)
			out.append(in.at<CreatureBattleStats>(blockOffsetStart + blockSize * 4));

		//We encrypt it

		u32 seed = checkSum;

		for (usz i = blockOffsetStart; i < blockOffsetEnd; i += 2) {
			seed = nfs::CompressionHelper::generateRandom(seed);
			outOrigin.at<u16>(i) ^= u16(seed);
		}

		if (isInParty) {

			seed = personality;

			for (usz i = blockOffsetEnd; i < sizeof(*this); i += 2) {
				seed = nfs::CompressionHelper::generateRandom(seed);
				outOrigin.at<u16>(i) ^= u16(seed);
			}
		}
	}

}