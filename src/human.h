#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Human: public Player {
    private:
       

    public:
        Human(int mode);

        vector<pair<pair<int,int>,pair<int,int>>> auto_place_ships();
        vector<pair<pair<int,int>,pair<int,int>>> place_ships();
        
        pair<int,int>  take_shot_coords();
};
#endif
