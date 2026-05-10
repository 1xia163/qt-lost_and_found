#include "profilepage.h"
#include <QVBoxLayout>

ProfilePage::ProfilePage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("个人中心（待完善）");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}