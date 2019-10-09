#ifndef K_MEANS_H
#define K_MEANS_H

#include <utility>
#include <list>

class k_means
{
public:
    k_means();
    void setCountCenters(int value);

    void setMaxx(int value);

    void setMaxy(int value);

    void compute();

    void setPoints(std::list<std::pair<int, std::pair<int, int> > > value);

    std::list<std::pair<int, std::pair<int, int> > > getPoints() const;

private:
    int countCenters;
    int maxx;
    int maxy;
    std::list< std::pair<int,std::pair<int,int>> > points;
    std::list< std::pair<int,int> > centers;

    std::pair<int,int> find_center(int number_cluster);
    void setRandomCenters();
    int detect_sqrt(std::pair<int, int> first, std::pair<int, int> second);
    int detect_min_center(std::pair<int,int>);
};

#endif // K_MEANS_H
