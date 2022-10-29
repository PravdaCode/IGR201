#ifndef MYSHAPE_H
#define MYSHAPE_H
#include <QImage>
#include <QMouseEvent>
#include "typeDraw.h"
class myshape {
private:
  int x, y, widght, height;
public:
  myshape(int x, int y, int widght, int height, typeDraw t, int size, QColor color);
  typeDraw typeD;
  QRectF getRect();
  int size;
  QColor color;

  void setPos(int x, int y);

};

#endif // MYSHAPE_H
