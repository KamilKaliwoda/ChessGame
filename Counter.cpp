#include "Counter.h"

Pawn::Pawn(int x_cords, int y_cords, Color color){
    x_cords_ = x_cords;
    y_cords_ = y_cords;
    color_ = color;
    counter_type = Counter_type::PAWN;
    set_pixmap();
}

// Sets correct Pixel map and position in scene, depends on counter's color.
void Pawn::set_pixmap(){
    if (color_ == Color::BLACK){
        setPixmap(QPixmap(":/images/BlackPawn.png"));
    }
    else{
        setPixmap(QPixmap(":/images/WhitePawn.png"));
    }
    setPos(x_cords_, y_cords_);
}

// Returns possible moves as binary matrix according to Pawn moveset.
possible_moves_type Pawn::get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves){
    if (this->color_ == Color::BLACK){
        if (chessboard[x_pos][5] == nullptr && y_pos == 6){
            possible_moves[x_pos][5] = true;
            if (chessboard[x_pos][4] == nullptr){
                possible_moves[x_pos][4] = true;
            }
        }
        if (chessboard[x_pos][y_pos - 1] == nullptr){
            possible_moves[x_pos][y_pos - 1] = true;
        }
        if (x_pos > 0){
            if (chessboard[x_pos - 1][y_pos - 1] != nullptr && chessboard[x_pos - 1][y_pos - 1].get()->get_color() != this->color_){
                possible_moves[x_pos - 1][y_pos - 1] = true;
            }
        }
        if (x_pos < 7){
            if (chessboard[x_pos + 1][y_pos - 1] != nullptr && chessboard[x_pos + 1][y_pos - 1].get()->get_color() != this->color_){
                possible_moves[x_pos + 1][y_pos - 1] = true;
            }
        }
    }
    else if (this->color_ == Color::WHITE){
        if (chessboard[x_pos][2] == nullptr && y_pos == 1){
            possible_moves[x_pos][2] = true;
            if (chessboard[x_pos][3] == nullptr){
                possible_moves[x_pos][3] = true;
            }
        }
        if (chessboard[x_pos][y_pos + 1] == nullptr){
            possible_moves[x_pos][y_pos + 1] = true;
        }
        if (x_pos > 0){
            if (chessboard[x_pos - 1][y_pos + 1] != nullptr && chessboard[x_pos - 1][y_pos + 1].get()->get_color() != this->color_){
                possible_moves[x_pos - 1][y_pos + 1] = true;
            }
        }
        if (x_pos < 7){
            if (chessboard[x_pos + 1][y_pos + 1] != nullptr && chessboard[x_pos + 1][y_pos + 1].get()->get_color() != this->color_){
                possible_moves[x_pos + 1][y_pos + 1] = true;
            }
        }
    }
    else{
        throw std::logic_error("Invalid color.");
    }
    return possible_moves;
}

void Pawn::make_move(int x_pos, int y_pos){
    this->x_cords_ = 5 + (x_pos * 75);
    this->y_cords_ = 5 + (y_pos * 75);
    setPos(this->x_cords_, this->y_cords_);
}

// Returns possible moves as binary matrix according to Knight moveset, that is maximum 8 available positions.
Knight::Knight(int x_cords, int y_cords, Color color){
    x_cords_ = x_cords;
    y_cords_ = y_cords;
    color_ = color;
    counter_type = Counter_type::KNIGHT;
    set_pixmap();
}

void Knight::set_pixmap(){
    if (color_ == Color::BLACK){
        setPixmap(QPixmap(":/images/BlackKnight.png"));
    }
    else{
        setPixmap(QPixmap(":/images/WhiteKnight.png"));
    }
    setPos(x_cords_, y_cords_);
}

