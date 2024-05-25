#include "state_graph_draw.h"

StateGraphDraw::StateGraphDraw() {}

StateGraphDraw::StateGraphDraw(StateGraph graph){
    this->graph = graph;
}

void StateGraphDraw::draw(QPainter* painter, QRect window)
{
    //Установка нужных значений в плоскости программы
    int dimension = this->graph.getMatrixRowDimension();
    double fontSize = 20;
    double centerW = 0.5 * window.width();
    double centerH = 0.5 * window.height();
    double circleR = (centerW > centerH ? centerH : centerW) - 2 * fontSize - 50;
    double margin = 2.0 * acos(-1.0)/dimension;

    //Устанавливаем у нашего painter стиль текста(для номеров вершин)
    QFont font;
    font.setFamily("Times");
    font.setPointSize(fontSize);
    painter->setFont(font);

    //Устанавливаем у нашего painter толщину кисти и цвет
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::black);
    pen.setBrush(QBrush(Qt::black));
    painter->setPen(pen);


    QPointF *points = new QPointF[dimension];
    double x;
    double y;

    for (int i = 0; i < dimension; i++)
    {
        x = centerW + circleR*sin(i*margin);
        y = centerH - circleR*cos(i*margin);
        points[i] = QPointF(x, y);
    }

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            //Проверяем на наличие пути из i в j
            if (graph.getElement(i,j))
                drawLines(points, painter, i, j, fontSize);
        }
    }



    for (int i = 0; i < dimension; i++)
    {
        //Устанавливаем цвет границы
        painter->setPen(QPen(Qt::white));
        //Устанавливаем цвет заднего фона
        if (graph.getIndex() == i) {
            painter->setBrush(QBrush(Qt::darkGreen));
        }
        else {
            painter->setBrush(QBrush(Qt::darkBlue));
        }
        //Рисуем вершину в виде окружности с радиусом fontSize
        painter->drawEllipse(points[i], fontSize, fontSize);
        //Рисуем текст внутри окружности(вершины)
        painter->drawText(QRectF(points[i].x()-fontSize,points[i].y()-fontSize, 2.0*fontSize, 2.0*fontSize), QString().setNum(i+1), QTextOption(Qt::AlignCenter));
    }
    //После отрисовки удаляем наш динамический массив точек
    delete [] points;
}

void StateGraphDraw::drawLines(QPointF *points, QPainter *p, int i, int j, qreal radius)
{
    int size = graph.getMatrixRowDimension();
    double angle = 2.0 * acos(-1.0) / size;
    double circleX;
    double circleY;
    if (i == j)
    {
        p->setBrush(QBrush());
        circleX = points[i].x() + radius * sin(i*angle);
        circleY = points[i].y() - radius * cos(i*angle);
        p->drawEllipse(QPointF(circleX, circleY), radius / 1.25, radius / 1.25);
    }
    else
    {
        p->drawLine(points[i], points[j]);

        qreal k = (points[j].y() - points[i].y()) / (points[j].x() - points[i].x());

        if ((points[j].x() < points[i].x()) && points[j].y() > points[i].y())
        {
            circleX = points[j].x() + radius*cos((atan(k)));
            circleY = points[j].y() + radius*sin((atan(k)));

        }
        else if ((points[j].x() > points[i].x()) && points[j].y() > points[i].y())
        {
            circleX = points[j].x() - radius*cos(atan(k));
            circleY = points[j].y() - radius*sin(atan(k));

        }
        else if ((points[j].x() < points[i].x()) && points[j].y() < points[i].y())
        {
            circleX = points[j].x() + radius*cos(atan(k));
            circleY = points[j].y() + radius*sin(atan(k));

        }
        else if ((points[j].x() > points[i].x()) && points[j].y() < points[i].y())
        {
            circleX = points[j].x() - radius*cos(atan(k));
            circleY = points[j].y() - radius*sin(atan(k));


        }
        else if ((points[j].x() == points[i].x()) && points[j].y() < points[i].y())
        {
            circleX = points[j].x() - radius*cos(atan(k)) * 0;
            circleY = points[j].y() - radius*sin(atan(k));

        }
        else if ((points[j].x() == points[i].x()) && points[j].y() > points[i].y())
        {
            circleX = points[j].x() - radius*cos(atan(k)) * 0;
            circleY = points[j].y() - radius*sin(atan(k));

        }
        else if ((points[j].x() > points[i].x()) && points[j].y() == points[i].y())
        {
            circleX = points[j].x() - radius*cos(atan(k));
            circleY = points[j].y() - radius*sin(atan(k)) * 0;

        }
        else if ((points[j].x() < points[i].x()) && points[j].y() == points[i].y())
        {
            circleX = points[j].x() + radius*cos(atan(k));
            circleY = points[j].y() - radius*sin(atan(k)) * 0;

        }
        else
        {
            return;
        }
        p->drawEllipse(QPointF(circleX, circleY), radius/5, radius/5);
    }
}


void StateGraphDraw::newEvent(bool direction)
{
    if (direction) {
        graph.nextNode();
    }else {
        graph.lastNode();
    }
}
