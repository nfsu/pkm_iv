#pragma once
#include "ntypes.hpp"

namespace pkm_iv {

	template<usz v>
	struct CreatureFormBase { static constexpr u16 id = u16(v); };

	#define CreatureForm(Id, ...)									\
	struct I##Id##Form : public CreatureFormBase<Id> {				\
		enum E : u8 {												\
			Normal,													\
			__VA_ARGS__,											\
			Count													\
		};															\
		static constexpr E values[] = { __VA_ARGS__ };				\
		static constexpr E allValues[] = { Normal, __VA_ARGS__ };	\
	};

	CreatureForm(172, SpikyEared);
	CreatureForm(351, Sunny, Rainy, Snowy);
	CreatureForm(386, Atk, Def, Spd);
	CreatureForm(412, Sandy, Trash);
	CreatureForm(421, Sunshine);
	CreatureForm(422, East);
	CreatureForm(479, Heat, Wash, Frost, Fan, Mow);
	CreatureForm(487, Origin);
	CreatureForm(492, Sky);

	using I413Form = I412Form;
	using I423Form = I422Form;

	CreatureForm(
		493, 
		Fight, Flying, Poison,
		Ground, Rock, Bug, Ghost,
		Steel, QQQ, Fire, Water, 
		Grass, Electric, Psychic, Ice, 
		Dragon, Dark, Fairy, Anti
	);

	struct I201Form : public CreatureFormBase<201> {
		static constexpr c8 letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
		static constexpr u8 Count = u8(sizeof(letters) - 1);
	};

	//Mapping with magic
	//Might not be pretty or like "good coding standard"
	//but I don't care

	template<typename...>
	struct TFormTypeList {};

	template<usz i, typename A, typename ...args>
	static inline bool FormTypeIsValid(TFormTypeList<A, args...>, u16 type, u8 form) {

		if (type == A::id)
			return form < A::Count;

		if constexpr (bool(sizeof...(args)))
			return FormTypeIsValid<i + 1>(TFormTypeList<args...>{}, type, form);

		else return !form;
	}

	using FormTypeList = TFormTypeList<
		I172Form, I201Form, I351Form, 
		I386Form, I412Form, I413Form, 
		I421Form, I422Form, I423Form, 
		I479Form, I487Form, I492Form, 
		I493Form
	>;

	static inline bool FormTypeIsValid(u16 type, u8 form) {
		return FormTypeIsValid<0>(FormTypeList{}, type, form);
	}
}