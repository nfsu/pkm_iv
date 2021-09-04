#include "species.hpp"

namespace pkm {

    String SpeciesHelper::toString(SpeciesId id) {
        
        u16 i = u16(id);
        
        String str(3, '0');
        
        str[2] = '0' + (i % 10);
        i /= 10;
        
        str[1] = '0' + (i % 10);
        i /= 10;
        
        str[0] = '0' + (i % 10);
        
        return str;
    }
}