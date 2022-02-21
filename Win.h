#ifndef WIN_H
#define WIN_H
#include "Types.h"
#include <QGraphicsPixmapItem>

// Displays relevant screen in scene depends on player whose won the game.
class Win: public QGraphicsPixmapItem, public QObject{
public:
    Win(int x_cords, int y_cords, Color color);
    Win(Win&& other){
        x_cords_ = other.x_cords_;
        y_cords_ = other.y_cords_;
        color_ = other.color_;
        set_pixmap();
    }

    Win(const Win& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        set_pixmap();
    }

    Win& operator = (const Win& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        set_pixmap();
        return *this;
    }

    ~Win() = default;
private:
    int x_cords_;
    int y_cords_;
    Color color_;
    void set_pixmap();
};

#endif // WIN_H
