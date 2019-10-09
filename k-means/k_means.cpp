#include "k_means.h"
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <QDebug>

k_means::k_means()
{
    maxx = 0;
    maxy = 0;
}

void k_means::setCountCenters(int value)
{
    countCenters = value;
}

void k_means::setMaxx(int value)
{
    maxx = value;
}

void k_means::setMaxy(int value)
{
    maxy = value;
}

void k_means::compute()
{
    setRandomCenters();
    auto last_center = centers;
    last_center.clear();
    for(auto iter : centers)
        last_center.push_back({0,0});
    qDebug()<<"begin centers";
    qDebug()<<centers;
    int number = 0;
    while(last_center != centers){
        qDebug()<<"iter "<<number;
        number++;
        last_center = centers;
        for(auto& iter : points){
            iter.first = detect_min_center(iter.second);
        }

        for(int i = 0; i < countCenters; i++){
            int countLocalPoint = 0;
            int sumx = 0;
            int sumy = 0;
            for(auto& iter2 : points){
                if(iter2.first == i){
                    countLocalPoint++;
                    sumx += iter2.second.first;
                    sumy += iter2.second.second;
                }
            }
            int localCenterX = 1;
            int localCenterY = -1;
            if(countLocalPoint)
            {
                localCenterX = sumx / countLocalPoint;
                localCenterY = sumy / countLocalPoint;
                //qDebug()<<localCenterX;
                //qDebug()<<localCenterY;
                std::next(centers.begin(), i)->first = localCenterX;
                std::next(centers.begin(), i)->second = localCenterY;
            }

        }


    }
    qDebug()<<"end centers";
    qDebug()<<centers;
}

void k_means::setPoints(std::list<std::pair<int, std::pair<int, int> > > value)
{
    points = value;
}

std::list<std::pair<int, std::pair<int, int> > > k_means::getPoints() const
{
    return points;
}

int k_means::detect_sqrt(std::pair<int,int> first_el, std::pair<int,int> second_el)
{
    return sqrt(pow(first_el.first-second_el.first,2)- pow(first_el.second-second_el.second,2));
}

int k_means::detect_min_center(std::pair<int,int> point){
    int min = INT_MAX;
    int return_val = -1;
    for(int i = 0; i < countCenters; i++){
        int result = detect_sqrt(point, find_center(i));
        if(result < min){
            min = result;
            return_val = i;
        }
    }
    //qDebug()<<point;
    //qDebug()<<min;
    //qDebug()<<return_val;
    return return_val;
}

std::pair<int, int> k_means::find_center(int number_cluster)
{
    if(number_cluster > countCenters){
        qDebug()<<"error";
        return {-1,-1};
    }
    return *std::next(centers.begin(), number_cluster);
}

void k_means::setRandomCenters()
{
    std::srand(std::time(nullptr));
    centers.clear();
    for(int i = 0; i < countCenters; i++){
        int randomx = std::rand()/((RAND_MAX + 1)/maxx);
        int randomy = std::rand()/((RAND_MAX + 1)/maxy);
        centers.push_back({randomx,randomy});
    }
}