possible_moves_type Knight::get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves){
    int x_2[2] = {-2, 2};
    int x_1[2] = {-1, 1};
    int y_2[2] = {-2, 2};
    int y_1[2] = {-1, 1};
    for (auto x: x_2){
        for (auto y: y_1){
            if (x_pos + x <= 7 && x_pos + x >= 0  && y_pos + y <= 7 && y_pos + y >= 0){
                if (chessboard[x_pos + x][y_pos + y] == nullptr || chessboard[x_pos + x][y_pos + y].get()->get_color() != this->color_){
                    possible_moves[x_pos + x][y_pos + y] = true;
                }
            }
        }
    }
    for (auto y: y_2){
        for (auto x: x_1){
            if (x_pos + x <= 7 && x_pos + x >= 0  && y_pos + y <= 7 && y_pos + y >= 0){
                if (chessboard[x_pos + x][y_pos + y] == nullptr || chessboard[x_pos + x][y_pos + y].get()->get_color() != this->color_){
                    possible_moves[x_pos + x][y_pos + y] = true;
                }
            }
        }
    }
    return possible_moves;
}

void Knight::make_move(int x_pos, int y_pos){
    this->x_cords_ = 5 + (x_pos * 75);
    this->y_cords_ = 5 + (y_pos * 75);
    setPos(this->x_cords_, this->y_cords_);
}

Bishop::Bishop(int x_cords, int y_cords, Color color){
    x_cords_ = x_cords;
    y_cords_ = y_cords;
    color_ = color;
    counter_type = Counter_type::BISHOP;
    set_pixmap();
}

void Bishop::set_pixmap(){
    if (color_ == Color::BLACK){
        setPixmap(QPixmap(":/images/BlackBishop.png"));
    }
    else{
        setPixmap(QPixmap(":/images/WhiteBishop.png"));
    }
    setPos(x_cords_, y_cords_);
}

// Returns possible moves as binary matrix according to Bishop moveset, that is in four directions.
possible_moves_type Bishop::get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves){
    int distance = 1;
    int shift_x[4] = {1, 1, -1, -1};
    int shift_y[4] = {1, -1, -1, 1};
    for (int i = 0; i < 4; i++){
        while (true){
            int actual_pos_x = x_pos + (shift_x[i] * distance);
            int actual_pos_y = y_pos + (shift_y[i] * distance);
            if (actual_pos_x <= 7 && actual_pos_x >= 0 && actual_pos_y <= 7 && actual_pos_y >= 0){
                if (chessboard[actual_pos_x][actual_pos_y] == nullptr){
                    possible_moves[actual_pos_x][actual_pos_y] = true;
                }
                else if (chessboard[actual_pos_x][actual_pos_y].get()->get_color() != this->color_){
                    possible_moves[actual_pos_x][actual_pos_y] = true;
                    break;
                }
                else{
                    break;
                }
            }
            else{
                break;
            }
            distance++;
        }
        distance = 1;
    }
    return possible_moves;
}

void Bishop::make_move(int x_pos, int y_pos){
    this->x_cords_ = 5 + (x_pos * 75);
    this->y_cords_ = 5 + (y_pos * 75);
    setPos(this->x_cords_, this->y_cords_);
}

Rook::Rook(int x_cords, int y_cords, Color color){
    x_cords_ = x_cords;
    y_cords_ = y_cords;
    color_ = color;
    counter_type = Counter_type::ROOK;
    set_pixmap();
}

void Rook::set_pixmap(){
    if (color_ == Color::BLACK){
        setPixmap(QPixmap(":/images/BlackRook.png"));
    }
    else{
        setPixmap(QPixmap(":/images/WhiteRook.png"));
    }
    setPos(x_cords_, y_cords_);
}

// Returns possible moves as binary matrix according to Rook moveset, that is in four directions but other than Bishop.
possible_moves_type Rook::get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves){
    int distance = 1;
    int shift_x[4] = {1, -1, 0, 0};
    int shift_y[4] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++){
        while (true){
            int actual_pos_x = x_pos + (shift_x[i] * distance);
            int actual_pos_y = y_pos + (shift_y[i] * distance);
            if (actual_pos_x <= 7 && actual_pos_x >= 0 && actual_pos_y <= 7 && actual_pos_y >= 0){
                if (chessboard[actual_pos_x][actual_pos_y] == nullptr){
                    possible_moves[actual_pos_x][actual_pos_y] = true;
                }
                else if (chessboard[actual_pos_x][actual_pos_y].get()->get_color() != this->color_ || (chessboard[actual_pos_x][actual_pos_y].get()->get_counter_type() == Counter_type::KING && this->castling_)){
                    possible_moves[actual_pos_x][actual_pos_y] = true;
                    break;
                }
                else{
                    break;
                }
            }
            else{
                break;
            }
            distance++;
        }
        distance = 1;
    }
    return possible_moves;
}

