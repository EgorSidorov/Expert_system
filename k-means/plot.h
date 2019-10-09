#ifndef PLOT_H
#define PLOT_H

#include <QObject>
#include <QWidget>

class Plot : public QWidget
{
    Q_OBJECT
public:
    explicit Plot(QWidget *parent = nullptr);

    void setCountPoints(int value);

    std::list<std::pair<int,std::pair<int,int>>> getPoints() const;

    void setNeedCreateNew(bool value);

    void setPoints(const std::list<std::pair<int, std::pair<int, int> > > &value);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    int countPoints = 0;
    std::list<std::pair<int,std::pair<int,int>>> points;
    bool needCreateNew = false;
    std::list<QColor> colorMap {Qt::green, Qt::red, Qt::yellow, Qt::blue, Qt::black};

};

#endif // PLOT_H
