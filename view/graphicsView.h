#ifndef _GRAPHICSVIEW_H_
#define _GRAPHICSVIEW_H_

#include "view.h"

struct pos;

class GraphicsView : public View {
public:
    void printOutput(pos a, pos b) override;
};

#endif