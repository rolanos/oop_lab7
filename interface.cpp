#include "interface.h"

TInterface::TInterface(QWidget *parent) : QWidget(parent)
{
    width = 640;
    height = 360;

    setFixedSize(width, height);
    setWindowTitle("Практическая работа №8. Команда 14");
    // Устанавливаем серый цвет фона
    setStyleSheet("background-color: #F0F0F0;"); // серый цвет в формате RGB

    pushButton = new QPushButton(this);
    pushButton->setGeometry(width * 0.35, height * 0.8, width * 0.3, height * 0.1);
    pushButton->setText("Загрузить граф");

    stateLabel = new QLabel(this);
    stateLabel->setText("Никакой граф не выбран.\nНажмите для выбора на кнопку ниже");
    stateLabel->setGeometry(width * 0.05, height * 0.05, width * 0.8, height * 0.6);
    stateLabel->setStyleSheet("font-weight: 600; font-size: 20px; font-family: Times New Roman;");

    connect(pushButton, SIGNAL(clicked()), this, SLOT(pickFile()));
}

TInterface::~TInterface(){
    delete pushButton;
    delete stateLabel;
}

void TInterface::pickFile()
{
    QString fileName = "";
    fileName = QFileDialog::getOpenFileName(this, ("Open File"), QDir::currentPath(), ("Graph (*.txt)"));
    stateLabel->setVisible(true);
    //Проверка на правильность открытия файла
    if (fileName != "")
    {
        StateGraph graph(fileName);
        //Проверка на правильность считывания файла графа
        QString status = graph.setGraph(fileName);
        if(status != nullptr){
            stateLabel->setText(status);
            repaint();
            return;
        }
        this->graph = StateGraph(graph);
        //Скрываем строку состояния
        stateLabel->setVisible(false);
        repaint();
    }
    else {
        stateLabel->setText("Не удалось получить доступ к файлу");
    }
}

void TInterface::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    graph.draw(&p, QRect(0, height * 0.05, width, height * 0.75));
    p.end();
}

void TInterface::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)  graph.newEvent(false);
    if (event->button() == Qt::RightButton) graph.newEvent(true);
    update();
}
