#include "txt.hpp"
#include <algorithm>

namespace pkm_iv {

	//Shout outs to PPRE once again

	Txt Txt::parse(Buffer b) {

		Buffer beg = b.clone();
		FINALLY(beg.dealloc(););

		auto head = b.consume<TxtHeader>();

		u16 key = u16(head.seed * 0x2FD);

		List<TxtEntry> stArr;

		for (usz i = 0; i < head.num; ++i) {

			//Simple decryption

			TxtStringHeaderKey txt{ 
				u16(key * (i + 1)),
				b.consume<u32>(),
				b.consume<u32>()
			};

			//Decrypt

			Buffer atOff = beg.offset(txt.offset), atOffBeg = atOff;

			u16 keyj = u16(0x91bd3 * (i + 1));

			for (usz j = 0; j < txt.size; ++j) {
				atOff.consume<NinChar>() ^= keyj;
				keyj = u16(keyj + 0x493D);
			}

			//Create string

			WString str;
			str.reserve(txt.size);

			bool compression{};

			//Check if compression and then process str

			NinChar c = atOffBeg.consume<NinChar>();

			List<NinChar> temp;
			u32 cache{}, shift{};

			if (c != 0xF100)
				goto processStr;

			//Compression; basically it stores a bitset of 9 instead of the full 16 bits

			while ((c = atOffBeg.consume<NinChar>()) != u16_MAX) {

				cache |= u32(c) << shift;
				shift += 15;

				do {
					shift -= 9;

					if ((c = cache & 0x1FF) != 0x1FF)
						temp.push_back(c);

					else temp.push_back(u16_MAX);

					cache >>= 9;
				}
				while(shift >= 9);
			}

			atOffBeg = Buffer(temp.size() * sizeof(NinChar), (u8*) temp.data());

			compression = true;

		processStr:

			do {

				static_assert(sizeof(NinChar) == 2, "NinChar expected to = 2");

				if (c == u16_MAX - 1) {		//Encoded instruction in text

					u16 kind = atOffBeg.consume<u16>();
					u16 argc = atOffBeg.consume<u16>();

					WString stringifiedCmd = L"VAR(" + std::to_wstring(kind);

					for (u16 l = 0; l < argc; ++l)
						stringifiedCmd += L"," + std::to_wstring(l);

					str += stringifiedCmd + L")";
					continue;
				}

				str += stringify(c);

			} while ((c = atOffBeg.consume<NinChar>()) != u16_MAX);

			stArr.push_back(TxtEntry(u16(i), compression, str));
		}

		return Txt{
			.header = head,
			.data = stArr
		};
	}
}