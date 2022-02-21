#include <QGraphicsScene>
#include <QKeyEvent>
#include "Scene.h"
#include <QDebug>
#include <QApplication>
#include <QGraphicsView>

// Creates scene, view, chessboard and sets proper flags.
Scene::Scene(int width, int length){
    setPixmap(QPixmap(":/images/chessboard.png"));
    this->scene = new QGraphicsScene();
    scene->addItem(this);
    this->view = new QGraphicsView(scene);
    scene->setSceneRect(0, 0, width, length);
    length_ = length;
    width_ = width;
    this->chessboard_ = new Chessboard();
    chessboard_type new_chessboard = chessboard_->get_chessboard();
    create_chessboard(new_chessboard, scene);
    color_ = Color::WHITE;
    win_flag_ = false;
    view->show();
}

// Adds Chessboard to screen.
void Scene::create_chessboard(const chessboard_type chessboard, QGraphicsScene *scene){
    for (auto &row: chessboard){
        for (auto &item: row){
            if (item != nullptr){
                scene->addItem(item.get());
            }
        }
    }
}

// Recalculates cordinates on screen to position on chessboard.
int Scene::get_position(int cords) const {
    int pos = cords / 75;
    return pos;
}

// Changes actual color after successful move.
void Scene::swap_color(){
    if (this->color_ == Color::BLACK){
        this->color_ = Color::WHITE;
    }
    else{
        this->color_ = Color::BLACK;
    }
}

// Restarts game if once of players win the game.
void Scene::restart_game(){
    delete(this->chessboard_);
    this->chessboard_ = new Chessboard();
    chessboard_type new_chessboard = chessboard_->get_chessboard();
    create_chessboard(new_chessboard, this->scene);
    color_ = Color::WHITE;
    win_flag_ = false;
    this->win_class.reset();
}

// The mousePressEvent is in charge of game simulation.
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
   int x_cords = event->scenePos().x();
   int y_cords = event->scenePos().y();
   // Do if once of players did not win and exchange flag is actually sets to false.
   if (!(this->chessboard_->get_exchange_flag()) && !(this->win_flag_)){
       if (x_cords <= width_ && x_cords >= 0 && y_cords <= length_ and y_cords >= 0){
           int x_pos = get_position(x_cords);
           int y_pos = get_position(y_cords);
           if (this->chessboard_->get_move_flag()){
               bool is_successful = this->chessboard_->make_move(x_pos, y_pos);
               if (is_successful){
                   if (this->chessboard_->get_win_flag()){
                       this->win_flag_ = true;
                       this->win_class = std::make_shared<Win>(Win(100, 200, this->color_));
                       this->scene->addItem(this->win_class.get());
                   }
                   else{
                       swap_color();
                   }
               }
           }
           else{
               if (this->chessboard_->get_chessboard()[x_pos][y_pos] != nullptr){
                   if (this->chessboard_->get_chessboard()[x_pos][y_pos]->get_color() == this->color_){
                       this->chessboard_->get_possible_moves(x_pos, y_pos);
                    }
               }
            }
        }
   }
   // Restart game if once of players won.
   else if (this->win_flag_){
        this->restart_game();
   }
   // Do exchange if Pawn is in the right position.
   else{
        if (!(this->chessboard_->is_added_to_scene())){
            this->scene->addItem(this->chessboard_->get_exchange_class().get());
            this->chessboard_->change_exchange_in_scene(true);
        }
        else{
            if (x_cords <= 500 && x_cords >= 100 && y_cords <= 350 and y_cords >= 250){
                this->scene->addItem(this->chessboard_->make_exchange(x_cords).get());
                this->chessboard_->change_exchange_in_scene(false);
            }
        }
   }
}

