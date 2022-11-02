#include "draw.h"
#include <QWidget>
#include <iostream>
#include <QPainter>
#include <QPushButton>
#include <QLine>
#include <QObject>
#include "myshape.h"

draw::draw(QWidget * parent) : QWidget(parent){
  this->setMinimumSize(50,200);
}

void draw::setTypeD(typeDraw typeD){
  this->typeD = typeD;
}

// Start editing here
void draw::mouseDoubleClickEvent(QMouseEvent *event){
  if (event->buttons() & Qt::LeftButton){
      diselectAll();
      int pos = 0;
      foreach(myshape shape, shapes){
          if (shape.getRect().contains(event->pos())){
              editing = true;
              shapes.removeAt(pos);
              shape.select(true);
              shapes.push_back(shape);
              update();
              return;
            }
          pos++;
        }
    }
  editing = false;
}

// Deals with 2 things drawing and editing
void draw::mousePressEvent(QMouseEvent *event){
  if (event->buttons() & Qt::LeftButton  & editing == false){
      this->drawing = true;
      shapecount = shapes.size();
      this->x = event->x();
      this->y = event->y();
    }


  else if (event->buttons() & Qt::LeftButton && this->drawing == false ){
      if (shapes[shapes.size()-1].getCLeftUp().contains(event->pos())){
          resize = true;
          resizepos = 0;
          setCursor(Qt::SizeBDiagCursor);
          return;
        }
      else if (shapes[shapes.size()-1].getCLeftDown().contains(event->pos())){
          resize = true;
          resizepos = 1;
          setCursor(Qt::SizeBDiagCursor);
          return;
        }
      else if (shapes[shapes.size()-1].getCRightUp().contains(event->pos())){
          resize = true;
          resizepos = 2;
          setCursor(Qt::SizeBDiagCursor);
          return;
        }
      else if (shapes[shapes.size()-1].getCRightDown().contains(event->pos())){
          resize = true;
          resizepos = 3;
          setCursor(Qt::SizeBDiagCursor);
          return;
        }
      else if (shapes[shapes.size()-1].getRect().contains(event->pos()) && resize == false){
          moving = true;
          return;
        }

      moving = false;
    }





}

void draw::mouseReleaseEvent(QMouseEvent *event){
  this->drawing = false;
  setCursor(Qt::ArrowCursor);
  resize = false;


}

void draw::mouseMoveEvent(QMouseEvent *event){
// Here we are creating the shape
  if(event->buttons() & Qt::LeftButton && drawing == true){
      int nx = event->x();
      int ny = event->y();

      myshape shape(this->x, this->y, nx - x, ny - y, typeD, this->penWidght, this->penColor);
      if(shapecount<shapes.size()){
          shapes.removeLast();
        }
      shapes.push_back(shape);
      update();


    }
// Here we are moving the shape
  else if (event->buttons() & Qt::LeftButton && moving == true){
      int nx = event->x();
      int ny = event->y();
      shapes[shapes.size()-1].setPos(nx, ny);
      update();
    }
// Here we are resizing the shape
  else if (event->buttons() & Qt::LeftButton && resize == true){
      int nx = event->x();
      int ny = event->y();

      shapes[shapes.size()-1].resize(resizepos, nx, ny);

      update();
    }
}


void draw::paintEvent(QPaintEvent* event){
  QWidget::paintEvent(event);
  QPainter painter(this);
  painter.setPen(QPen(this->penColor, this->penWidght, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
  foreach(myshape shape, shapes){
      // If selected we want to paint a editing box around our shape
      if (shape.isSelected()){
          painter.setPen(QPen(Qt::black, this->penWidght*2, Qt::SolidLine, Qt::RoundCap,
                              Qt::RoundJoin));
          painter.drawRect(shape.getCLeftDown());
          painter.drawRect(shape.getCRightDown());
          painter.drawRect(shape.getCLeftUp());
          painter.drawRect(shape.getCRightUp());
          painter.setPen(QPen(shape.color, shape.size*2, Qt::DotLine, Qt::RoundCap,
                              Qt::RoundJoin));
        }

      else
        painter.setPen(QPen(shape.color, shape.size, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));

      // We draw the shape here
      switch (shape.typeD) {
        case RECTANGLE:
          painter.drawRect(shape.getRect());
          break;

        case ELIPSE:
          painter.drawEllipse(shape.getRect());
          break;

        case LINE:
          painter.drawLine(shape.getLine());
          break;
        }
    }
}

void draw::setColor(QColor ncolor){
  this->penColor = ncolor;
}
QColor draw::getColor(){return this->penColor;}

void draw::setWidght(int nsize){
  this->penWidght = nsize;
}
int draw::getWidght(){return this->penWidght;}

// We'll diselect the selected shape
void draw::diselectAll(){
  if (shapes.size()>0)
    return;
  myshape shape = shapes[shapes.size()-1];
  shapes.removeLast();
  shape.select(false);
  shapes.push_back(shape);
  update();
}

