#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Types.h"
#include "Exchange.h"
#include "Counter.h"

// This is the most important class in this project. Class Chessboard contains information about possible moves in specific turn, whole chessboard as matrix of
// shared_pointers and allows to perform additional operations for example exchange. This class is strongly correlated with Scene class which is in charge of
// front-end part of this project.
class Chessboard{
public:
    Chessboard();
    chessboard_type get_chessboard() const;
    void get_possible_moves(int x_pos, int y_pos);
    void set_move_flag(bool value);
    bool get_move_flag() const ;
    void reset_possible_moves();
    bool make_move(int x_pos, int y_pos);
    exchange_status get_exchange_flag() const;
    bool is_added_to_scene() const;
    std::shared_ptr<Exchange> get_exchange_class() const;
    void change_exchange_in_scene(bool status);
    std::shared_ptr<Counter> make_exchange(int x_cords);
    bool get_win_flag() const;
private: 
    void set_exchange_flag(){this->exchange_flag = true;};
    void reset_exchange_flag(){this->exchange_flag = false;};

    bool move_flag_;
    bool win_flag_;
    bool exchange_in_scene;
    exchange_status exchange_flag;
    int x_pos_;
    int y_pos_;
    std::shared_ptr<Exchange> exchange;
    possible_moves_type possible_moves_;
    chessboard_type chessboard;
};

#endif // CHESSBOARD_H
