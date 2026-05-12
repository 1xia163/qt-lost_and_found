#include "postdialog.h"
#include <QVBoxLayout>
#include <QLabel>


PostDialog::PostDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("发布信息");
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("物品名称/标题:"));
    titleEdit = new QLineEdit(this);
    layout->addWidget(titleEdit);

    layout->addWidget(new QLabel("详细描述:"));
    detailEdit = new QTextEdit(this);
    detailEdit->setMaximumHeight(120);
    layout->addWidget(detailEdit);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QString PostDialog::getTitle() const {
    return titleEdit->text().trimmed();
}

QString PostDialog::getDetail() const {
    return detailEdit->toPlainText().trimmed();
}