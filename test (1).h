#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>


struct Duck {
    int id;
    int position;
    int status;

    Duck(int _id, int _pos = 0, int _sta = 0) : id(_id), position(_pos), status(_sta) {}
};

class Player{
public:

    Action(Board& b, Set_up& a, std::vector<Player>& p) : board(b), setduck(a), players(p) {};


    Player(std::string playername) : _name(playername) {
        for (int i = 0; i < 5; ++i) {
            _ducks.push_back(Duck(i));
            _playerducksdeck.push_back(std::vector<std::string>{playername, std::to_string(i)});
        }
    }

    std::vector<Duck> get_ducks() const { return _ducks; }
    std::string get_name() const { return _name; }
    std::vector<std::string> get_playeractiondeck() const { return _playeractiondeck; }
    std::vector<std::vector<std::string>> get_playerducksdeck() const { return _playerducksdeck; }

    void set_ducks(const std::vector<Duck>& ducks) { _ducks = ducks; }
    void set_name(const std::string& name) { _name = name; }
    void set_playeractiondeck(const std::vector<std::string>& playeractiondeck ) { _playeractiondeck = playeractiondeck ; }
    void set_playerducksdeck(const std::vector<std::vector<std::string>>& playerducksdeck) { _playerducksdeck = playerducksdeck; }

    //เรียกดูข้อมูลผู้เล่น
    void Print_player() const {
        std::cout << "Deck:\n";
        for (const std::string& card : _playeractiondeck) {
        std::cout << "  - " << card << "\n";
        }
    }

    void Take_Aim(int y){action.Take_Aim(y);}
    void Shoot(int y){ action.Shoot(y);} 
    void Hang_Back(int y){action.Hang_Back(y);}
    void Give_Peace_A_Chance() { action.Give_Peace_A_Chance(); }
    void Move_Ahead(int y) { action.Move_Ahead(y); }
    void Misfire(int y) { action.Misfire(y); }
    void Two_Birds(int y) { action.Two_Birds(y); }
    void Resurrection(std::vector<int> target, std::vector<std::string> cards, std::vector<std::string> deck, std::string color) {
        action.Resurrection(target, cards, deck, color);
    }
    void Double_Barrel(std::vector<std::string>& cols, std::vector<std::string>& Status) {
        action.Double_Barrel(cols, Status);
    }
    void Bump_Left_Bump_Right(std::vector<std::string>& cols, std::vector<std::string>& Status) {
        action.Bump_Left_Bump_Right(cols, Status);
    }
    void Fast_Forward(std::vector<std::string>& cols, std::vector<std::string>& Status) {
        action.Fast_Forward(cols, Status);
    }
    void Quick_Shot(std::vector<std::string>& cols, std::vector<std::string>& Status) {
        action.Quick_Shot(cols, Status);
    }


private:
    std::vector<Duck> _ducks;
    std::string _name ;
    std::vector<std::string> _playeractiondeck;
    std::vector<std::vector<std::string>>_playerducksdeck;
};

class Set_up{
public:

    std::vector<std::vector<std::string>> get_ducksdeck() const { return _ducksdeck; }
    std::vector<std::string> get_actiondeck() const { return _actiondeck; }

    void set_ducksdeck(const std::vector<std::vector<std::string>>& ducksdeck) { _ducksdeck = ducksdeck; }
    void set_actiondeck(const std::vector<std::string>& actiondeck) {_actiondeck = actiondeck; }

    //สร้างกองการ์ดเป็ด สำหรับเรียกเข้าสู่สระน้ำ
    void get_allducksfromplayers(const std::vector<Player>& players) {
    _ducksdeck.clear();
    for (const Player& player : players) {
        const std::vector<std::vector<std::string>>& ducks = player.get_playerducksdeck();
        _ducksdeck.insert(_ducksdeck.end(), ducks.begin(), ducks.end());
        }
    }

    //สับกองการ์ดเป็ด 
    void shuffle_ducksdeck() {
        std::random_device rd; 
        std::mt19937 g(rd());   
        std::shuffle(_ducksdeck.begin(), _ducksdeck.end(), g);
    }

    //สับกองการ์ดเเอคชั่น
    void shuffle_actiondeck() {
        std::random_device rd; 
        std::mt19937 g(rd());   
        std::shuffle(_actiondeck.begin(), _actiondeck.end(), g);
    }