void Rook::make_move(int x_pos, int y_pos){
    this->x_cords_ = 5 + (x_pos * 75);
    this->y_cords_ = 5 + (y_pos * 75);
    setPos(this->x_cords_, this->y_cords_);
    if (this->castling_){
        this->castling_ = false;
    }
}

Queen::Queen(int x_cords, int y_cords, Color color){
    x_cords_ = x_cords;
    y_cords_ = y_cords;
    color_ = color;
    counter_type = Counter_type::QUEEN;
    set_pixmap();
}

void Queen::set_pixmap(){
    if (color_ == Color::BLACK){
        setPixmap(QPixmap(":/images/BlackQueen.png"));
    }
    else{
        setPixmap(QPixmap(":/images/WhiteQueen.png"));
    }
    setPos(x_cords_, y_cords_);
}

// Returns possible moves as binary matrix according to Queen moveset, that is merge of movesets of Rook and Bishop.
possible_moves_type Queen::get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves){
    int distance = 1;
    int shift_x[8] = {1, 1, -1, -1, 1, -1, 0, 0};
    int shift_y[8] = {-1, 1, -1, 1, 0, 0, 1, -1};
    for (int i = 0; i < 8; i++){
        while (true){
            int actual_pos_x = x_pos + (shift_x[i] * distance);
            int actual_pos_y = y_pos + (shift_y[i] * distance);
            if (actual_pos_x <= 7 && actual_pos_x >= 0 && actual_pos_y <= 7 && actual_pos_y >= 0){
                if (chessboard[actual_pos_x][actual_pos_y] == nullptr){
                    possible_moves[actual_pos_x][actual_pos_y] = true;
                }
                else if (chessboard[actual_pos_x][actual_pos_y].get()->get_color() != this->color_){
                    possible_moves[actual_pos_x][actual_pos_y] = true;
                    break;
                }
                else{
                    break;
                }
            }
            else{
                break;
            }
            distance++;
        }
        distance = 1;
    }
    return possible_moves;
}

void Queen::make_move(int x_pos, int y_pos){
    this->x_cords_ = 5 + (x_pos * 75);
    this->y_cords_ = 5 + (y_pos * 75);
    setPos(this->x_cords_, this->y_cords_);
}

King::King(int x_cords, int y_cords, Color color){
    x_cords_ = x_cords;
    y_cords_ = y_cords;
    color_ = color;
    counter_type = Counter_type::KING;
    set_pixmap();
}

void King::set_pixmap(){
    if (color_ == Color::BLACK){
        setPixmap(QPixmap(":/images/BlackKing.png"));
    }
    else{
        setPixmap(QPixmap(":/images/WhiteKing.png"));
    }
    setPos(x_cords_, y_cords_);
}

// Returns possible moves as binary matrix according to King moveset, that is 1 unit in each direction.
possible_moves_type King::get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves){
    int shift[3] = {-1, 0, 1};
    for (auto x: shift){
        for (auto y: shift){
            if (x_pos + x <= 7 && x_pos + x >= 0 && y_pos + y <= 7 && y_pos + y >= 0){
                if (chessboard[x_pos + x][y_pos + y] == nullptr || chessboard[x_pos + x][y_pos + y].get()->get_color() != this->color_){
                    possible_moves[x_pos + x][y_pos + y] = true;
                }
            }
        }
    }
    possible_moves[x_pos][y_pos] = false;
    return possible_moves;
}

void King::make_move(int x_pos, int y_pos){
    this->x_cords_ = 5 + (x_pos * 75);
    this->y_cords_ = 5 + (y_pos * 75);
    setPos(this->x_cords_, this->y_cords_);
    if (this->castling_){
        this->castling_ = false;
    }
}

