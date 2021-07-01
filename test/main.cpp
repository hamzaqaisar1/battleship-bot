#include <iostream>
#include <string>
#include "../src/human.h"
#include "../src/bot.h"


int Player::ship_sizes[5] = {1,2,2,3,4};
string Player::ship_names[5] = {"DEST","SUBM","CRUS","BATT","CARR"};
string Player::ship_full_names[5] = {"Destroyer","Submarines","Cruiser","Battleship","Carrier"};



int main(int argc,char* argv[]){
    srand(time(NULL));
    Bot bot_player;
    bot_player.display_my_map();
    
    Human human_player(0);
    int turn,end;
    if(rand() % 2 == 0 ){
        turn = 0;
        cout << "First turn is of the Bot" << endl;
        cout << "Enter to continue: ";
        getchar();
    } else {
        turn = 1;
        cout << "The player gets the first shot" << endl;
        cout << "Enter to continue: ";
        getchar();
    }
    while(1){
        pair<int,int> shot_coords;
        bool hit;
        if(turn == 0){
            turn = 1;
            int ships_alive = human_player.ship_down_ids.size();
            shot_coords = bot_player.determine_shot_coords();

            cout << "The bot has fired at " << shot_coords.first << "," << shot_coords.second << " point on your map" << endl;
            cout << "Enter to continue: ";
            getchar();
            cout << "\n\n";
            hit = human_player.check_if_hit(shot_coords);

            //If bots hits push to hits_to_process and coords_hit vector
            if(hit){
                vector<pair<int,int>> hits_to_process = bot_player.get_hits_to_process();
                hits_to_process.push_back(shot_coords);
                bot_player.coords_hit.push_back(shot_coords);
                cout << "You've been Hit!!!" << endl;
                cout << "Enter to continue: ";
                getchar();
                cout << "\n\n";
                if(ships_alive < human_player.ship_down_ids.size()){
                    cout << "Your " << Player::ship_full_names[human_player.ship_down_ids.back()] << " is down" << endl;
                    cout << "Enter to continue: ";
                    getchar();
                    cout << "\n\n";
                }
            } else {
                cout << "The opponent missed" << endl;
                cout << "Enter to continue: ";
                getchar();
                cout << "\n\n";
                bot_player.coords_shot.push_back(shot_coords);
            }
            
            

            if(bot_player.ship_down_ids.size() == 5){
                end = 1;
                break;
            }
        } else {
            turn = 0;
            int sentinel;
            bool restart = false;
            while(1){
                string buffer;
                cout << "Enter the number corresponding to the action you want performed: "<<endl;
                cout << "1: Display your map" << endl;
                cout << "2: Display opponent's map" << endl;
                cout << "3: Replay" << endl;
                cout << "-1: Keep playing" << endl;
                cout << "Type the number here: ";
                getline(cin,buffer,'\n');
                sentinel = stoi(buffer);

                if(sentinel == 1){
                    human_player.display_my_map();
                } else if(sentinel == 2){
                    human_player.display_opp_map();
                } else if(sentinel == 3){   
                    restart = true;
                    break;
                } else if(sentinel == -1){
                    break;
                }
            }
            if(restart){
                bot_player.place_ships();
                human_player.place_ships();
                if(rand() % 2 == 0){
                    turn = 0;
                    cout << "First turn is of the Bot" << endl;
                    cout << "Enter to continue: ";
                    getchar();
                    cout << "\n\n";
                } else {
                    turn = 1;
                    cout << "The player gets the first shot" << endl;
                    cout << "Enter to continue: ";
                    getchar();
                    cout << "\n\n";
                }
                continue;

            }
            shot_coords = human_player.take_shot_coords();
            hit = bot_player.check_if_hit(shot_coords);

            if(hit){
                cout << "Nice Shot!!" << endl;
                cout << "Enter to continue: ";
                getchar();
                cout << "\n\n";
                human_player.coords_hit.push_back(shot_coords);
            } else {
                cout << "You missed!!" << endl;
                cout << "Enter to continue: ";
                getchar();
                cout << "\n\n";
                human_player.coords_shot.push_back(shot_coords);
            }

            if(human_player.ship_down_ids.size() == 5){
                end = 0;
                break;
            }
        }

    }

    if(end == 0){
        cout << "You won!!!!" << endl;
        cout << "Enter to finish: ";
        getchar();
        cout << "\n\n";
    } else {
        cout << "You lost!!!!" << endl;
        cout << "Enter to finish: ";
        getchar();
        cout << "\n\n";
    }

}