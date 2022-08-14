#include "additemdialog.h"
#include "ui_additemdialog.h"
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>

AddItemDialog::AddItemDialog(Item *&newItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
    this->newItem = &newItem;
    imageFilePath = "none.png";
    //registering the events
    connect(ui->btnConfirmAdd, &QPushButton::clicked, this, &AddItemDialog::confirmAdd);
    connect(ui->btnLoadImage, &QPushButton::clicked, this, &AddItemDialog::loadItemImage);

    QDir pathDir("./images");

}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}

void AddItemDialog::confirmAdd(){
    QString productName = ui->txtProductName->text();
    int quantity = ui->sbQuantity->value();

    if(productName.trimmed() != "" && quantity >= 1 && quantity <= 1000){
        *newItem = new Item(productName, quantity, imageFilePath);
        this->close();
    } else {
        QMessageBox mb;
        mb.setText("You must have a valid name, and quanitity between 1 and 1000");
        mb.exec();
    }
}

void AddItemDialog::loadItemImage(){
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
