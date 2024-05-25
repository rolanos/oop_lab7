#ifndef GRAPHDRAW_H
#define GRAPHDRAW_H

#include <QPainter>

#include "state_graph.h"

class StateGraphDraw
{

public:
    StateGraphDraw();
    StateGraphDraw(StateGraph);

    //Отрисовка
    void draw(QPainter*, QRect);
    //Новое событие
    void newEvent(bool);

private:
    StateGraph graph;

    void drawLines(QPointF*, QPainter*, int i, int j, qreal);
};

#endif // GRAPHDRAW_H
