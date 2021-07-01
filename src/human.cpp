#include "human.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

Human::Human(int mode){
    if(mode == 0){
        this->ship_coords = this->auto_place_ships();
    } else {
        this->ship_coords = this->place_ships();

    }

}

vector<pair<pair<int,int>,pair<int,int>>> Human::auto_place_ships(){
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


vector<pair<pair<int,int>,pair<int,int>>> Human::place_ships(){
    vector<pair<pair<int,int>,pair<int,int>>> coords;
    string buffer;
    string delimiter = ",";
    cout << "Enter the co-ordiniates for your ships as you are prompted to: "<< endl;


    for(int i = 0;i < 5;i++){
        pair<int,int> start;
        
        cout << "Enter the starting co-ordinates of the " << Player::ship_full_names[i] << " (Size = " <<  Player::ship_sizes[i] + 1 << ")"  << " separated by comma: ";
        getline(cin,buffer,'\n');

        if(!(sscanf(buffer.substr(0, buffer.find(delimiter)).c_str(), "%d", &start.first) == 1 && 
            sscanf(buffer.substr(buffer.find(delimiter)+1,buffer.size()).c_str(), "%d", &start.second) == 1)) {
            cout << "Bad Input\n Try Again... \n\n";
            cout << "1";
            i -= 1;
            continue;
        }
        if(start.first > 10 || start.first < 1 || start.second > 10 || start.second < 1){
            cout << "Bad Input\n Try Again... \n\n";
            cout << "2";
            i -= 1;
            continue;
        }

        pair<int,int> end;

        cout << "Enter the ending co-ordinates of the " << Player::ship_full_names[i] << " separated by comma: ";
        getline(cin,buffer,'\n');

        if(!(sscanf(buffer.substr(0, buffer.find(delimiter)).c_str(), "%d", &end.first) == 1  && 
            sscanf(buffer.substr(buffer.find(delimiter)+1,buffer.size()).c_str(), "%d", &end.second) == 1)) {
            cout << "Bad Input\n Try Again... \n\n";
            cout << "3";
            i -= 1;
            continue;
        }
        if(end.first > 10 || end.first < 1 || end.second > 10 || end.second < 1 || 
            start.first - end.first > Player::ship_sizes[i] || start.second - end.second > Player::ship_sizes[i]){
            cout << "Bad Input\n Try Again... \n\n";
            cout << "4";
            i -= 1;
            continue;
        }
        if(start.first != end.first && start.second != end.second){
            cout << "Bad Input\n Try Again... \n\n";
            cout << "5";
            i -= 1;
            continue;
        }


        int curr_ship_size;
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
            cout << "Bad Input\n Try Again... \n\n";
            cout << "6";
            i -= 1;
            continue;
        } else{
            coords.push_back(temp);
        }
    }
    return coords;
}



pair<int,int> Human::take_shot_coords(){
    string buffer;
    string delimiter = ",";
    bool is_val_correct = false;
    pair<int,int> shot_coords;
    
    cout << "Enter the co-ordinates of your shot separated by comma" << ": ";
    getline(cin,buffer,'\n');

    while(!is_val_correct){
        if((sscanf(buffer.substr(0, buffer.find(delimiter)).c_str(), "%d", &shot_coords.first) == 1 && 
        sscanf(buffer.substr(buffer.find(delimiter)+1,buffer.size()).c_str(), "%d", &shot_coords.second) == 1)) {
            is_val_correct = true;
        } else {
            cout << "Bad Input\n Try Again... \n\n";
        }
    }
    cout << "Shot Taken" << endl;
    return shot_coords;
}