    //จั่วการ์ดให้ผู้เล่นคนละ 3 ใบ
    void drawactioncards(std::vector<Player>& players, int cards = 3) {
        for (Player& player : players) {
            std::vector<std::string> playerdeck = player.get_playeractiondeck();
            for (int i = 0; i < cards; ++i) {
                std::string card = _actiondeck.back();
                _actiondeck.pop_back();
                playerdeck.push_back(card);
            }
            player.set_playeractiondeck(playerdeck);
        }
    }

    //setupเริ่มต้นเกมส์
    void setup(std::vector<Player>& players) {
        get_allducksfromplayers(players);
        shuffle_ducksdeck();
        shuffle_actiondeck();
        drawactioncards(players);
    }

private:
    std::vector<std::vector<std::string>> _ducksdeck ={};
    std::vector<std::string> _actiondeck = {"Bump_Left_Bump_Right", "Bump_Left_Bump_Right", "Bump_Left_Bump_Right",
                                            "Take_Aim", "Take_Aim", "Take_Aim", "Take_Aim", "Take_Aim",
                                            "Shoot", "Shoot", "Shoot", "Shoot", "Shoot",
                                            "Give_Peace_A_Chance", "Give_Peace_A_Chance", "Give_Peace_A_Chance",
                                            "Double_Barrel", "Double_Barrel", "Double_Barrel",
                                            "Move_Ahead", "Move_Ahead", "Move_Ahead",
                                            "Fast_Forward", "Fast_Forward", "Fast_Forward",
                                            "Two_Birds", "Two_Birds", "Two_Birds",
                                            "Hang_Back", "Hang_Back", "Hang_Back",
                                            "Quick_Shot", "Quick_Shot", "Quick_Shot",
                                            "Misfire", "Misfire", "Misfire"
                                        }
                                    };
                                        

class Board{
public:
    Board(std::vector<std::string> status, std::vector<std::string> pool)
      : Status(status), Pool(pool) {}

    std::vector<std::string> get_status(){return Status ;}
    std::vector<std::string> get_pool(){return Pool ;}

    void set_status(std::vector<std::string>status){ Status = status ;} 
    void set_pool(std::vector<std::string>pool){ Pool = pool ;} 
    
    std::vector<std::string>* ptrstatus = &Status; 
    std::vector<std::string>* ptrPool = &Pool; 

    void Print() const

    {   
        std::cout << "\n";
        std::cout << "Status:";
        for (const std::string& s : Status)
        {
            std::cout << s << "  ";
        }
        std::cout << "\n";
        std::cout << "Pool:  ";
        for  (const std::string& c : Pool ) 
        {
        std::cout << c << "  ";
        }
        std::cout << "\n";
        std::cout << "\n";
    }

private:   
    std::vector<std::string> Pool;
    std::vector<std::string> Status;
};

class Action{

public:

    Action(Board& b, Set_up& a, std::vector<Player>& p) : board(b), setduck(a), players(p) {}

    /*เล็งเป็ด*/
    void Take_Aim(int y){
   
        if (y>6 || y<1){
            std::cout <<"\n"<< "plase enter number between 1 to 6" <<"\n";
            return;
        }
        else {
            std::vector<std::string> status = board.get_status();
            status[y-1] = "X";
            board.set_status(status);
            
        }

        for (Player& player : players) {
        std::vector<Duck> ducks = player.get_ducks();
        if (y - 1 < ducks.size()) {
            ducks[y - 1].status = 1;  
            player.set_ducks(ducks);  
        }
    }

    }

    /*ยิงเป็ด*/
   void Shoot(int y) {
    auto pool = board.get_pool();
    auto status = board.get_status();
    if (y < 1 || y > pool.size()) {
        std::cout << "ตำแหน่งไม่ถูกต้อง (1-6): " << y << "\n";
        return;
    }
    std::cout << "ยิงที่ช่อง: " << y << "\n";
    if (pool[y - 1] != " ") {
        std::cout << "พบเป็ดในช่อง " << y << "\n";
        pool[y - 1] = " ";
        status[y - 1] = " ";
        // อัปเดต ducksdeck ด้วย setter
        auto ducksdeck = setduck.get_ducksdeck();
        ducksdeck[y - 1] = {"X"};
        setduck.set_ducksdeck(ducksdeck);
    } else {
        std::cout << "ไม่พบเป็ดในช่อง " << y << "\n";
        status[y - 1] = " ";
    }
    board.set_status(status);
    board.set_pool(pool);
    }

