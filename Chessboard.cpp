#include "Chessboard.h"
// Contructor creates all counters and add it to chessboard matrix. It also sets specific flags necessary to properly program working.
Chessboard::Chessboard(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 0; j++){
            this->chessboard[i][i] = nullptr;
        }
    }
    for (int i = 0; i < 8; i++){
        this->chessboard[i][1] = std::make_shared<Pawn>(Pawn(5 + (i * 75), 80, Color::WHITE));
        this->chessboard[i][6] = std::make_shared<Pawn>(Pawn(5 + (i * 75), 455, Color::BLACK));
    }
    for (int i = 0; i < 8; i = i + 7){
        this->chessboard[i][0] = std::make_shared<Rook>(Rook(5 + (i * 75), 5, Color::WHITE));
        this->chessboard[i][7] = std::make_shared<Rook>(Rook(5 + (i * 75), 530, Color::BLACK));
    }
    for (int i = 1; i < 8; i = i + 5){
        this->chessboard[i][0] = std::make_shared<Knight>(Knight(5 + (i * 75), 5, Color::WHITE));
        this->chessboard[i][7] = std::make_shared<Knight>(Knight(5 + (i * 75), 530, Color::BLACK));
    }
    for (int i = 2; i < 8; i = i + 3){
        this->chessboard[i][0] = std::make_shared<Bishop>(Bishop(5 + (i * 75), 5, Color::WHITE));
        this->chessboard[i][7] = std::make_shared<Bishop>(Bishop(5 + (i * 75), 530, Color::BLACK));
    }
    this->chessboard[3][0] = std::make_shared<Queen>(Queen(230, 5, Color::WHITE));
    this->chessboard[3][7] = std::make_shared<Queen>(Queen(230, 530, Color::BLACK));
    this->chessboard[4][0] = std::make_shared<King>(King(305, 5, Color::WHITE));
    this->chessboard[4][7] = std::make_shared<King>(King(305, 530, Color::BLACK));
    this->move_flag_ = false;
    this->exchange_in_scene = false;
    this->exchange_flag = false;
    this->win_flag_ = false;
}

chessboard_type Chessboard::get_chessboard() const{
    return this->chessboard;
}

std::shared_ptr<Exchange> Chessboard::get_exchange_class() const {
    return this->exchange;
}

// Sets possible moves as moves of specific counter on chessboard and sets move_flag_ as true.
void Chessboard::get_possible_moves(int x_pos, int y_pos){
    if (this->chessboard[x_pos][y_pos] != nullptr){
        this->reset_possible_moves();
        this->possible_moves_ = this->chessboard[x_pos][y_pos].get()->get_possible_moves(this->chessboard, x_pos, y_pos, this->possible_moves_);
        this->x_pos_ = x_pos;
        this->y_pos_ = y_pos;
        this->move_flag_ = true;
    }
}

void Chessboard::set_move_flag(bool value){
    this->move_flag_ = value;
}

// This class is in charge of setting all values in possible_move matrix to false and set move_flag_ to false. In normal operating mode, this funtion is
// called every time, when mouse is clicked.
void Chessboard::reset_possible_moves(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            this->possible_moves_[i][j] = false;
        }
    }
    this->move_flag_ = false;
}

bool Chessboard::get_move_flag() const {
    return this->move_flag_;
}

exchange_status Chessboard::get_exchange_flag() const {
    return this->exchange_flag;
}

bool Chessboard::is_added_to_scene() const {
    return this->exchange_in_scene;
}

void Chessboard::change_exchange_in_scene(bool status){
    this->exchange_in_scene = status;
}

bool Chessboard::get_win_flag() const {
    return this->win_flag_;
}

