#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QPainter>
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include "graph_draw.h"

class TInterface : public QWidget
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();
    //Ширина окна приложения
    static inline double width;
    //Высота окна приложения
    static inline double height;

private:
    //Кнопка с загрузкой графа
    QPushButton* pushButton;
    //Надпись со статусом приложения
    QLabel* stateLabel;
    //Класс, отвечающий за хранение реализации и отображение графа
    GraphDraw graph;

public slots:
    //Callback для получения файла с матрицой смежности
    void pickFile();
protected:
    //Переопределяем метод отрисовки виджета
    void paintEvent(QPaintEvent*) override;
};
#endif // TINTERFACE_H