    /*เป็ดชิว*/
    void Hang_Back(int y){
        std::vector<std::string> pool = board.get_pool();
        if (y >= pool.size() || y < 1) {
            std::cout << "\nplase enter number between 1 to " << pool.size()-1 << "\n";
        } else {
            std::swap(pool[y-1], pool[y]);
            board.set_pool(pool);
        }
    }

    /*เป็ดสันติ*/
    void Give_Peace_A_Chance() {
        auto status = board.get_status();
        for (auto& s : status) s = " ";
        board.set_status(status);
    }

    //Pedpo : swap with the front card
    void Move_Ahead(int y){
        std::vector<std::string> pool = board.get_pool();
        if (y < 2 || y > pool.size()) {
            std::cout << "\nplase enter number between 2 to " << pool.size() << "\n";
            return;
        }
        std::swap(pool[y-1], pool[y-2]);
        board.set_pool(pool);
        // Print ("เป็ดโผ",target,cards,deck);
    }

    //Soonbeaw : shoot the duck that next to the targeted duck
    void Misfire(int y){
        std::vector<std::string> pool = board.get_pool();
        std::vector<std::string> status= board.get_status();
        std::vector<std::vector<std::string>> set = setduck.get_ducksdeck();
        if(status[y-2] == "X" || status[y] == "X"){
            pool.erase(pool.begin() + y-1);
            pool.push_back(set[0]);
            set.erase(set.begin());
        }
        else{
            std::cout << "No action occured" << std::endl;
        }
        board.set_status(status);
        board.set_pool(pool);
        setduck.set_ducksdeck(set);
        // Print("ศูนย์เบี้ยว",target,cards,deck);
    }


    //Taiku : shoot 2 ducks if they were targeted and next to each other
    void Two_Birds(int y){   
        std::vector<std::string> pool = board.get_pool();
        std::vector<std::string> status= board.get_status();
        std::vector<std::vector<std::string>> set = setduck.get_ducksdeck();
        if(status[y-2] == "X" && status[y-1] == "X"){               //in case input y = targeted front duck
            pool.erase(pool.begin() + y-2,pool.begin() + y);
            for(int i = 0; i < 2; i++){
                pool.push_back(set[0][1]);
                set.erase(set.begin());
            }
        }
        else if(status[y] == "X" && status[y-1] == "X"){            //in case input y = targeted back duck
            pool.erase(pool.begin() + y,pool.begin() + y+1);
            for(int i = 0; i < 2; i++){
                pool.push_back(set[0]);
                set.erase(set.begin());
            }
        }
        else if(status[y-1] == "X"){                              //in case no nearby targeted duck
            pool.erase(pool.begin() + y-1);
            pool.push_back(set[0]);
            set.erase(set.begin());
        }    
        board.set_status(status);
        board.set_pool(pool);
        setduck.set_ducksdeck(set);
        // Print("ตายคู่",target,cards,deck);
    }

    
    // ///Pedreborn : bring a duck card back      PS. may need to fix struct   take a look again na
    // void Resurrection(){
    //     std::vector<std::string> name = players.get_name();
    //     std::vector<std::vector<std::string>> set = setduck.get_ducksdeck();
    //     std::cout << "\nPlease enter name to reborn\n";
    // }