// The make_move function contain 5 scenarios. Castling, winning game by one of players, moving to empty place, moving to occupied place and Pawn exchange.
bool Chessboard::make_move(int x_pos, int y_pos){
    if (this->move_flag_ && this->possible_moves_[x_pos][y_pos]){
        // Moving to occupied place.
        if (this->chessboard[x_pos][y_pos] != nullptr){
            // Castling scenario.
            if (this->chessboard[x_pos][y_pos]->get_counter_type() == Counter_type::KING && this->chessboard[this->x_pos_][this->y_pos_]->get_counter_type() == Counter_type::ROOK && this->chessboard[x_pos][y_pos]->get_color() == this->chessboard[this->x_pos_][this->y_pos_]->get_color()){
                if (this->chessboard[x_pos][y_pos]->whether_castling() && this->chessboard[this->x_pos_][this->y_pos_]->whether_castling()){
                    std::shared_ptr copy = this->chessboard[x_pos][y_pos];
                    this->chessboard[x_pos][y_pos].reset();
                    if (x_pos < this->x_pos_){
                        this->chessboard[x_pos + 1][y_pos] = this->chessboard[this->x_pos_][this->y_pos_];
                        this->chessboard[x_pos + 2][this->y_pos_] = copy;
                        chessboard[x_pos + 2][this->y_pos_]->make_move(x_pos + 2, y_pos_);
                        this->chessboard[this->x_pos_][this->y_pos_].reset();
                        chessboard[x_pos + 1][y_pos]->make_move(x_pos + 1, y_pos);
                    }
                    else{
                        this->chessboard[x_pos - 1][y_pos] = this->chessboard[this->x_pos_][this->y_pos_];
                        this->chessboard[x_pos - 2][this->y_pos_] = copy;
                        chessboard[x_pos - 2][this->y_pos_]->make_move(x_pos - 2, y_pos_);
                        this->chessboard[this->x_pos_][this->y_pos_].reset();
                        chessboard[x_pos - 1][y_pos]->make_move(x_pos - 1, y_pos);
                    }
                    this->move_flag_ = false;
                    return true;
                }
                else{
                   this->move_flag_ = false;
                   return false;
                }
            }
            // Winning scenario.
            else if (this->chessboard[x_pos][y_pos]->get_counter_type() == Counter_type::KING && this->chessboard[x_pos][y_pos]->get_color() != this->chessboard[this->x_pos_][this->y_pos_]->get_color()){
                this->win_flag_ = true;

                this->chessboard[x_pos][y_pos].reset();
                this->chessboard[x_pos][y_pos] = chessboard[this->x_pos_][this->y_pos_];
                this->chessboard[this->x_pos_][this->y_pos_].reset();
                this->chessboard[x_pos][y_pos]->make_move(x_pos, y_pos);
                this->move_flag_ = false;
                return true;
            }
            else{
                this->chessboard[x_pos][y_pos].reset();
            }
        }
        // Moving to empty place.
        this->chessboard[x_pos][y_pos] = chessboard[this->x_pos_][this->y_pos_];
        this->chessboard[this->x_pos_][this->y_pos_].reset();
        this->chessboard[x_pos][y_pos]->make_move(x_pos, y_pos);
        // Pawn exchange scenario.
        if ((y_pos == 0 || y_pos == 7) && chessboard[x_pos][y_pos].get()->get_counter_type() == Counter_type::PAWN){
            this->x_pos_ = x_pos;
            this->y_pos_ = y_pos;
            set_exchange_flag();
            this->exchange = std::make_shared<Exchange>(Exchange(100, 250, chessboard[x_pos][y_pos].get()->get_color()));
        }
        this->move_flag_ = false;
        return true;
    }
    else{
        this->move_flag_ = false;
        return false;
    }
}

// This funtion is in charge of changing Pawn to other counter type if it reaches the end of the chessboard.
std::shared_ptr<Counter> Chessboard::make_exchange(int x_cords){
    Counter_type counter_type = this->exchange->get_counter_type(x_cords);
    Color counter_color = this->chessboard[x_pos_][y_pos_].get()->get_color();
    int x_pos = this->x_pos_;
    int y_pos = this->y_pos_;
    this->chessboard[x_pos][y_pos].reset();
    if (counter_type == Counter_type::KNIGHT){
        this->chessboard[x_pos][y_pos] = std::make_shared<Knight>(Knight(5 + (x_pos * 75), 5 + (y_pos * 75), counter_color));
    }
    else if (counter_type == Counter_type::BISHOP){
        this->chessboard[x_pos][y_pos] = std::make_shared<Bishop>(Bishop(5 + (x_pos * 75), 5 + (y_pos * 75), counter_color));
    }
    else if (counter_type == Counter_type::ROOK){
        this->chessboard[x_pos][y_pos] = std::make_shared<Rook>(Rook(5 + (x_pos * 75), 5 + (y_pos * 75), counter_color));
    }
    else if (counter_type == Counter_type::QUEEN){
        this->chessboard[x_pos][y_pos] = std::make_shared<Queen>(Queen(5 + (x_pos * 75), 5 + (y_pos * 75), counter_color));
    }
    else{
        throw std::runtime_error("Invalid counter type.");
    }
    this->reset_exchange_flag();
    this->exchange.reset();
    return this->chessboard[x_pos][y_pos];
}
