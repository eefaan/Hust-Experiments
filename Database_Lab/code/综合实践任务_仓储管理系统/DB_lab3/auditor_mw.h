#ifndef AUDITOR_MW_H
#define AUDITOR_MW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class auditor_mw;
}

class auditor_mw : public QMainWindow
{
    Q_OBJECT

public:
    explicit auditor_mw(QWidget *parent = nullptr);
    ~auditor_mw();

private:
    Ui::auditor_mw *ui;
    QMessageBox *msgBox;
    int po_row;
    int so_row;
    int g_row;

// send to login_mw to process
signals:
    void logout_signal();
    void poflash_signal();
    void posubmit_signal(QString request);
    void soflash_signal();
    void sosubmit_signal(QString request);
    void gflash_signal();
// transfer button_clicked to outside signals
public slots:
    void on_logout_clicked();
    void on_poflash_clicked();
    void on_posubmit_clicked();
    void on_soflash_clicked();
    void on_sosubmit_clicked();
    void on_gflash_clicked();

// function programming, do something after reciving responses.
public:
    void proc_response_poflash(QString response);
    void proc_response_posubmit(QString response);
    void proc_response_soflash(QString response);
    void proc_response_sosubmit(QString response);
    void proc_response_gflash(QString response);
};

#endif // AUDITOR_MW_H
