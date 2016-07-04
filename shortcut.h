#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <QWidget>

namespace Ui {
class shortcut;
}

class shortcut : public QWidget
{
    Q_OBJECT

public:
    explicit shortcut(QWidget *parent = 0);
    ~shortcut();

private:
    Ui::shortcut *ui;
};

#endif // SHORTCUT_H
