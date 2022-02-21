#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include "Chessboard.h"
#include "Counter.h"
#include "Types.h"
#include "Win.h"
// This class is in change of communicating with Chessboard class and displaying actual situation on screen. It is also in charge of simulating game by MouseClick events.

class Scene: public QObject, public QGraphicsPixmapItem{
public:
    Scene(int width, int length);
    void create_chessboard(chessboard_type chessboard, QGraphicsScene *scene);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int get_position(int cords) const;
private:
    void swap_color();
    void restart_game();

    bool win_flag_;
    int width_;
    int length_;
    std::shared_ptr<Win> win_class;
    Color color_;
    QGraphicsView *view;
    QGraphicsScene *scene;
    Chessboard *chessboard_;
};


#endif // SCENE_H
