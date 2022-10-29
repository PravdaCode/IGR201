#include "myshape.h"

int aux = 0;

myshape::myshape(int x, int y, int widght, int height, typeDraw t, int size, QColor color){
  this->x= x;
  this->y = y;
  this->widght = widght;
  this->height = height;
  this->typeD = t;
  this->size = size;
  this->color =color;

}

QRectF myshape::getRect(){
  return QRectF(this->x+aux, this->y, this->widght, this->height);
}

void myshape::setPos(int x, int y){
  this->x = x;
  this->y = y;
}
