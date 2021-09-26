#pragma once
#include "ntypes.hpp"
#include <algorithm>

namespace pkm_iv {

	struct TxtHeader {
		u16 num, seed;
	};

	struct TxtStringHeader {
		u32 offset, size;
	};

	inline u32 copyU16ToU32(u16 x) {
		return (u32(x) << 16) | x;
	}

	struct TxtStringHeaderKey : TxtStringHeader {

		u16 key;

		TxtStringHeaderKey(u16 key, u32 offset, u32 size): 
			TxtStringHeader{ offset ^ copyU16ToU32(key), size ^ copyU16ToU32(key) }, key(key) { }
	};

	using NinChar = u16;

	struct TxtEntry {

		WString content;
		u32 entry;

		TxtEntry(u16 e, bool isCompressed, const WString &content):
			entry((u32(isCompressed) << 31) | e), content(content) { }

		inline bool operator<(const TxtEntry &other) const {

			if (other.content.empty() || content.empty())
				return false;

			return content[0] < other.content[0];
		}
	};

	struct Txt {

		TxtHeader header;
		List<TxtEntry> data;

		inline void sort() {
			std::sort(data.begin(), data.end());
		}

		static Txt parse(Buffer b);

		static WString stringifyEncoded(const NinChar *ptr, usz N, bool encodeUndefined = false);
		static WString stringify(NinChar ninText, bool encodeUndefined = false);
	};
}