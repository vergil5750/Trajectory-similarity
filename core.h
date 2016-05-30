#ifndef CORE_H
#define CORE_H

#include <QString>
#include <QFileDialog>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include "sequence.h"
#include "csv.h"

struct PointCompare{
  int index1;
  int index2;
  double distance;
};

//struct PointCollection{
//    QVector<int>p1;
//    QVector<int>p2;
//};


struct SecCompare{
    int beginIndex1;//起点1
    int endIndex1;//终点1
    int beginIndex2;
    int endIndex2;
    double simliarity;//轨迹段相似度
};

QVector<SecCompare> getBestSce(QVector<SecCompare> secCompareV_a,int a);
void initMemSpace(Sequence *p, Sequence *q);
void getSquFromFile(Csv *csv, Sequence *se);
double computeDiscreteFrechet(Sequence *sa,Sequence *sb);
double computeDFD(int i,int j, Sequence *p_a, Sequence * q_a);
double euclideanDistance(Point a, Point b);
double  getSecSim(int i1,int j1,int i2,int j2);
bool compare(SecCompare s1,SecCompare s2);
QVector<SecCompare> findSimilarSection(Sequence *se_a, Sequence *se_b,int a);//调用以计算轨迹段
void calculateSec(int gap, int h,QVector<SecCompare>&q1);
void mergeChange(int gap,QVector<SecCompare>&q1,QVector<SecCompare>&q2);
Sequence* longestCommonSeq(Sequence &p, Sequence &q, double thres);
Point getCenterPoint(Sequence *se_a, int num);
Point getCenterPoint(QVector<Sequence> seqV);
Time &loadToStruct(QString time);
bool timeCompare(Point*p1,Point*p2);
double calTimeDistance(Point &a,Point &b);
double calCoef();
QVector<SecCompare> findBest(Sequence*p,Sequence*q,int &beginMin1,int &beginMin2);
QVector<QVector<int> > getSimplify(Sequence*p,Sequence*q,int& beginMin1,int& beginMin2);
QVector<PointCompare> getNearestPoint(Sequence *se_a, Sequence *se_b);
bool compareDis(PointCompare p1,PointCompare p2);
void out2DArray(double **arr, int x, int y);
void getSec(int m, int n);
double computeDFD_new(int startx, int endx, int starty, int endy);
#endif // CORE_H
