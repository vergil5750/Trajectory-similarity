#include "searchwin.h"
#include "ui_mainwindow.h"
SearchWin::SearchWin(Ui::MainWindow *ui,DataBase *db)
{
    this->ui = ui;
    this->db = db;
    input = new Sequence();
    time = false;
    distinct = true;
    numOfSeqs = 3;
    tracs = new QStringList();
    rowcount = 0;
    db = new DataBase(1);
    ui->searchMap->initJS();
    ui->searchMap->reload();
    initTable(ui->searchTable_common);
    initTable(ui->searchTable_common_part);
    initTable(ui->searchTable_common_point);
    initTable(ui->searchTable_time);
    initTable(ui->searchTable_time_part);
    initTable(ui->searchTable_time_point);
    initSeqPartTable(ui->searchTable_common_part);
    initSeqPartTable(ui->searchTable_time_part);
    initPointTable(ui->searchTable_common_point);
    initPointTable(ui->searchTable_time_point);

    ui->searchStackedWidget->setCurrentIndex(0);
    ui->searchStackedWidget_time->setCurrentIndex(0);
    initSig();
    //refreshTable();
}

void SearchWin::setTracs(QStringList *tracs)
{
    this->tracs = tracs;
}

void SearchWin::setDB(DataBase *db)
{
    this->db = db;
}


SearchWin::~SearchWin()
{
    delete input;
}

