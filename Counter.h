#ifndef COUNTER_H
#define COUNTER_H
#define SIZE 8
#include <QGraphicsPixmapItem>
#include <array>
#include "Types.h"

// Class counter is an interface and it is in charge of contains informations about each counter types. Each derived class are a polimorfism of Counter class.

class Counter: public QGraphicsPixmapItem, public QObject{
public:
    // Changing counter position in scene.
    virtual void make_move(int x_pos, int y_pos) = 0;
    virtual Color get_color() const = 0;
    // Calculates possible moves as binary array and returns it.
    virtual possible_moves_type get_possible_moves(std::array<std::array<std::shared_ptr<Counter>, SIZE>, SIZE> chessboard, int x_pos, int y_pos, possible_moves_type possible_moves) = 0;
    virtual Counter_type get_counter_type() const = 0;
    virtual bool whether_castling() const = 0;
    virtual ~Counter() = default;
};

// Supplementary data type.
using chessboard_type = std::array<std::array<std::shared_ptr<Counter>, SIZE>, SIZE>;

class Pawn: public Counter{
public:
    Pawn(int x_cords, int y_cords, Color color);
    Pawn(Pawn&& other){
        x_cords_ = other.x_cords_;
        y_cords_ = other.y_cords_;
        color_ = other.color_;
        counter_type = other.counter_type;
        set_pixmap();
    }

    Pawn(const Pawn& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
    }

    Pawn& operator = (const Pawn& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
        return *this;
    }

    void make_move(int x_pos, int y_pos);
    Color get_color() const {return color_;}
    possible_moves_type get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves);
    Counter_type get_counter_type() const {return counter_type;}
    bool whether_castling() const {return false;};
    ~Pawn() = default;
private:
    int x_cords_;
    int y_cords_;
    Color color_;
    Counter_type counter_type;
    void set_pixmap();
};


class Knight: public Counter{
public:
    Knight(int x_cords, int y_cords, Color color);
    Knight(Knight&& other){
        x_cords_ = other.x_cords_;
        y_cords_ = other.y_cords_;
        color_ = other.color_;
        counter_type = other.counter_type;
        set_pixmap();
    }

    Knight(const Knight& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
    }

    Knight& operator = (const Knight& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
        return *this;
    }

    void make_move(int x_pos, int y_pos);
    Color get_color() const {return color_;}
    possible_moves_type get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves);
    Counter_type get_counter_type() const {return counter_type;}
    bool whether_castling() const {return false;};
    ~Knight() = default;
private:
    int x_cords_;
    int y_cords_;
    Color color_;
    Counter_type counter_type;
    void set_pixmap();
};


class Bishop: public Counter{
public:
    Bishop(int x_cords, int y_cords, Color color);
    Bishop(Bishop&& other){
        x_cords_ = other.x_cords_;
        y_cords_ = other.y_cords_;
        color_ = other.color_;
        counter_type = other.counter_type;
        set_pixmap();
    }

    Bishop(const Bishop& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
    }

    Bishop& operator = (const Bishop& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
        return *this;
    }

    void make_move(int x_pos, int y_pos);
    Color get_color() const {return color_;}
    possible_moves_type get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves);
    Counter_type get_counter_type() const {return counter_type;}
    bool whether_castling() const {return false;};
    ~Bishop() = default;
private:
    int x_cords_;
    int y_cords_;
    Color color_;
    Counter_type counter_type;
    void set_pixmap();
};


class Rook: public Counter{
public:
    Rook(int x_cords, int y_cords, Color color);
    Rook(Rook&& other){
        x_cords_ = other.x_cords_;
        y_cords_ = other.y_cords_;
        color_ = other.color_;
        counter_type = other.counter_type;
        set_pixmap();
    }

    Rook(const Rook& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
    }

    Rook& operator = (const Rook& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
        return *this;
    }

    void make_move(int x_pos, int y_pos);
    Color get_color() const {return color_;}
    possible_moves_type get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves);
    Counter_type get_counter_type() const {return counter_type;}
    bool whether_castling() const {return this->castling_;};
    ~Rook() = default;
private:
    int x_cords_;
    int y_cords_;
    Color color_;
    Counter_type counter_type;
    void set_pixmap();
    // Additional parameter whose tell if Rook is still allowed to do castling.
    bool castling_;
};


class Queen: public Counter{
public:
    Queen(int x_cords, int y_cords, Color color);
    Queen(Queen&& other){
        x_cords_ = other.x_cords_;
        y_cords_ = other.y_cords_;
        color_ = other.color_;
        counter_type = other.counter_type;
        set_pixmap();
    }

    Queen(const Queen& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
    }

    Queen& operator = (const Queen& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
        return *this;
    }

    void make_move(int x_pos, int y_pos);
    Color get_color() const {return color_;}
    possible_moves_type get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves);
    Counter_type get_counter_type() const {return counter_type;}
    bool whether_castling() const {return false;};
    ~Queen() = default;
private:
    int x_cords_;
    int y_cords_;
    Color color_;
    Counter_type counter_type;
    void set_pixmap();
};


class King: public Counter{
public:
    King(int x_cords, int y_cords, Color color);

    King(King&& other){
        x_cords_ = other.x_cords_;
        y_cords_ = other.y_cords_;
        color_ = other.color_;
        counter_type = other.counter_type;
        set_pixmap();
    }

    King(const King& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
    }

    King& operator = (const King& copy){
        x_cords_ = copy.x_cords_;
        y_cords_ = copy.y_cords_;
        color_ = copy.color_;
        counter_type = copy.counter_type;
        set_pixmap();
        return *this;
    }

    void make_move(int x_pos, int y_pos);
    Color get_color() const {return color_;}
    possible_moves_type get_possible_moves(chessboard_type chessboard, int x_pos, int y_pos, possible_moves_type possible_moves);
    Counter_type get_counter_type() const {return counter_type;}
    bool whether_castling() const {return this->castling_;};
    ~King() = default;
private:
    int x_cords_;
    int y_cords_;
    Color color_;
    Counter_type counter_type;
    void set_pixmap();
    // Additional parameter whose tell if King is still allowed to do castling.
    bool castling_;
};

#endif // COUNTER_H
