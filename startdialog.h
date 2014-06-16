#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

#include "drawpos.h"

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

private:
    Ui::StartDialog *ui;
    DrawPos p;

private slots:
    void portSelected();
};

#endif // STARTDIALOG_H
