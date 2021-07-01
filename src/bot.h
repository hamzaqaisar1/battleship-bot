#ifndef BOT_H
#define BOT_H

#include "player.h"
#include <vector>

class Bot: public Player {
    private:
       vector<pair<int,int>> hits_to_process;
       vector<pair<int,int>> targets;
       bool target_mode;

    public:
        Bot();

        vector<pair<int,int>> get_hits_to_process();
        void set_hits_to_process(vector<pair<int,int>> hits_to_process);

        pair<int,int> determine_shot_coords();
        void set_targets(pair<int,int> hit_coords);
        vector<pair<pair<int,int>,pair<int,int>>> place_ships();
};
#endif
