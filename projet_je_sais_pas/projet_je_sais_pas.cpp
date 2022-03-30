#include "projet_je_sais_pas.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QObject>
#include <QPointF>
#include <QLabel>
#include <QMessageBox>
#include <QCoreApplication>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <QString>

projet_je_sais_pas::projet_je_sais_pas(QWidget *parent)
    : QWidget(parent)
{
    count = 0;
    setFixedSize(500, 500);

    labelT = new QLabel(this);
    QTimer* t = new QTimer(this);
    t->setInterval(1000);
    t->start();
    connect(t, &QTimer::timeout, this, [=]()->void {integrityTimersEvent(t->timerId()); });
    timer = t;
    label = new QLabel(this);
    //label->setText(QString::number(timer->nsecsElapsed()));
    label->show();
    m_gridLayout = new QGridLayout(this);
    createGridGroupBox();
    setLayout(m_gridLayout);
}

void projet_je_sais_pas::paintEvent(QPaintEvent*) {
    //QPainter painter(this);
    //painter.setPen(Qt::blue);
    //painter.setFont(QFont("Arial", 30));
    //painter.drawText(rect(), Qt::AlignCenter, "Qt");
    //label->setText(QString::number(timer->nsecsElapsed()/60/60));
}

void projet_je_sais_pas::createGridGroupBox()
{
    int nb_mine = 20;
    int cooldown = 0;
    srand(time(NULL));
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 14; j++) {
            
            int random = rand() % 5 + 1;
            QPixmap pixmap("C:\\Users\\louis\\source\\repos\\projet_je_sais_pas\\images\\case.png");
            QPixmap m_pixmap("C:\\Users\\louis\\source\\repos\\projet_je_sais_pas\\images\\mine.png");
            QLabel* label = new QLabel(this);
            label->setPixmap(pixmap);
            label->setScaledContents(true);
            m_gridLayout->addWidget(label, j, i, 1, 1, Qt::AlignHCenter);
            if (random == 5 && nb_mine != 0 && cooldown == 0) {
                if (cooldown == 0)
                    cooldown = 5;
                tab[i][j] = 5;
                label->setPixmap(m_pixmap);
                nb_mine--;
            }
            else {
                tab[i][j] = 0;
            }
            if(cooldown != 0)
                cooldown--;
        }
    }
}

void projet_je_sais_pas::gameOver()
{
    QMessageBox::information(
        this,
        tr("demineur"),
        tr("vous avez perdu"));
    QCoreApplication::quit();
}

void projet_je_sais_pas::begin(int i, int j)
{      
    chooseAsset(i, j);
    if (tab[i][j + 1] == 5 || tab[i][j - 1] == 5 || tab[i + 1][j] == 5 || tab[i - 1][j] == 5 || tab[i - 1][j+1] == 5 || tab[i + 1][j-1] == 5 || tab[i - 1][j-1] == 5 || tab[i + 1][j+1] == 5)
        return;
    if (tab[i][j + 1] != 5 && j < 13) {
        chooseAsset(i, j+1);
    }
    if (tab[i][j + 2] != 5 && j < 12) {
        chooseAsset(i, j+2);
    }
    if (tab[i + 1][j] != 5 && i < 11) {
        chooseAsset(i+1, j);
    }
    if (tab[i + 2][j] != 5 && i < 10) {
        chooseAsset(i+2, j);
    }
    if (tab[i][j - 1] != 5 && j > 0) {
        chooseAsset(i, j-1);
    }
    if (tab[i][j - 2] != 5 && j-2 > 0) {
        chooseAsset(i, j-2);
    }
    if (tab[i - 1][j] != 5 && i > 0) {
        chooseAsset(i-1, j);
    }
    if (tab[i - 2][j] != 5 && i-2 > 0) {
        chooseAsset(i-2, j);
    }
    if (tab[i + 1][j + 1] != 5 && j < 13 && i < 11) {
        chooseAsset(i+1, j+1);
    }
    if (tab[i - 1][j + 1] != 5 && j < 13 && i > 0) {
        chooseAsset(i-1, j+1);
    }
    if (tab[i + 1][j - 1] != 5 && j > 0 && i < 11) {
        chooseAsset(i+1, j-1);
    }
    if (tab[i - 1][j - 1] != 5 && j > 0 && i > 0) {
        chooseAsset(i-1, j-1);
    }
}

