#ifndef STATEGRAPH_H
#define STATEGRAPH_H

#include "QString"
#include "graph.h"

class StateGraph : public Graph
{

public:
    StateGraph();
    StateGraph(QString path);

    void nextNode();
    void lastNode();
    int getIndex();

private:
    int selectedIndex;
};

#endif // STATEGRAPH_H
