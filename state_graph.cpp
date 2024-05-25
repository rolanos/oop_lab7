#include "state_graph.h"

StateGraph::StateGraph()
{
    this->selectedIndex = 0;
}


StateGraph::StateGraph(QString path) {
    this->selectedIndex =  0;
    setGraph(path);
}

void StateGraph::nextNode() {
    if(selectedIndex != getMatrixRowDimension() - 1) {
        selectedIndex++;
    }
}

void StateGraph::lastNode() {
    if(selectedIndex != 0) {
        selectedIndex--;
    }
}

int StateGraph::getIndex() {
    return selectedIndex;
}
