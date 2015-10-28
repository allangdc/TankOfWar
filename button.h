#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QSize>

#define BTN_BLUE    ":/image/buttons/image/arrow_blue.png"
#define BTN_SILVER  ":/image/buttons/image/arrow_silver.png"

class Button: public QGraphicsPixmapItem
{
public:
    explicit Button(QGraphicsScene *scene);
    QSize Size();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void ClickOn() = 0;
    virtual void ClickOff() = 0;
    QGraphicsScene *scene;
private:
    QSize size;
};

#endif // BUTTON_H
