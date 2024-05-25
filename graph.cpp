#include "graph.h"

//Создаем матрицу конструктором по умолчанию
Graph::Graph() {
    matrix = new Matrix<bool>();
}

//Создаем матрицу конструктором по умолчанию
Graph::Graph(QString path) {
    setGraph(path);
}

Graph::~Graph() {}

//В случае ошибки возвращает её текст
QString Graph::setGraph(QString path) {
    QFile file = QFile(path);
    //Устанавливаем флаг на чтение, иначе выходим из функции
    file.open(QIODevice::ReadOnly);
    QString sizeBuffer;
    QByteArray values;
    QByteArray data = file.readAll();
    data.replace('\r', "");
    char separator = '\n';
    //Считываем данные с файла
    if(data.split(separator).length() == 2) {
        sizeBuffer = data.split(separator).first();
        values = data.split(separator).last();
    }

    int size = sizeBuffer.toInt();
    matrix = new Matrix<bool>(size, size);
    QByteArrayList valuesList = values.split(' ');
    if((size * size) != valuesList.length()){
        return QString("Ошибка! В файле указано элемента ") + QString::number(size) + QString(", а в матрице ") + QString::number(valuesList.length());
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            //Определяем по матрице смежности, есть ли путь
            //Если есть - true, иначе - false
            bool bufferValue = QString::compare(valuesList[i * size + j], QString("1")) ? true : false;
            matrix->inputValue(bufferValue, i, j);
        }
    }
    return nullptr;
}

int Graph::getMatrixRowDimension() {
    return matrix->getRowNumber();
}


int Graph::getMatrixColumnDimension() {
    return matrix->getColumnNumber();
}


bool Graph::getElement(int i, int j) {
    return (*matrix)(i, j);
}
