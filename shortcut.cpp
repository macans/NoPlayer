#include "shortcut.h"
#include "ui_shortcut.h"
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
shortcut::shortcut(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shortcut)
{
    ui->setupUi(this);
}

shortcut::~shortcut()
{
    delete ui;



}
