#pragma once
#include "ntypes.hpp"

#define HGSS_TEXT_NO_SLASH "a/0/2/7"
#define HGSS_TEXT HGSS_TEXT_NO_SLASH "/"

namespace pkm_iv {

	struct HGSS {

		static constexpr c8 species[] = "a/0/0/2";
		static constexpr c8 battleSprites[] = "a/0/0/4";
		static constexpr c8 boxPath[] = "a/0/1/9";
		static constexpr c8 icons[] = "a/0/2/0";
		static constexpr c8 battleSpritesExt[] = "a/1/1/4";
		static constexpr c8 friendlyYOff[] = "a/0/0/5";
		static constexpr c8 opponentYOff[] = "a/1/3/2";
		static constexpr c8 eggMoves[] = "a/0/2/9";

		static constexpr usz paletteLocation = 0xFFC10;
		static constexpr usz paletteSize = 535;

		struct Text {
			static constexpr c8 textBase[]			= HGSS_TEXT_NO_SLASH;
			static constexpr c8 boxUI[]				= HGSS_TEXT "24.*";
			static constexpr c8 boxActions[]		= HGSS_TEXT "25.*";
			static constexpr c8 trainerNames[]		= HGSS_TEXT "27.*";
			static constexpr c8 natures[]			= HGSS_TEXT "34.*";
			static constexpr c8 status[]			= HGSS_TEXT "44.*";
			static constexpr c8 options[]			= HGSS_TEXT "45.*";
			static constexpr c8 battleEffect[]		= HGSS_TEXT "197.*";
			static constexpr c8 itemDesc[]			= HGSS_TEXT "221.*";
			static constexpr c8 itemNames[]			= HGSS_TEXT "222.*";
			static constexpr c8 speciesNames[]		= HGSS_TEXT "237.*";
			static constexpr c8 followerText[]		= HGSS_TEXT "265.*";
			static constexpr c8 locations[]			= HGSS_TEXT "279.*";
			static constexpr c8 events[]			= HGSS_TEXT "280.*";
			static constexpr c8 regions[]			= HGSS_TEXT "281.*";
			static constexpr c8 ribbons[]			= HGSS_TEXT "424.*";
			static constexpr c8 credits[]			= HGSS_TEXT "440.*";
			static constexpr c8 statNames[]			= HGSS_TEXT "443.*";
			static constexpr c8 rivalNames[]		= HGSS_TEXT "445.*";
			static constexpr c8 abilityNames[]		= HGSS_TEXT "720.*";
			static constexpr c8 abilityDescs[]		= HGSS_TEXT "722.*";
			static constexpr c8 trainerClasses[]	= HGSS_TEXT "730.*";
			static constexpr c8 typeNames[]			= HGSS_TEXT "735.*";
			static constexpr c8 moveDescs[]			= HGSS_TEXT "749.*";
			static constexpr c8 moveNames[]			= HGSS_TEXT "750.*";
			static constexpr c8 dexHG[]				= HGSS_TEXT "803.*";
			static constexpr c8 dexSS[]				= HGSS_TEXT "804.*";
			static constexpr c8 dexDppt[]			= HGSS_TEXT "805.*";
			static constexpr c8 dexWeight[]			= HGSS_TEXT "812.*";
			static constexpr c8 dexHeight[]			= HGSS_TEXT "814.*";
			static constexpr c8 dexCategories[]		= HGSS_TEXT "816.*";
		};
	};
}