    void Double_Barrel() {
    std::vector<std::string> pool = board.get_pool();
    std::vector<std::string> status= board.get_status();
    int idx1, idx2;
    while (true) 
    {
        for (int i = 0; i < pool.size(); ++i)  //แสดงการ์ดบนกระดาน กับสเตตัส
            cout << "[" << i << "] " << pool[i] << "  " << status[i] << "\n";

        std::cout << "Select 2 adjacent cards to mark : ";
        std::cin >> idx1 >> idx2;

        if (idx1 >= 0 && idx1 < pool.size() && idx2 >= 0 && idx2 < pool.size()) { //เช็คอินเด็คการ์ดว่าเกินจำนวนการ์ดที่มีบนบอร์ดมั้ย
            if (abs(idx1 - idx2) == 1) 
            { //การ์ดอยู่ติดกัน
                if (pool[idx1] != "(   )" && pool[idx2] != "(   )") 
                {
                    //เปลี่ยนสเตตัสของการ์ดในตำแหน่งที่เลือก
                    status[idx1] = "X"; 
                    status[idx2] = "X";
                    std::cout << "Marked successfully!\n";
                    break;
                } else //การ์ดว่าง
                {
                    std::cout << "Cannot mark blank cards!\n";
                }
            } 
            else //การ์ดไม่ติดกัน
            {
                std::cout << "Cards must be adjacent!\n";
            }
        } 
        else //อินเด็คผิด
        {
            std::cout << "Invalid index!\n";
        }
    }
    board.set_status(status);
    }
    
// Action 2: Move a card left or right
    void Bump_Left_Bump_Right() {   
        std::vector<std::string> pool = board.get_pool();
        std::vector<std::string> status = board.get_status();
        int idx;
        char dir;
        while (true) 
        {
            for (int i = 0; i <pool.size(); ++i)  //แสดงการ์ดบนกระดาน กับสเตตัส
                std::cout << "[" << i << "] " << pool[i] << "  " << status[i] << "\n";

            std::cout << "Select a card to move : ";
            std::cin >> idx;

            if (idx >= 0 && idx < pool.size()) { 
                std::cout << "Move (L)eft or (R)ight?: ";
                std::cin >> dir;

                if ((dir == 'L' || dir == 'l') && idx > 0) //สลับไปซ้ายการ์ดไม่ใช่ใบแรก
                { 
                    swap(pool[idx], pool[idx - 1]);
                    swap(status[idx], status[idx - 1]);
                    break;
                } 
                else if ((dir == 'R' || dir == 'r') && idx < pool.size() - 1) //สลับไปขวาการ์ดไม่ใช่ใบสุดท้าย
                {
                    swap(pool[idx], pool[idx + 1]);
                    swap(status[idx], status[idx + 1]);
                    break;
                } 
                else 
                {
                    std::cout << "Cannot move in that direction!\n";
                }
            } 
            else 
            {
                std::cout << "Invalid index!\n";
            }
        }
        board.set_status(status);
    }

// Action 3: Move a card to the front
    void Fast_Forward() {
        std::vector<std::string> pool = board.get_pool();
        std::vector<std::string> status = board.get_status();
        int idx;
        while (true) 
        {
            for (int i = 0; i < pool.size(); ++i) //แสดงการ์ดบนบอร์ด
                std::cout << "[" << i << "] " << pool[i] << "  " << status[i] << "\n";

            std::cout << "Select the card to move to the front : ";
            std::cin >> idx;

            if (idx >= 0 && idx < pool.size()) 
            { //เช็คอินเด็คการ์ด
                std::string temp_col = pool[idx]; //เก็บค่าการ์ด(สี)ในอินเด็คที่เลือก
                std::string temp_status = status[idx]; //เก็บค่าการ์ด(สเตตัส)ในอินเด็คที่เลือก
                //ลบค่าการ์ดตำแหน่งที่เลือก
                pool.erase(pool.begin() + idx); 
                status.erase(status.begin() + idx);
                //เพิ่มค่าการ์ดไว้ที่ตำแหน่งหน้าสุด
                pool.insert(pool.begin(), temp_col); 
                status.insert(status.begin(), temp_status);
                break;
            } 
            else 
            {
                std::cout << "Invalid index!\n";
            }
        }
        board.set_status(status);
    }

// Action 4: Instant kill (remove marked card)
    void Quick_Shot() {
        std::vector<std::string> pool = board.get_pool();
        std::vector<std::string> status = board.get_status();
        int idx;
        while (true) 
        {
            for (int i = 0; i < pool.size(); ++i){
                std::cout << "[" << i << "] " << pool[i] << "  " << status[i] << "\n";

            std::cout << "Select the card to kill instantly : ";
            std::cin >> idx;

            if (idx >= 0 && idx < pool.size()) 
            {
            
                std::cout << "Instantly killed " << pool[idx] << "!\n"; //อินเด็กถูกแสดงบนเทอมินอลว่าฆ่าการ์ดที่เลือก
                //ลบค่าการ์ดตำแหน่งที่เลือก
                pool.erase(pool.begin() + idx); 
                status.erase(status.begin() + idx);
                break;

            } 
            else 
            {
                std::cout << "Invalid index!\n";
            }
        }
         board.set_status(status);
    }


    private:
        Board& board;
        Set_up& setduck;
        std::vector<Player>& players;

    };

class Playloop{
public:
    // สร้างลูบเงื่อนไขคือจนกว่าการ์ดเป็ดในบ่อจะเหลือ 1 ใบ
    // เรียกข้อมูลผู้เล่นได้ทีละ 1 คน
    // บังคับเล่นการ์ด 1 ใบ
    //  จั่วการ์ด 1 ใบ

