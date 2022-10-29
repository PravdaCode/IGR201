#ifndef DRAW_H
#define DRAW_H
#include <QWidget>
#include <QMouseEvent>
#include <QImage>
#include "myshape.h"
#include "typeDraw.h"

class draw: public QWidget {

private:
  bool drawing = false;
  bool moving = false;
  void drawLine (int nx, int ny);
  QImage * image;
  QList<myshape> shapes;
  int movingshape = 0;
  int shapecount= 0;
  QColor penColor = Qt::blue;
  int penWidght = 1;
  void updateShape();

protected:
  virtual void paintEvent(QPaintEvent *event) override;

public:
  draw(QWidget* parent = nullptr);
  typeDraw typeD;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void setTypeD(typeDraw typeD);

  void setColor(QColor ncolor);
  QColor getColor();

  void setWidght(int nsize);
  int getWidght();

  int x, y;

signals:
  void Mouse_Pressed();
};


#endif // DRAW_H
