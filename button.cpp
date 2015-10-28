#include "button.h"

#include <QPixmap>

Button::Button(QGraphicsScene *scene): QGraphicsPixmapItem()
{
    this->scene = scene;
    size = QSize(50, 50);
    setPixmap(QPixmap(BTN_BLUE).scaled(size,
                                       Qt::IgnoreAspectRatio,
                                       Qt::SmoothTransformation));  //imagem do botão;
    setTransformOriginPoint(this->pixmap().width()/2,
                            this->pixmap().height()/2);             //define o ponto de rotação
    setRotation(0);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setPixmap(QPixmap(BTN_SILVER).scaled(size,
                                       Qt::IgnoreAspectRatio,
                                       Qt::SmoothTransformation));  //imagem do botão;
    ClickOn();
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setPixmap(QPixmap(BTN_BLUE).scaled(size,
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation));  //imagem do botão;
    ClickOff();
}

QSize Button::Size()
{
    return size;
}

