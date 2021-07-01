#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Player {
        
    public:
        vector<pair<pair<int,int>,pair<int,int>>> ship_coords;
        map<int,vector<pair<int,int>>> ships_hit_points;

        vector<pair<int,int>> opp_shots;
        vector<pair<int,int>> coords_shot;
        vector<pair<int,int>> coords_hit;
        vector<int> ship_down_ids;
        vector<int> opp_ship_down_ids;

        static int ship_sizes[5];
        static string ship_names[5];
        static string ship_full_names[5];

    
        Player(){
            return;
        };
        pair<pair<int,int>,pair<int,int>> get_ship_coords(int ship_id){
            return this->ship_coords[ship_id];
        }

        bool check_if_hit(pair<int,int> shot_coords){
            bool hit = false;
            opp_shots.push_back(shot_coords);
            for(int i = 0; i < this->ship_coords.size();i++){
                if(shot_coords == this->ship_coords[i].first || shot_coords == this->ship_coords[i].second){
                    if(this->ships_hit_points.find(i) != this->ships_hit_points.end()){
                        this->ships_hit_points.find(i)->second.push_back(shot_coords);
                    } else {
                        pair<int,vector<pair<int,int>>> temp(i,{shot_coords});
                        this->ships_hit_points.insert(temp);
                    }
                    if(this->ships_hit_points.find(i)->second.size() == Player::ship_sizes[i] + 1){
                        this->ship_down_ids.push_back(i);
                    }
                    hit = true;
                    break;
                }
                if(i != 0){
                    int size;
                    if(this->ship_coords[i].first.first - this->ship_coords[i].second.first == 0){
                        size = this->ship_coords[i].first.second - this->ship_coords[i].second.second;
                        for(int j = 1;j < size;j++){
                            pair<int,int> comp_coords = this->ship_coords[i].first;
                            comp_coords.second += size;
                            if(comp_coords == shot_coords){
                                if(this->ships_hit_points.find(i) != this->ships_hit_points.end()){
                                    this->ships_hit_points.find(i)->second.push_back(shot_coords);
                                } else {
                                    pair<int,vector<pair<int,int>>> temp(i,{shot_coords});
                                    this->ships_hit_points.insert(temp);
                                }
                                if(this->ships_hit_points.find(i)->second.size() == Player::ship_sizes[i] + 1){
                                    this->ship_down_ids.push_back(i);
                                }
                                hit = true;
                                break;
                            }
                        }
                    } else {
                        size = this->ship_coords[i].first.first - this->ship_coords[i].second.first;
                        for(int j = 1;j < size;j++){
                            pair<int,int> comp_coords = this->ship_coords[i].first;
                            comp_coords.first += size;
                            if(comp_coords == shot_coords){
                                if(this->ships_hit_points.find(i) != this->ships_hit_points.end()){
                                    this->ships_hit_points.find(i)->second.push_back(shot_coords);
                                } else {
                                    pair<int,vector<pair<int,int>>> temp(i,{shot_coords});
                                    this->ships_hit_points.insert(temp);
                                }
                                if(this->ships_hit_points.find(i)->second.size() == Player::ship_sizes[i] + 1){
                                    this->ship_down_ids.push_back(i);
                                }
                                hit = true;
                                break;
                            }
                        }
                    }  

                } else {
                    continue;
                }
                

            }
            return hit;
        }

        bool check_if_overlap(int size,int axis,pair<int,int> start_new,pair<int,int> start_stored,pair<int,int> end_stored){
            bool in_range = false;
            pair<int,int> test_coord = start_new;
            int size_stored,axis_stored;
            if(start_stored.first - end_stored.first == 0){
                size_stored = end_stored.second - start_stored.second;
                axis_stored = 1;
            } else {
                size_stored = end_stored.first - start_stored.first;
                axis_stored = 0;
            }
            if(size > 0){
                while(size != 0){
                    if(axis == 1){
                        test_coord.second += 1;
                    } else {
                        test_coord.first += 1;
                    }
                    if(this->check_if_in_range(size_stored, axis_stored, start_stored, test_coord)){
                        in_range = true;
                        break;
                    }
                    size--;
                }
            } else {
                size = abs(size);
                while(size != 0){
                    if(axis == 1){
                        test_coord.second -= 1;
                    } else {
                        test_coord.first -= 1;
                    }
                    if(this->check_if_in_range(size_stored, axis_stored, start_stored, test_coord)){
                        in_range = true;
                        break;
                    }
                    size--;
                }
            }
            return in_range;

        }
        

        bool check_if_in_range(int size,int axis,pair<int,int> start,pair<int,int> curr_coord){
            bool in_range = false;
            pair<int,int> test_coord = start;
            if(size > 0){
                while(size != 0){
                    if(axis == 1){
                        test_coord.second += 1;
                    } else {
                        test_coord.first += 1;
                    }
                    if(test_coord == curr_coord){
                        in_range = true;
                        break;
                    }
                    size--;
                }
            } else {
                size = abs(size);
                while(size != 0){
                    if(axis == 1){
                        test_coord.second -= 1;
                    } else {
                        test_coord.first -= 1;
                    }
                    if(test_coord == curr_coord){
                        in_range = true;
                        break;
                    }
                    size--;
                }
            }
            return in_range;
        }

        void display_my_map(){
            for(int n = 1;n < 11; n++){
                cout <<"    "<< n<< "    ";
            }
            for(int i = 1;i < 11;i++){
                cout << "\n"<< i;
                for(int j = 1;j < 11;j++){
                    cout <<"  ";
                    pair<int,int> curr_coords (i,j);
                    bool in_range;
                    for(int k = 0;k < 5;k++){
                        in_range = false;
                        if(this->ship_coords[k].first == curr_coords || this->ship_coords[k].second == curr_coords){
                            in_range = true;
                        } else {
                            pair<int,int> test_coord = this->ship_coords[k].first;
                            int size;
                            if(this->ship_coords[k].first.first - this->ship_coords[k].second.first == 0){
                                size = this->ship_coords[k].second.second - this->ship_coords[k].first.second;
                                in_range = check_if_in_range(size,1,this->ship_coords[k].first, curr_coords);
                            } else {
                                size = this->ship_coords[k].second.first - this->ship_coords[k].first.first;
                                in_range = check_if_in_range(size,0,this->ship_coords[k].first, curr_coords);
                            }

                        }

                        if(in_range){
                            if(!this->ships_hit_points.empty() && !this->ships_hit_points[k].empty() && 
                                find(this->ships_hit_points[k].begin(),this->ships_hit_points[k].end(),curr_coords) != this->ships_hit_points[k].end()){
                                    cout << Player::ship_names[k] << "X";
                                    break;
                            } else {
                                cout << Player::ship_names[k];
                                break;

                            }

                        }
                    }

                    if(!this->opp_shots.empty() && 
                        find(this->opp_shots.begin(),this->opp_shots.end(),curr_coords) != this->opp_shots.end()
                        && !in_range){
                            cout << "OpHit";
                    } else if(!in_range){
                        cout << "       ";
                    } else {
                        cout <<"   ";
                    }
                }
                cout << "\n\n";
            }
        }

        void display_opp_map(){
            for(int n = 1;n < 11; n++){
                cout <<"   "<< n<< "   ";
            }
            for(int i = 1;i < 11;i++){
                cout << "\n"<< i;
                for(int j = 1;j < 11;j++){
                    cout <<"  ";
                    pair<int,int> curr_coords (i,j);
                    
                    if(!this->coords_hit.empty() && 
                        find(this->coords_hit.begin(),this->coords_hit.end(),curr_coords) != this->coords_hit.end()){
                            cout << "Hit";
                    } else if(!this->coords_shot.empty() && 
                        find(this->coords_shot.begin(),this->coords_shot.end(),curr_coords) != this->coords_shot.end()){
                            cout << "Miss";
                    } else {
                        cout << "N/A";
                    }
                    cout << "  ";
                }
                cout << "\n\n";
            }
        }
};
#endif
