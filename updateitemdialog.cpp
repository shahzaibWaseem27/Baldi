#include "updateitemdialog.h"
#include "ui_updateitemdialog.h"

#include <QFileDialog>
#include <QMessageBox>

UpdateItemDialog::UpdateItemDialog(Item *currentItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateItemDialog)
{
    ui->setupUi(this);
    this->currentItem = currentItem;

    if(currentItem != nullptr){
        ui->lblItemName->setText(currentItem->getName());

        QPixmap pixmap(currentItem->getImageFilePath());
        ui->lblImage->setPixmap(pixmap);
        ui->lblImage->setScaledContents(true);
        ui->sbQuantity->setValue(currentItem->getQuantity());

        imageFilePath = currentItem->getImageFilePath();

    }

    connect(ui->btnConfirmEdit, &QPushButton::clicked, this, &UpdateItemDialog::confirmUpdate);
    connect(ui->btnLoadItemImage, &QPushButton::clicked, this, &UpdateItemDialog::loadItemImage);
}

UpdateItemDialog::~UpdateItemDialog()
{
    delete ui;
}

void UpdateItemDialog::confirmUpdate(){
    int quantity = ui->sbQuantity->value();

    if(quantity >= 1 && quantity <= 1000){
        currentItem->setQuantity(quantity);
        currentItem->setImageFilePath(imageFilePath);
        this->close();
    } else {
        QMessageBox mb;
        mb.setText("Quantity must be between 1 and 1000");
        mb.exec();
    }
}

void UpdateItemDialog::loadItemImage(){
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, "Open Image", "./", "Image Files (*.png *.jpg)");
    if(fileName != ""){
        int lastSlash = fileName.lastIndexOf("/");
        QString shortName = fileName.right(fileName.size() - lastSlash - 1);
        QFile::copy(fileName, "./images/" + shortName);

        QPixmap pixmap("./images/" + shortName);
        ui->lblImage->setPixmap(pixmap);
        ui->lblImage->setScaledContents(true);
        imageFilePath = "./images/" + shortName;
    }
}
















