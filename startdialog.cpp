#include "startdialog.h"
#include "ui_startdialog.h"
#include "drawpos.h"

#include "mspcomms.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    ui->comboBox->insertItems(0, MspComms::getPortNames());

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(portSelected()));
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::portSelected() {
    p.show();
    this->close();
}
