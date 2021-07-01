#include "bot.h"
#include <ctime>
#include <cstdlib>

using namespace std;

Bot::Bot(){
    this->ship_coords = place_ships();
} 

void Bot::set_targets(pair<int,int> hit_coords){
    this->target_mode = true;
    if(hit_coords.first != 1){
        this->targets.push_back(pair<int,int> (hit_coords.first - 1,hit_coords.second));
    }
    if(hit_coords.first != 10){
        this->targets.push_back(pair<int,int> (hit_coords.first + 1,hit_coords.second));
    }
    if(hit_coords.second != 1){
        this->targets.push_back(pair<int,int> (hit_coords.first,hit_coords.second - 1));
    }
    if(hit_coords.second != 10){
        this->targets.push_back(pair<int,int> (hit_coords.first,hit_coords.second + 1));    
    }
    hits_to_process.pop_back();
}

void Bot::set_hits_to_process(vector<pair<int,int>> hits_to_process){
    this->hits_to_process = hits_to_process;
}


vector<pair<int,int>> Bot::get_hits_to_process(){
    return this->hits_to_process;
}

pair<int,int> Bot::determine_shot_coords(){
    srand(time(NULL));

    pair<int,int> shot_coords;
    if(this->targets.empty() && this->hits_to_process.empty()){
        this->target_mode = false;
    } else if(this->targets.empty() && !this->hits_to_process.empty()){
        this->set_targets(this->hits_to_process.back());
    }
    if(!this->target_mode){
        bool is_valid = false;
        while(!is_valid){
            shot_coords = pair<int,int> (rand() % 10 + 1,rand() % 10 + 1);
            if(find(this->coords_shot.begin(),this->coords_shot.end(),shot_coords) != this->coords_shot.end() ||
                find(this->coords_hit.begin(),this->coords_hit.end(),shot_coords) != this->coords_hit.end() ||
                (shot_coords.first % 2 == 0 && shot_coords.second % 2 != 1) || 
                (shot_coords.first % 2 == 1 && shot_coords.second % 2 != 0)){
                    continue;
            }
            is_valid = true;
        }
    } else {
        
        if(!this->targets.empty()){
            shot_coords = this->targets.back();
        } else if(this->targets.empty() && this->hits_to_process.empty()){
            this->target_mode = false;
            shot_coords = this->determine_shot_coords();
        } else if(this->targets.empty() && !this->hits_to_process.empty()){
            this->set_targets(this->hits_to_process.back());
            shot_coords = this->determine_shot_coords();
        }
        while(1){
            if(find(this->coords_shot.begin(),this->coords_shot.end(),shot_coords) != this->coords_shot.end() ||
                    find(this->coords_hit.begin(),this->coords_hit.end(),shot_coords) != this->coords_hit.end()){
                    this->targets.pop_back();
                    if(!this->targets.empty()){
                        shot_coords = *(this->targets.end() - 1);
                    } else {
                        break;
                    }
            } else {
                break;
            }
        }
        
    } 
    return shot_coords;
}



vector<pair<pair<int,int>,pair<int,int>>> Bot::place_ships(){
    vector<pair<pair<int,int>,pair<int,int>>> coords;
    srand(time(NULL));

    for(int i = 0;i < 5;i++){
        pair<int,int> start = pair<int,int> (rand() % 10 + 1,rand() % 10 + 1);
        pair<int,int> end;
        int curr_ship_size;
        if((rand() % 2) + 1 == 1){
            end = pair<int,int> (start.first,10 - start.second >= Player::ship_sizes[i] ? start.second +  Player::ship_sizes[i] : start.second -  Player::ship_sizes[i]);
            curr_ship_size = start.second - end.second;
        } else {
            end = pair<int,int> (10 - start.first >=  Player::ship_sizes[i] ? start.first +  Player::ship_sizes[i] : start.first -  Player::ship_sizes[i],start.second);
            curr_ship_size = start.first - end.first;
        }
        cout << Player::ship_names[i] << ": " << start.first << "," << start.second << "\t to: " << end.first << "," << end.second << endl;
        pair<pair<int,int>,pair<int,int>> temp (start,end);
        bool is_occupied = false;
        for(int k = 0;k < coords.size();k++){
            is_occupied = false;
            
            if(coords[k].first == temp.first || coords[k].second == temp.second || coords[k].second == temp.first || coords[k].first == temp.second){
                is_occupied = true;
                break;
            } else {
                if(temp.first.first - temp.second.first == 0){
                    curr_ship_size = temp.second.second - temp.first.second;
                    is_occupied = this->check_if_overlap(curr_ship_size,1,temp.first,coords[k].first,coords[k].second);
                } else {
                    curr_ship_size = temp.second.first - temp.first.first;
                    is_occupied = this->check_if_overlap(curr_ship_size,0,temp.first,coords[k].first,coords[k].second);
                } 
            }
            if(is_occupied){
                break;
            }
        
        }
        if(is_occupied){
            i--;
            continue;
        } else{
            coords.push_back(temp);
        }
    }

    return coords;
}
