#include "seller_mw.h"
#include "ui_seller_mw.h"

seller_mw::seller_mw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::seller_mw)
{
    ui->setupUi(this);

    connect(ui->flash,SIGNAL(clicked()),this,SLOT(on_flash_clicked()));
    connect(ui->gflash,SIGNAL(clicked()),this,SLOT(on_gflash_clicked()));

    // disable edit
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // bind a row
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    // fill the table
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // initial the table's head
    QStringList HStrList;
    HStrList.push_back(QString("出货单号"));
    HStrList.push_back(QString("货号"));
    HStrList.push_back(QString("货品名称"));
    HStrList.push_back(QString("货品存放地"));
    HStrList.push_back(QString("货品产家"));
    HStrList.push_back(QString("出货量"));
    HStrList.push_back(QString("是否审批"));
    HStrList.push_back(QString("审批人"));
    HStrList.push_back(QString("申请日期"));
    int HlableCnt = HStrList.count();
    ui->table->setRowCount(0);
    ui->table->setColumnCount(HlableCnt);
    ui->table->setHorizontalHeaderLabels(HStrList);

    // ini gtable
    ui->gtable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // bind a row
    ui->gtable->setSelectionBehavior(QAbstractItemView::SelectRows);
    // fill the table
    ui->gtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // initial the table's head
    QStringList gHStrList;
    gHStrList.push_back(QString("货号"));
    gHStrList.push_back(QString("货品名称"));
    gHStrList.push_back(QString("货品存放地"));
    gHStrList.push_back(QString("货品产家"));
    gHStrList.push_back(QString("库存量"));
    gHStrList.push_back(QString("是否缺货"));
    int gHlableCnt = gHStrList.count();
    ui->gtable->setRowCount(0);
    ui->gtable->setColumnCount(gHlableCnt);
    ui->gtable->setHorizontalHeaderLabels(gHStrList);
}

seller_mw::~seller_mw()
{
    delete ui;
}

void seller_mw::on_logout_clicked(){
    emit logout_signal();
    return;
}

void seller_mw::on_flash_clicked(){
    emit flash_signal();
    return;
}

void seller_mw::on_submit_clicked(){
    QString request;
    request = "5,"+ui->gname->text()+","+ui->gplace->text()+","+ui->gmanu->text()+","+ui->gnum->text();
    emit submit_signal(request);
    return;
}

void seller_mw::on_gflash_clicked(){
    emit gflash_signal();
    return;
}

void seller_mw::proc_response_flash(QString response){
    /* response's construct:
     *     response_type, alarm_message, flash_flag, pono, gno, gnum, auti_flag, ano, date
     */
    QString section1 = response.section(",",1,1);// get alarm_message
    int section2 = response.section(",",2,2).toInt();// if flash
    int section3 = response.section(",",3,3).toInt();// 进货单号
    int section4 = response.section(",",4,4).toInt();// 货号
    int section5 = response.section(",",5,5).toInt();// 进货量
    QString section6 = response.section(",",6,6);// 是否审批
    QString section7 = response.section(",",7,7);// 审批人
    QString section8 = response.section(",",8,8);// 申请日期
    QString section9 = response.section(",",9,9);// 商品名
    QString section10 = response.section(",",10,10);// 存放地
    QString section11 = response.section(",",11,11);// 产家

    if(section2){
        // flash table
        row = 0;
        ui->table->setRowCount(row);
    }
    else{
        // insert data to table
        ui->table->setRowCount(row+1);
        ui->table->setItem(row,0,new QTableWidgetItem(QString::number(section3)));//单号
        ui->table->setItem(row,1,new QTableWidgetItem(QString::number(section4)));//货号
        ui->table->setItem(row,2,new QTableWidgetItem(section9));//货名
        ui->table->setItem(row,3,new QTableWidgetItem(section10));//存放地
        ui->table->setItem(row,4,new QTableWidgetItem(section11));//厂家
        ui->table->setItem(row,5,new QTableWidgetItem(QString::number(section5)));//进货量
        ui->table->setItem(row,6,new QTableWidgetItem(section6));//是否审批
        ui->table->setItem(row,7,new QTableWidgetItem(section7));//审批人
        ui->table->setItem(row,8,new QTableWidgetItem(section8));//申请日期

        for(int i = 0; i < 9; i++){
            ui->table->item(row, i)->setTextAlignment(Qt::AlignCenter);
        }

        row++;
    }
    return;
}

void seller_mw::proc_response_submit(QString response){
    /* response's construct:
     *     response_type, alarm_message, legal_flag
     */
    QString section1 = response.section(",",1,1);// get alarm_message

    msgBox = new QMessageBox("提示",		///--这里是设置消息框标题
        section1,						///--这里是设置消息框显示的内容
        QMessageBox::Critical,							///--这里是在消息框显示的图标
        QMessageBox::Ok | QMessageBox::Default,		///---这里是显示消息框上的按钮情况
        QMessageBox::Cancel | QMessageBox::Escape,	///---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件
        0);														///---这里是 定义第三个按钮， 该例子 只是 了显示2个按钮
    msgBox->show();

    return;
}

void seller_mw::proc_response_gflash(QString response){
    /* response's construct:
     *     response_type, alarm_message, flash_flag, pono, gno, gnum, auti_flag, ano, date
     */
    QString section1 = response.section(",",1,1);// get alarm_message
    int section2 = response.section(",",2,2).toInt();// if_flash
    int section3 = response.section(",",3,3).toInt();// 货号
    QString section4 = response.section(",",4,4);// 商品名
    QString section5 = response.section(",",5,5);// 存放地
    QString section6 = response.section(",",6,6);// 产家
    int section7 = response.section(",",7,7).toInt();// 进货量
    QString section8 = response.section(",",8,8);// 是否缺货


    if(section2){
        // flash table
        g_row = 0;
        ui->gtable->setRowCount(g_row);
    }
    else{
        // insert data to table
        ui->gtable->setRowCount(g_row+1);
        ui->gtable->setItem(g_row,0,new QTableWidgetItem(QString::number(section3)));//货号
        ui->gtable->setItem(g_row,1,new QTableWidgetItem(section4));//货名
        ui->gtable->setItem(g_row,2,new QTableWidgetItem(section5));//存放地
        ui->gtable->setItem(g_row,3,new QTableWidgetItem(section6));//厂家
        ui->gtable->setItem(g_row,4,new QTableWidgetItem(QString::number(section7)));//进货量
        ui->gtable->setItem(g_row,5,new QTableWidgetItem(section8));//缺货

        for(int i = 0; i < 6; i++){
            ui->gtable->item(g_row, i)->setTextAlignment(Qt::AlignCenter);
        }

        g_row++;
    }
    return;
}
