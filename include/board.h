#ifndef BOARD_H
#define BOARD_H

class Board
{
    public:
        virtual int get_width() const = 0;
        virtual ~Board() = default;
};

#endif