void projet_je_sais_pas::win()
{
    bool nope = false;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 14; j++) {
            if (tab[i][j] == 0) {
                nope = true;
            }
        }
    }
    if (nope == false) {
        QMessageBox::information(
            this,
            tr("demineur"),
            tr("vous avez gagne!!!"));
        QCoreApplication::quit();
    }
}

int projet_je_sais_pas::check_mine(int i, int j) {
    int mine = 0;
    if (tab[i][j] == 5)
        gameOver();

            if (tab[i][j + 1] == 5) {
                mine++;
            }
            if(tab[i][j - 1] == 5)
            {
                mine++;
            }
            if (tab[i-1][j] == 5)
            {
                mine++;
            }
            if (tab[i+1][j] == 5)
            {
                mine++;
            }
            if (tab[i-1][j + 1] == 5)
            {
                mine++;
            }
            if (tab[i+1][j + 1] == 5)
            {
                mine++;
            }
            if (tab[i+1][j - 1] == 5)
            {
                mine++;
            }
            if (tab[i-1][j - 1] == 5)
            {
                mine++;
            }

    return mine;
}

void projet_je_sais_pas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        auto toto = m_gridLayout->geometry();
        int posx = event->pos().x() - m_gridLayout->geometry().x();
        int posy = event->pos().y() - m_gridLayout->geometry().y();
        int x =  posx / (m_gridLayout->geometry().width() / 12);
        int y = posy / (m_gridLayout->geometry().height() / 14);
        QLabel* alu = qobject_cast<QLabel*>(m_gridLayout->itemAtPosition(y, x)->widget());
        QPixmap pixmap("C:\\Users\\louis\\source\\repos\\projet_je_sais_pas\\images\\drapeau.png");
        //alu->setText("alu");

        alu->setPixmap(pixmap);
        //alu->setScaledContents(true);
    }
    else if (event->buttons() == Qt::LeftButton) {
        auto toto = m_gridLayout->geometry();
        int posx = event->pos().x() - m_gridLayout->geometry().x();
        int posy = event->pos().y() - m_gridLayout->geometry().y();
        int x = posx / (m_gridLayout->geometry().width() / 12);
        int y = posy / (m_gridLayout->geometry().height() / 14);
        begin(x, y);
        win();
    }
} 

void projet_je_sais_pas::chooseAsset(int x, int y)
{
    int hole = check_mine(x, y);
    QLabel* alu = qobject_cast<QLabel*>(m_gridLayout->itemAtPosition(y, x)->widget());
    switch (hole)
    {
    case 1:
    {QPixmap* pixmap = new QPixmap("C:\\Users\\louis\\source\\repos\\projet_je_sais_pas\\images\\case1.png");
    alu->setPixmap(*pixmap);
    tab[x][y] = 1;
    break; }
    case 2:
    {QPixmap* pixmap2 = new QPixmap("C:\\Users\\louis\\source\\repos\\projet_je_sais_pas\\images\\case2.png");
    alu->setPixmap(*pixmap2);
    tab[x][y] = 2;
    break; }
    case 3:
    {QPixmap* pixmap3 = new QPixmap("C:\\Users\\louis\\source\\repos\\projet_je_sais_pas\\images\\case3.png");
    alu->setPixmap(*pixmap3);
    tab[x][y] = 3;
    break; }
    case 4:
    {QPixmap* pixmap4 = new QPixmap("C:\\Users\\louis\\source\\repos\\projet_je_sais_pas\\images\\case4.png");
    alu->setPixmap(*pixmap4);
    tab[x][y] = 4;
    break; }
    default:
    {QPixmap* pixmap5 = new QPixmap("C:\\Users\\louis\\source\\repos\\projet_je_sais_pas\\images\\case_vide.png");
    alu->setPixmap(*pixmap5);
    tab[x][y] = 6;
    break; }
    }
} 

void projet_je_sais_pas::integrityTimersEvent(int timerID)
{
    qDebug() << "integrityTimersEvent => Timer ID:" << timerID;
    qDebug() << count++;
    labelT->setText(QString("%1 sec").arg(count));
    labelT->show();
    //labelT->close();
}