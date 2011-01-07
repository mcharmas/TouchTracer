#include "mapper.h"

Mapper::Mapper(QVector<CalibrationSquare*> *squares, QObject *parent) :
    QObject(parent), squares(squares)
{    
}

Mapper::~Mapper()
{
    for(int i = 0;i<squares->size(); i++)
    {
        delete (*squares)[i];
    }
    delete squares;
}

Point2f Mapper::map(Point2f &point)
{
    for(int i = 0; i<squares->size();i++)
    {
        CalibrationSquare *sq = (*squares)[i];
        if(sq->isInside(point))
        {            
            return sq->map(point);
        }
    }
    return Point2f(0,0);
}