void SearchWin::initTable(QTableWidget *table)
{
        table->horizontalHeader()->setStretchLastSection(true);
        table->verticalHeader()->hide();
        table->setContextMenuPolicy(Qt::ActionsContextMenu);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setColumnCount(4);
        table->setRowCount(ROW_NUM);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void SearchWin::initSeqPartTable(QTableWidget *table)
{
    table->setColumnCount(4);
    table->setRowCount(ROW_NUM);
    table->clearContents();
    QStringList header;
    header << tr("ID")
           << tr("PointNumber")
           << tr("StartPoint")
           << tr("EndPoint");
    table->setHorizontalHeaderLabels(header);
}

void SearchWin::initPointTable(QTableWidget *table)
{    
    table->clearContents();
    QStringList header;
    header << "轨迹ID"
           << "点在轨迹中位置"
           << "编号"
           << "";

    table->setHorizontalHeaderLabels(header);
}

void SearchWin::showPartofSeq()
{
    qDebug() << "show Part Of Sequence\n";
}

void SearchWin::drawPoints()
{
    QMap<QString, int> seq_index;
    for (int i = 0; i < seqs.length(); i++)
    {
        seq_index.insert(seqs[i].getID(), i);
    }
    QString sid = "";
    int index1 = 0;
    double dis = 0;
    for (int j = 0; j < rowcount; j ++)
    {
        if (!time)
        {
            sid =  ui->searchTable_common_point->item(j,0)->text();
            index1 =  ui->searchTable_common_point->item(j,1)->text().toInt();
            dis = ui->searchTable_common_point->item(j,3)->text().toDouble();
        }
        else
        {
            sid =  ui->searchTable_time_point->item(j,0)->text();
            index1 = ui->searchTable_time_point->item(j,1)->text().toInt();
            dis = ui->searchTable_time_point->item(j,3)->text().toDouble();
        }

        if (dis > 1)
        {
            break;
        }
       // ui->searchMap->drawPoint(&((seqs[seq_index[sid]])[index1]),"",seq_index[sid],j);
       ui->searchMap->drawPoint(&((seqs[seq_index[sid]])[index1]),"",seq_index[sid],true);
    }
}

void SearchWin::search()
{
    fillTable(*input);//填充三个表格
    if (!time)
    {
        sortPointTable(ui->searchTable_common_point);
    }
    else
    {
        sortPointTable(ui->searchTable_time_point);
    }

    ui->searchMap->initJS();
    ui->searchMap->showPoints(true);
    ui->searchMap->showTimes(true);
    ui->searchMap->setCentralPoint(getCenterPoint(seqs), 5);
    ui->searchMap->drawSequences(seqs);
    drawPoints();
    ui->searchMap->reload();

    qDebug() << "Search Over";
    coincide.clear();
    seqs.clear();
    rowcount = 0;
}

void SearchWin::sortPointTable(QTableWidget *table)
{
    table->sortItems(3, Qt::AscendingOrder);
    int length = rowcount;
    for (int i =0; i < length; i++)
    {
        table->setItem(i,2, new QTableWidgetItem(QString::number(i)));
    }

}

void SearchWin::initSig()
{
    connect(ui->searchStartBtn, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui->searchPartCBox, SIGNAL(clicked()), this, SLOT(rankPartOfSeq()));
    connect(ui->searchSequenceCBox, SIGNAL(clicked()), this, SLOT(rankSeqChecked()));
    connect(ui->searchPointCBox, SIGNAL(clicked()), this, SLOT(rankSeqPointChecked()));
    connect(ui->searchWinBtn, SIGNAL(clicked()), this, SLOT(startSearch()));
}

void SearchWin::fillPointTable(QTableWidget *table, QVector<PointCompare> pointsV, Sequence *se)
{
   // qDebug() << "rowcount = "
     //        << QString::number(rowcount);
    if (distinct)
    {
        if (coincide.contains(se->getID()))
        {
            return;
        }
    }
    int start = rowcount;
    int end = start + pointsV.length();
    if (end > rowcount)
    {
        table->setRowCount(end + 10);
    }
    else if (rowcount == 0)
    {
        table->setRowCount(ROW_NUM);
    }
    for (int x = start; x < end; x++)
    {
        table->setItem(x,0, new QTableWidgetItem(se->getID()));
        table->setItem(x,1, new QTableWidgetItem(
                                                QString::number(pointsV[x - start].index1)));

        table->setItem(x,3, new QTableWidgetItem(
                                                QString::number(pointsV[x - start].distance)));
    }
    rowcount = end;
}

void SearchWin::fillTable(Sequence inSeq)
{
    string tb = "importtest";
    QVector<PointCompare> pVec;

    double dfDis;
    double maxDis = 0;
//    if (sf.pts->time == "")
//    {
//        qDebug() << "No time";
//        time = false;
//    }
//    else {
//        time = true;
//        qDebug() << "Has time";
//    }

    int c = 0;
    int t = 0;
    for (int i = 0;i < tracs->length();i++)
    {
        Sequence sf;
        QTableWidgetItem *tItem = new QTableWidgetItem();
        db->getSequenceByID(tb,&sf,QString((*tracs)[i]).toStdString());
        dfDis = computeDiscreteFrechet(&inSeq,&sf);
        if (dfDis == 0)
        {
            coincide << sf.getID();
        }
        tItem->setData(Qt::DisplayRole,dfDis);
        pVec = getNearestPoint(&inSeq, &sf);

        if (sf.hasTime() && inSeq.hasTime())
        {
            ui->searchTable_time->setItem(t,2,tItem);
            fillPointTable(ui->searchTable_time_point, pVec, &sf);
            t++;
        }
        else if (!sf.hasTime() && !inSeq.hasTime())
        {
            ui->searchTable_common->setItem(c,2,tItem);
            fillPointTable(ui->searchTable_common_point, pVec, &sf);
            c++;
        }
        if (dfDis >= maxDis)
        {
            maxDis = dfDis;
        }
    }
    seqs.append(inSeq);
    if ( c != 0)
    {
        time = false;
        ui->searchTable_common->sortItems(2,Qt::AscendingOrder);
        for (int i = 0; i < c; i++)
        {
            Sequence sf;
            if (i < numOfSeqs) {
                QString id = ui->searchTable_common->item(i, 0)->text();
                db->getSequenceByID(tb,&sf,id.toStdString());
                seqs.append(sf);
            }

            QTableWidgetItem *tItem = new QTableWidgetItem();
            double dis = ui->searchTable_common->item(i, 2)->text().toDouble();
            double percent = (maxDis - dis)/maxDis * 100;
            if (percent < 0)
            {
                percent = 0;
            }
            tItem->setData(Qt::DisplayRole,
                           QString::number(percent) + "%");
            ui->searchTable_common->setItem(i,3,tItem);
        }
    }
    else if (t != 0)
    {
        time = true;
        ui->searchTable_time->sortItems(2,Qt::AscendingOrder);
        for (int i = 0; i < t; i++)
        {
            Sequence sf;
            if (i < numOfSeqs)
            {
                QString id = ui->searchTable_time->item(i, 0)->text();
                db->getSequenceByID(tb,&sf,id.toStdString());
                seqs.append(sf);
            }
            QTableWidgetItem *tItem = new QTableWidgetItem();
            double dis = ui->searchTable_time->item(i, 2)->text().toDouble();
            double percent = (maxDis - dis)/maxDis * 100;
            if (percent < 0)
            {
                percent = 0;
            }
            tItem->setData(Qt::DisplayRole,
                           QString::number(percent) + "%");
            ui->searchTable_time->setItem(i,3,tItem);
        }
    }
}

void SearchWin::refreshTable()
{
    initSeqPartTable(ui->searchTable_common_part);
    initSeqPartTable(ui->searchTable_time_part);
    initPointTable(ui->searchTable_common_point);
    initPointTable(ui->searchTable_time_point);
    ui->searchTable_common->clearContents();
    ui->searchTable_time->clearContents();
    QStringList header;
    header << tr("ID")
           << tr("PointNumber")
           << tr("Frechet Distance")
           << tr("Similarity");
    ui->searchTable_common->setHorizontalHeaderLabels(header);
    ui->searchTable_time->setHorizontalHeaderLabels(header);
    if (tracs->length() == 0)
    {
        ui->searchTable_common->clearContents();
        ui->searchTable_time->clearContents();
    }
    else {
        int pos_c = 0;
        int pos_t = 0;
        if (tracs->length() > ROW_NUM)
        {
            ui->searchTable_common->setRowCount(tracs->length() + 10);
            ui->searchTable_time->setRowCount(tracs->length() + 10);
        }
        else
        {
            ui->searchTable_common->setRowCount(ROW_NUM);
            ui->searchTable_time->setRowCount(ROW_NUM);
        }
        for(int i = 0; i < tracs->length();i++)
        {
            QString temp = (*tracs)[i];
            if (db->hasTime(temp.toStdString(),"importtest"))
            {
                ui->searchTable_time->setItem(pos_t,0, new QTableWidgetItem(temp));
                ui->searchTable_time->setItem(pos_t,1,
                                   new QTableWidgetItem(QString::number(db->getPointNumByID(temp.toStdString()))));
                pos_t ++;
            }
            else
            {
                ui->searchTable_common->setItem(pos_c,0, new QTableWidgetItem(temp));
                ui->searchTable_common->setItem(pos_c,1,
                                   new QTableWidgetItem(QString::number(db->getPointNumByID(temp.toStdString()))));
                pos_c ++;
            }
        }
    }

}

void SearchWin::setNumOfSeqs(int num)
{
    numOfSeqs = num;
}

void SearchWin::init()
{

}


void SearchWin::openFile()
{

    if (input != NULL)
    {
        delete input;
        input = new Sequence();
    }
    QString file_name = QFileDialog::getOpenFileName(NULL,
            tr("Open File"),
            "",
            "CSV Files(*.csv)",
            0);
    if (!file_name.isNull())
        {
            qDebug()<<file_name;
        }
        else{
            return;
    }
    string fileName = file_name.toLocal8Bit().data();
    ifstream fin(fileName.c_str());
    Csv csv(fin);
    getSquFromFile(&csv,input);
    ui->searchPathEdit->setText(file_name);
}

void SearchWin::rankPartOfSeq()
{
    bool flag = (ui->searchPartCBox->isChecked());
    if (flag)
    {
        ui->searchStackedWidget->setCurrentIndex(2);
        ui->searchStackedWidget_time->setCurrentIndex(2);
        showPartofSeq();
    }
    else
    {
        ui->searchStackedWidget->setCurrentIndex(0);
        ui->searchStackedWidget_time->setCurrentIndex(0);
    }
}

void SearchWin::rankSeqChecked()
{
    bool flag = (ui->searchSequenceCBox->isChecked());
    if (flag)
    {
        ui->searchStackedWidget->setCurrentIndex(0);
        ui->searchStackedWidget_time->setCurrentIndex(0);
        showPartofSeq();
    }
    else
    {
        ui->searchStackedWidget->setCurrentIndex(0);
        ui->searchStackedWidget_time->setCurrentIndex(0);
    }
}

void SearchWin::rankSeqPointChecked()
{
    bool flag = (ui->searchPointCBox->isChecked());
    if (flag)
    {
        ui->searchStackedWidget->setCurrentIndex(1);
        ui->searchStackedWidget_time->setCurrentIndex(1);
        showPartofSeq();
    }
    else
    {
        ui->searchStackedWidget->setCurrentIndex(0);
        ui->searchStackedWidget_time->setCurrentIndex(0);
    }
}

void SearchWin::startSearch()
{
    this->ui->searchMap->initJS();
    this->ui->searchMap->setDefaultCentralPt();
    this->ui->searchMap->reload();
    refreshTable();
    init();

    if (input->getNum() == 0)
    {
        return;
    }
    search();
}

