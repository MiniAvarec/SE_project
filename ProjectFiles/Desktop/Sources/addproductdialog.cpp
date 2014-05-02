#include "addproductdialog.h"
#include "ui_addproductdialog.h"
#include <QFileDialog>
#include <QProcess>

AddProductDialog::AddProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProductDialog)
{
    ui->setupUi(this);
     QProcess *process = new QProcess(this);
        QString program = "explorer.exe";
        QString folder = "C:\\Windows\\System32\\osk.exe";
        process->start(program, QStringList() << folder);
}

AddProductDialog::~AddProductDialog()
{
    delete ui;
}

void AddProductDialog::on_photoBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    if(!fileName.isEmpty())
    {
        ui->productPhotoEdit->setText(fileName);
        QFile f(fileName);
        if(f.open(QIODevice::ReadOnly))
        {
            imageData = f.readAll();
        }
    }
}
