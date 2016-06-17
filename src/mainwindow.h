#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"sling.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include<QPushButton>
#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include"redbird.h"
#include"enemy.h"
#include"block.h"
#include"blackbird.h"
#include"yellowbird.h"
#include"whitebird.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    void startGame();
    void exitGame();
    void selectRed();
    void selectBlack();
    void selectYellow();
    void selectWhite();
    void restart();
    // For debug slot
    void QUITSLOT();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer *timer= new QTimer;
    QPushButton *startButton;
    QPushButton *exitButton;
    QPushButton *reButton;
    QPushButton *selectRedButton;
    QPushButton *selectBlackButton;
    QPushButton *selectYellowButton;
    QPushButton *selectWhiteButton;
    Bird *currentBird=NULL;
    Bird *birdList[4];
    enemy*enemyList[3];
    bool isBirdStop=true;
bool isLaunch=false;
bool abilityUsed=false;
QRectF dragBox;
   int dx, dy, dl;
bool drag=false;
bool isEnemyKill=false;
QPointF start, origin=QPointF(133,340);
};

#endif // MAINWINDOW_H
