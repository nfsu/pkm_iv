#pragma once
#include "creature_enums.hpp"
#include "item.hpp"
#include "gen_iv_base.hpp"

namespace pkm_iv {

    enum class SpeciesEffortYield: u16 {
        Hp = 3,
        Atk = Hp << 2,
        Def = Atk << 2,
        Spd = Def << 2,
        SpAtk = Spd << 2,
        SpDef = SpAtk << 2
    };

    enum class SpeciesGender : u8 {	//Any number inbetween is "Mixed"
        MaleOnly = 0x00,
        FemaleOnly = 0xFE,
        None = 0xFF
    };

    enum class SpeciesLevelUpType : u8 {
        MediumFast,	    //1M
        Erratic,		//.6M
        Fluctuating,	//1.64M
        MediumSlow,	    //1 059 860
        Fast,			//.8M
        Slow			//1.25M
    };

    enum class EggGroup : u8 {
        None, Monster, Water1, Bug, 
        Flying, Field, Fairy, Grass, 
        Humanoid, Water3, Mineral, Amorphous, 
        Water2, Ditto, Dragon, Undiscovered
    };

    enum class SpeciesColorAndFlip : u8 {

        Red, Blue, Yellow, Green,
        Black, Brown, Purple, Gray, 
        White, Pink,

        IsFlipped = 0x80		//If the image is flipped in summary (horizontal)
    };

	struct Species {

        CreatureStats<u8> baseStats;
        TypeId types[2];
        
        u8 catchRate;
        u8 baseXpYield;
        SpeciesEffortYield yield;
        
        ItemId wildItemCommon;
        ItemId wildItemRare;
        
        SpeciesGender gender;
        u8 eggCycles;
        u8 baseHappiness;
        SpeciesLevelUpType levelUpType;
        
        EggGroup eggGroup[2];
        AbilityId ability[2];
        
        u8 safariZoneRate;
        SpeciesColorAndFlip colorAndFlip;
        u16 padding;
        
        u8 moves[(u8(MoveId::TMHMCount) + 7) >> 3];
        u8 pad[3];	//Always 00 00 00

        inline bool notMaleOnly() const {
            return gender >= SpeciesGender::FemaleOnly;
        }

        inline bool isMaleOnly() const {
            return gender == SpeciesGender::MaleOnly;
        }

        inline bool isGenderUndefined() const {
            return gender == SpeciesGender::None;
        }

        inline bool isFemaleOnly() const {
            return gender == SpeciesGender::FemaleOnly;
        }

        inline bool hasDefaultSprite() const {
            return !isMaleOnly() && !isGenderUndefined();
        }

        inline bool hasMaleSprite() const {
            return !isFemaleOnly();
        }

        inline bool flipped() const {
            return u8(colorAndFlip) & u8(SpeciesColorAndFlip::IsFlipped);
        }

        inline bool canLearnMove(MoveId move) const {
            return (moves[u8(move) >> 3] >> (u8(move) & 7)) & 1;
        }
	};

    enum SpeciesId : u16 {

        //Global ids

        I000,
        I001,
        I493 = 493,
        IStart = I001,
        IEnd = I493 + 1,

        //Ids for stats
        //Yes, eggs have stats for some reason?

        Egg = 494,
        Egg490,

        I386_Form1,
        I386_Form2,
        I386_Form3,

        I413_Form1,
        I413_Form2,

        I487_Form1,

        I492_Form1,

        I479_Form1,
        I479_Form2,
        I479_Form3,
        I479_Form4,
        I479_Form5,

        End
    };

    struct SpeciesHelper {
        static String toString(SpeciesId id);
    };
}