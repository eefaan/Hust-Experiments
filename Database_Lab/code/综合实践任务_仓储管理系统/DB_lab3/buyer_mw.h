#ifndef BUYER_MW_H
#define BUYER_MW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class buyer_mw;
}

class buyer_mw : public QMainWindow
{
    Q_OBJECT

public:
    explicit buyer_mw(QWidget *parent = nullptr);
    ~buyer_mw();

private:
    Ui::buyer_mw *ui;
    QMessageBox *msgBox;
    int row;
    int g_row;

// send to login_mw to process
signals:
    void logout_signal();
    void flash_signal();
    void submit_signal(QString request);
    void gflash_signal();
// transfer button_clicked to outside signals
public slots:
    void on_logout_clicked();
    void on_flash_clicked();
    void on_submit_clicked();
    void on_gflash_clicked();

// function programming, do something after reciving responses.
public:
    void proc_response_flash(QString response);
    void proc_response_submit(QString response);
    void proc_response_gflash(QString response);

};

#endif // BUYER_MW_H
