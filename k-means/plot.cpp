#include "plot.h"
#include <ctime>
#include <cstdlib>
#include <QPainter>

Plot::Plot(QWidget *parent) : QWidget(parent)
{
    points.push_back({0,{100,100}});
}

void Plot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this); // Создаём объект отрисовщика
        // Устанавливаем кисть абриса
        if(needCreateNew){

            points.clear();

            /* Проверяем, какой из радиобаттонов выбран
             * */
            std::srand(std::time(nullptr)); // use current time as seed for random generator
            for(int i = 0 ; i < countPoints; i++){
                int randomx = std::rand()/((RAND_MAX + 1)/width());
                int randomy = std::rand()/((RAND_MAX + 1)/height());

                    // Если зелёный, то отрисовываем зеленый круг
                    int colorNumber = 0;
                    painter.setBrush(QBrush(*std::next(colorMap.begin(),colorNumber), Qt::SolidPattern));
                    painter.drawEllipse(randomx, randomy, 5, 5);
                    points.push_back({0,{randomx, randomy}});
            }
            needCreateNew = false;
        }
        else {
            for(int i = 0 ; i < countPoints; i++){
                    // Если зелёный, то отрисовываем зеленый круг
                    int colorNumber = std::next(points.begin(),i)->first;
                    painter.setBrush(QBrush(*std::next(colorMap.begin(),colorNumber), Qt::SolidPattern));
                    int x = std::next(points.begin(),i)->second.first;
                    int y = std::next(points.begin(),i)->second.second;
                    painter.drawEllipse(x, y, 5, 5);
            }
        }

}

void Plot::setPoints(const std::list<std::pair<int, std::pair<int, int> > > &value)
{
    points = value;
}

void Plot::setNeedCreateNew(bool value)
{
    needCreateNew = value;
}

std::list<std::pair<int,std::pair<int,int>>> Plot::getPoints() const
{
    return points;
}

void Plot::setCountPoints(int value)
{
    countPoints = value;
}