    std::string chosen;
    int position;


    void run(std::vector<Player>& players, Set_up& setup ,Board& board) {
        int turn = 0;
        
        while (setup.get_ducksdeck().size() > 1) {
            Player& current = players[turn % players.size()]; /*กำหนดตัวผู้เล่น*/


            std::cout << "Current Player: " << current.get_name() << "\n";
            current.Print_player();

            /*บังคับเล่นการ์ด*/
            std::vector<std::string> actiondeck = current.get_playeractiondeck();
            if (actiondeck.empty()== false){

                std::cout << "Action deck:";
                for(const auto& card : actiondeck) std::cout << card << " ";
                std::cout << "\n";
                std::cout << "Choose your action:"<< "\n" ;
                std::cin >> chosen;
                std::cout << "Choose your rosition:"<< "\n" ;
                std::cin >> position;;

                /*ตรวจว่ามีการ์ดนั้นใน deck action ไหม*/
               
                if (std::find(actiondeck.begin(), actiondeck.end(), chosen) != actiondeck.end()) {
                    std::cout << "You played: " << chosen << "\n";
                        /*เรียกใช้ action ที่เลือก*/ 

                    if (chosen == "Shoot"){
                            current.Shoot(position);
                    } else if (chosen == "Take_Aim") {
                            current.Take_Aim(position);
                    } else if (chosen == "Hang_Back") {
                            current.Hang_Back(position);
                    } else if (chosen == "Give_Peace_A_Chance") {
                            current.Give_Peace_A_Chance();
                    // } else if (chosen == "Resurrection") {
                    //         current.Resurrection(position);
                    } else if (chosen == "Misfire") {
                            current.Misfire(position);
                    } else if (chosen == "Two_Birds") {
                            current.Two_Birds(position);
                    } else if (chosen == "Fast_Forward") {
                            current.Fast_Forward();
                    }else if (chosen == "Double_Barrel") {
                        auto pool = board.get_pool();
                        auto status = board.get_status();
                        current.Double_Barrel(pool, status);
                    }
                    else if (chosen == "Bump_Left_Bump_Right" ) {
                        auto pool = board.get_pool();
                        auto status = board.get_status();
                        current.Bump_Left_Bump_Right(pool, status);
                    } else if (chosen == "Quick_Shot") {
                        auto pool = board.get_pool();
                        auto status = board.get_status();
                        current.Quick_Shot(pool, status);
                    }
                    else if (chosen == "Move_Ahead") {
                            current.Move_Ahead(position);
                    }
                    
                    /*ลบการ์ดที่เล่นออกจาก action deck*/
                    auto index = std::find(actiondeck.begin(), actiondeck.end(), chosen);
                    actiondeck.erase(index);

                    /*จั่วการ์ด*/
                   auto globaldeck = setup.get_actiondeck();
                    if (!globaldeck.empty()) {
                        auto draw_card = globaldeck.front();
                        actiondeck.push_back(draw_card);
                        current.set_playeractiondeck(actiondeck);
                        std::cout << "You drew: " << draw_card << "\n";
                        globaldeck.erase(globaldeck.begin());
                        setup.set_actiondeck(globaldeck);
                    }

                    /*เอาการ์ดออกจาก deckaction กองกลาง*/
                     

                    
                }
                else
                    {
                        std::cout << "You don't have that action card in your deck.\n";
                    }
            }

            ++turn; /*เปลี่ยนเทิร์นผู้เล่น*/
        }

             
    }

        std::cout << "Game Over! The winner is: " << (setup.get_ducksdeck().back())[0] << "\n";


private:

};

