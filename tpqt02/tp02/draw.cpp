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
  image = new QImage(800,800,QImage::Format_ARGB32);
}

void draw::setTypeD(typeDraw typeD){
  this->typeD = typeD;
}

void draw:: mousePressEvent(QMouseEvent *event){
  if (event->buttons() & Qt::LeftButton  & moving == false){
      this->drawing = true;
      switch (typeD) {
        case PEN:
          this->x = event->x();
          this->y = event->y();
          break;
        default:
          shapecount = shapes.size();
          this->x = event->x();
          this->y = event->y();
        }
    }

  else if (event->buttons() & Qt::RightButton && this->drawing == false ){
     movingshape = 0;
     foreach(myshape shape, shapes){
         if (shape.getRect().contains(event->pos())){
             moving = true;
             break;
           }
         movingshape++;
       }
  }



}

void draw::mouseReleaseEvent(QMouseEvent *event){
  this->drawing = false;
  this->moving = false;


}

void draw::mouseMoveEvent(QMouseEvent *event){
  std::cout << "Move Line"<<std::endl;
  if(event->buttons() & Qt::LeftButton && drawing == true){
      int nx = event->x();
      int ny = event->y();
      if (typeD == PEN) {
          drawLine(nx, ny);
        }
      else{

          myshape shape(this->x, this->y, nx - x, ny - y, typeD, this->penWidght, this->penColor);
          if(shapecount<shapes.size()){
            shapes.removeLast();
            }
          shapes.push_back(shape);
          update();

        }
    }

  else if (event->buttons() & Qt::RightButton && moving == true){
      int nx = event->x();
      int ny = event->y();
      shapes[movingshape].setPos(x + (nx - x), y + (ny-y));
      update();
    }
}

void draw::updateShape (){
  QPainter painter(image);
  painter.setPen(QPen(this->penColor, this->penWidght, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
  foreach(myshape shape, shapes){
      if (shape.typeD == RECTANGLE){
          painter.drawRect(shape.getRect());
          update();
        }
      else{
          painter.drawEllipse(shape.getRect());
          update();
        }
    }
}

void draw::drawLine (int nx, int ny){
  QPainter painter(image);
  painter.setPen(QPen(this->penColor, this->penWidght, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
  painter.drawLine(x, y, nx, ny);
  this->x = nx;
  this->y = ny;
  update();

}

void draw::paintEvent(QPaintEvent* event){
  QWidget::paintEvent(event);
  QPainter painter(this);
  painter.setPen(QPen(this->penColor, this->penWidght, Qt::SolidLine, Qt::RoundCap,
                      Qt::RoundJoin));
  foreach(myshape shape, shapes){
      if (shape.typeD == RECTANGLE){
          painter.setPen(QPen(shape.color, shape.size, Qt::SolidLine, Qt::RoundCap,
                              Qt::RoundJoin));
          painter.drawRect(shape.getRect());
        }
      else{
          painter.setPen(QPen(shape.color, shape.size, Qt::SolidLine, Qt::RoundCap,
                              Qt::RoundJoin));
          painter.drawEllipse(shape.getRect());
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

