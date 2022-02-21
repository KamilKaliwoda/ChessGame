#include "Win.h"

Win::Win(int x_cords, int y_cords, Color color){
    this->x_cords_ = x_cords;
    this->y_cords_ = y_cords;
    this->color_ = color;
    this->set_pixmap();
}

void Win::set_pixmap(){
    if (color_ == Color::BLACK){
        setPixmap(QPixmap(":/images/BlackWin.png"));
    }
    else{
        setPixmap(QPixmap(":/images/WhiteWin.png"));
    }
    setPos(x_cords_, y_cords_);
}
