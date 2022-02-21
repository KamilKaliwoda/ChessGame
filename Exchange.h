#ifndef EXCHANGE_H
#define EXCHANGE_H
#include "Types.h"
#include <QGraphicsPixmapItem>

// This class is in charge of displays Exchange field in scene and choose proper counter type.
class Exchange: public QGraphicsPixmapItem, public QObject{
public:
    Exchange(int x_cords, int y_cords, Color color);
    Exchange(Exchange&& other){
        x_cords_ = other.x_cords_;
        y_cords_ = other.y_cords_;
        color_ = other.color_;
        set_pixmap();
    }

    Exchange(const Exchange& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        set_pixmap();
    }

    Exchange& operator = (const Exchange& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        set_pixmap();
        return *this;
    }

    ~Exchange() = default;
    Counter_type get_counter_type(int x_cords) const;
private:
    void set_pixmap();
    int x_cords_;
    int y_cords_;
    Color color_;
};

#endif // EXCHANGE_H
