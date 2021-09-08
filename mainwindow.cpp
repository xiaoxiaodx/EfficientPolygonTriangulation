#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isShowResult = false;

    showindex = 0;
    // Small test application demonstrating the usage of the triangulate
      // class.


      // Create a pretty complicated little contour by pushing them onto
      // an stl vector.


      a.push_back( Vector2d(0,6));
      a.push_back( Vector2d(0,0));
      a.push_back( Vector2d(3,0));
      a.push_back( Vector2d(4,1));
      a.push_back( Vector2d(6,1));
      a.push_back( Vector2d(8,0));
      a.push_back( Vector2d(12,0));
      a.push_back( Vector2d(13,2));
      a.push_back( Vector2d(8,2));
      a.push_back( Vector2d(8,4));
      a.push_back( Vector2d(11,4));
      a.push_back( Vector2d(11,6));
      a.push_back( Vector2d(6,6));
      a.push_back( Vector2d(4,3));
      a.push_back( Vector2d(2,6));

      //  Invoke the triangulator to triangulate this polygon.
      Triangulate::Process(a,result);

      // print out the results.
//      int tcount = result.size()/3;

//      for (int i=0; i<tcount; i++)
//      {
//        const Vector2d &p1 = result[i*3+0];
//        const Vector2d &p2 = result[i*3+1];
//        const Vector2d &p3 = result[i*3+2];
//        printf("Triangle %d => (%0.0f,%0.0f) (%0.0f,%0.0f) (%0.0f,%0.0f)\n",i+1,p1.GetX(),p1.GetY(),p2.GetX(),p2.GetY(),p3.GetX(),p3.GetY());
//      }

}

void MainWindow::paintEvent(QPaintEvent *pe)
{

    QPainter painter(this);

    QPoint *pt = new QPoint[a.size()];

    for (int i=0;i<a.size();i++) {
        pt[i] = QPoint(a.at(i).GetX()*10,a.at(i).GetY()*10);
    }


    painter.translate(width()/2,height()/2);
    //painter.scale(10.0,10.0);
    painter.drawPolygon(pt,a.size());



    if(isShowResult){

        painter.setPen(QPen(QColor(255,0,0)));
        int tcount = result.size()/3;

        if(showindex >= tcount)
            showindex = 0;
        for (int i=0; i<showindex; i++)
        {
          QPoint *pt1 = new QPoint[3];

          pt1[0] = QPoint(result[i*3+0].GetX()*10,result[i*3+0].GetY()*10);
          pt1[1] = QPoint(result[i*3+1].GetX()*10,result[i*3+1].GetY()*10);
          pt1[2] = QPoint(result[i*3+2].GetX()*10,result[i*3+2].GetY()*10);


          painter.drawPolygon(pt1,3);

        }

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    isShowResult = !isShowResult;
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    showindex++;
    update();

}
