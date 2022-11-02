#include "myshape.h"

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
  return QRectF(this->x, this->y, this->widght, this->height);
}

QLineF myshape::getLine(){
  return QLineF(this->x, this->y, this->x + this->widght, this->y+this->height);
}
void myshape::select(bool select){
  if (!select)
    this->selected = false;
  else
    this->selected = true;
}

bool myshape::isSelected(){
  return selected;
}
void myshape::setPos(int x, int y){
  this->x = x-widght/2;
  this->y = y-height/2;
}
QRectF myshape::getCLeftUp(){
  return QRectF(this->x-thick,this->y-thick, thick*2,thick*2);
}
QRectF myshape::getCLeftDown(){
  return QRectF(this->x-thick,this->y-thick+this->height, thick*2, thick*2);
}
QRectF myshape::getCRightUp(){
  return QRectF(this->x-thick+this->widght,this->y-thick, thick*2, thick*2);
}
QRectF myshape::getCRightDown(){
  return QRectF(this->x+ this->widght-thick,this->y+this->height-thick, thick*2, thick*2);
}

void myshape::resize(int pos, int nx, int ny){
  if (pos == 0){
      int fx = x + widght;
      int fy = y + height;
      x = nx;
      y = ny;
      widght = fx -nx;
      height = fy - ny;
    }
  else if (pos == 1){
      int fx = x + widght;
      x = nx;
      widght = fx - x;
      height = ny - y;
    }
  else if (pos == 2){
      int fy = y + height;
      y = ny;
      widght = nx - x;
      height = fy - ny;
    }
  else if (pos == 3){
      widght = nx - x;
      height = ny - y;
    }
}
