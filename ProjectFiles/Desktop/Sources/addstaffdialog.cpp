#include "addstaffdialog.h"
#include "ui_addstaffdialog.h"
#include <QFileDialog>
#include <QProcess>

AddStaffDialog::AddStaffDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStaffDialog)
{
    ui->setupUi(this);
    QProcess *process = new QProcess(this);
       QString program = "explorer.exe";
       QString folder = "C:\\Windows\\System32\\osk.exe";
       process->start(program, QStringList() << folder);
}

AddStaffDialog::~AddStaffDialog()
{
    delete ui;
}

void AddStaffDialog::on_photoBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    if(!fileName.isEmpty())
    {
        ui->staffPhotoEdit->setText(fileName);
        QFile f(fileName);
        if(f.open(QIODevice::ReadOnly))
        {
            imageData = f.readAll();
        }
    }
}
