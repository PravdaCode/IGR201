#ifndef MYSHAPE_H
#define MYSHAPE_H
#include <QImage>
#include <QMouseEvent>
#include "typeDraw.h"
class myshape {
private:
  int x, y, widght, height;
  bool selected = false;
  int thick = 4;
public:
  myshape(int x, int y, int widght, int height, typeDraw t, int size, QColor color);
  typeDraw typeD;
  QRectF getRect();
  QLineF getLine();
  int size;
  QColor color;
  void select(bool select);
  void resize(int pos, int nx, int ny);
  bool isSelected();
  void setPos(int x, int y);
  QRectF getCLeftUp();
  QRectF getCRightUp();
  QRectF getCLeftDown();
  QRectF getCRightDown();

};

#endif // MYSHAPE_H
