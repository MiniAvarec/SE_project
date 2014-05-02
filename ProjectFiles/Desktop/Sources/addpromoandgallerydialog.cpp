#include "addpromoandgallerydialog.h"
#include "ui_addpromoandgallerydialog.h"
#include <QFileDialog>
#include <QProcess>

AddPromoAndGalleryDialog::AddPromoAndGalleryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPromoAndGalleryDialog)
{
    ui->setupUi(this);
    QProcess *process = new QProcess(this);
       QString program = "explorer.exe";
       QString folder = "C:\\Windows\\System32\\osk.exe";
       process->start(program, QStringList() << folder);
}

AddPromoAndGalleryDialog::~AddPromoAndGalleryDialog()
{
    delete ui;
}

void AddPromoAndGalleryDialog::on_photoBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    if(!fileName.isEmpty())
    {
        ui->photoEdit->setText(fileName);
        QFile f(fileName);
        if(f.open(QIODevice::ReadOnly))
        {
            imageData = f.readAll();
        }
    }
}
