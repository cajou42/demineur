#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <qgridlayout.h>
#include <QLabel>
#include <QGroupBox>
#include <QElapsedTimer>
#include <QTimer>
#include <string>

class projet_je_sais_pas : public QWidget
{
    Q_OBJECT

public:
    projet_je_sais_pas(QWidget *parent = Q_NULLPTR);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QGridLayout* m_gridLayout;
    void paintEvent(QPaintEvent* event);
    QString GetStyleSheetAsSting(QString Path);
    int check_mine(int, int);
    void createGridGroupBox();
    void gameOver();
    void begin(int, int);
    void win();
    void chooseAsset(int, int);
    QLabel* labels;
    QLabel* labelT;
    int tab[12][14];
    std::string casePath = "C:\\Users\\louis\\source\\repos\\projet_je_sais_pas\\images\\case.png";
    bool asmine = false;
    QLabel* label;
    QTimer* timer;
    void integrityTimersEvent(int);
    int count;
};
