#include "Exchange.h"

Exchange::Exchange(int x_cords, int y_cords, Color color){
    this->x_cords_ = x_cords;
    this->y_cords_ = y_cords;
    this->color_ = color;
    this->set_pixmap();
}

void Exchange::set_pixmap(){
    if (color_ == Color::BLACK){
        setPixmap(QPixmap(":/images/BlackExchange.png"));
    }
    else{
        setPixmap(QPixmap(":/images/WhiteExchange.png"));
    }
    setPos(x_cords_, y_cords_);
}

// Returns proper counter type depends on cordinates of scene which will be clicked.
Counter_type Exchange::get_counter_type(int x_cords) const {
    if (x_cords >= this->x_cords_){
        int relative_cords = x_cords - this->x_cords_;
        if (relative_cords < 100){
            return Counter_type::KNIGHT;
        }
        else if (relative_cords < 200){
            return Counter_type::BISHOP;
        }
        else if (relative_cords < 300){
            return Counter_type::ROOK;
        }
        else if (relative_cords < 400){
            return Counter_type::QUEEN;
        }
        else{
            throw std::runtime_error("Invalid cordinates.");
        }
    }
    else{
        throw std::runtime_error("Invalid cordinates.");
    }
}
