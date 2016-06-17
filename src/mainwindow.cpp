#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtMath>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//disable scrollbar (horizontal)
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//disable scrollbar (vertical)
    ui->graphicsView->setBackgroundBrush(QImage(":/image/Loading_screen.png").scaled(width(),height()));
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    startButton=new QPushButton();
    startButton->setGeometry(0,0,75,75);
    startButton->setText("START");
    connect(startButton,SIGNAL(clicked()),this,SLOT(startGame()));
     scene->addWidget(startButton);
    exitButton=new QPushButton();
    exitButton->setGeometry(0,75,75,75);
    exitButton->setText("EXIT");
 connect(exitButton,SIGNAL(clicked()),this,SLOT(exitGame()));
    scene->addWidget(exitButton);


    ui->graphicsView->setScene(scene);

}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
 QMouseEvent* mouseEvent = (QMouseEvent*)event;
    // Hint: Notice the Number of every event!
 if(currentBird==NULL||QRectF(0,0,150,300).contains(mouseEvent->pos()))return false;
if(event->type() == QEvent::MouseButtonPress)
    {

std::cout << "Press !" << std::endl ;
if(currentBird!=NULL)
{
 std::cout << "Press !" << std::endl ;
         if(isLaunch&&!abilityUsed){

             currentBird->ability();
             isLaunch=false;
             abilityUsed=true;
        }
        else
        {
             drag=true;
             start=mouseEvent->pos();
             dx=0;
             dy=0;



        }
         return true;

}


/* TODO : add your code here */

    }
if(isLaunch||!drag)return false;
    if(event->type() == QEvent::MouseMove)
    {
       dx = mouseEvent->pos().x()-start.x();
       dy = mouseEvent->pos().y()-start.y();
       dl = pow(pow(dx,2)+pow(dy,2),0.5);
       dl = (dl<1? 1: dl);
       dx = dx*(dl>100? 100: dl)/dl;
       dy = dy*(dl>100? 100: dl)/dl;
       currentBird->setBirdPosition(origin,dx,dy);
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(currentBird!=NULL)
        {
 drag = false;
 currentBird->setLinearVelocity(b2Vec2((float)-dx*0.4,(float)dy*0.4));
  isLaunch=true;
        }

        /* TODO : add your code here */
        //std::cout << "Release !" << std::endl ;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
if(!isEnemyKill){
    if((enemyList[0]->VelocityCheck().x+enemyList[0]->VelocityCheck().y)>1.0||enemyList[0]->positionCheck().x>28.8){

       delete enemyList[0];
        isEnemyKill=true;
    }

}
if(!isBirdStop){
if(currentBird->getbirdPositon().x>28.8f||currentBird->getbirdPositon().x<0||(currentBird->getbirdVelocity().x<0.1&&currentBird->getbirdVelocity().y<0.1&&isLaunch))
{ abilityUsed=false;
    isLaunch=false;
    delete currentBird;
    isBirdStop=true;
    currentBird=NULL;
}
}
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
void MainWindow::exitGame()
{

    close();
}
void MainWindow::startGame()
{  scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    exitButton=new QPushButton();
    exitButton->setGeometry(0,75,75,75);
    exitButton->setText("EXIT");
 connect(exitButton,SIGNAL(clicked()),this,SLOT(exitGame()));
    scene->addWidget(exitButton);
    reButton=new QPushButton();
    reButton->setGeometry(0,0,75,75);
    reButton->setText("RESTART");
    reButton->hide();
    connect(reButton,SIGNAL(clicked()),this,SLOT(restart()));
    scene->addWidget(reButton);

    selectRedButton=new QPushButton();
    selectRedButton->setGeometry(400,0,75,75);
    selectRedButton->setText("RED");
    scene->addWidget(selectRedButton);
    connect(selectRedButton,SIGNAL(clicked()),this,SLOT(selectRed()));
    selectYellowButton=new QPushButton();
    selectYellowButton->setGeometry(475,0,75,75);
    selectYellowButton->setText("YELLOW");
    scene->addWidget(selectYellowButton);
    connect(selectYellowButton,SIGNAL(clicked()),this,SLOT(selectYellow()));
    selectBlackButton=new QPushButton();
    selectBlackButton->setGeometry(550,0,75,75);
    selectBlackButton->setText("BLACK");
    scene->addWidget(selectBlackButton);
    connect(selectBlackButton,SIGNAL(clicked()),this,SLOT(selectBlack()));
    selectWhiteButton=new QPushButton();
    selectWhiteButton->setGeometry(625,0,75,75);
    selectWhiteButton->setText("WHITE");
    scene->addWidget(selectWhiteButton);
    connect(selectWhiteButton,SIGNAL(clicked()),this,SLOT(selectWhite()));
startButton->hide();
reButton->show();
ui->graphicsView->setScene(scene);
ui->graphicsView->setBackgroundBrush(QImage(":/image/background.jpg").scaled(width(),height()));

timer = new QTimer();
// Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(960,110),world,scene));
 itemList.push_back(new sling(5.0, 3.5, 2.0,4.0, QPixmap(":/image/catapult.png").scaled(50, 100), world, scene));

enemyList[0] = new enemy(25.7, 4.5, 0.3f, timer, QPixmap(":/image/pig.png").scaled(60, 60), world, scene);

 itemList.push_back(new block(26.4, 9.0, 3.5, 0.98, timer, QPixmap(":/image/thinwood0.png").scaled(116, 32), world, scene));
 itemList.push_back(new block(24.7, 6.0, 0.6, 2.5, timer, QPixmap(":/image/thinwood1.png").scaled(20, 120), world, scene));
 itemList.push_back(new block(27.7, 6.0,0.6, 2.5, timer, QPixmap(":/image/thinwood1.png").scaled(20,120 ), world, scene));


 connect(timer,SIGNAL(timeout()),this,SLOT(tick()));

    timer->start(100/6);
}
void MainWindow::selectRed()
{ if(currentBird==NULL&&isBirdStop)
    {
        birdList[0]=new redBird(4.0, 7,0.27f,timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
 currentBird=birdList[0];
        isBirdStop=false;


    }


    }
void MainWindow::selectYellow()
{ if(currentBird==NULL&&isBirdStop)
    {
        birdList[1]=new yellowbird(4.0, 6,0.27f,timer,QPixmap(":/image/yellow.png").scaled(height()/9.0,height()/9.0),world,scene);
isBirdStop=false;
currentBird=birdList[1];
    }


    }

void MainWindow::selectWhite()
{ if(currentBird==NULL&&isBirdStop)
    {
        birdList[2]=new whitebird(4.0, 6,0.27f,timer,QPixmap(":/image/white.png").scaled(height()/9.0,height()/9.0),world,scene);
isBirdStop=false;
currentBird=birdList[2];
    }




    }

void MainWindow::selectBlack()
{ if(currentBird==NULL&&isBirdStop)
    {
        birdList[3]=new blackbird(4.0, 6,0.27f,timer,QPixmap(":/image/black.png").scaled(height()/9.0,height()/9.0),world,scene);
 isBirdStop=false;
 currentBird=birdList[3];
    }

    }
void MainWindow::restart()
{
delete timer;

    currentBird=NULL;
    delete world;
itemList.clear();
  isBirdStop=true;
  isEnemyKill=false;
 isLaunch=false;
 abilityUsed=false;

 startGame();

}
