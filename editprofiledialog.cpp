#include "editprofiledialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>

EditProfileDialog::EditProfileDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("编辑个人资料");
    setFixedSize(320, 280);
    setStyleSheet("QDialog { background-color: #FFE7CC; }");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(16);

    // 昵称
    QLabel *nicknameLabel = new QLabel("昵称");
    nicknameLabel->setStyleSheet("font-size: 14px; color: #1D1D1F;");
    layout->addWidget(nicknameLabel);

    nicknameEdit = new QLineEdit();
    nicknameEdit->setPlaceholderText("请输入昵称");
    nicknameEdit->setStyleSheet(
        "border: 1px solid #E5E5E5; border-radius: 8px; padding: 8px; font-size: 14px; background: #F7F8FA;"
        );
    layout->addWidget(nicknameEdit);

    // 简介
    QLabel *bioLabel = new QLabel("个人简介");
    bioLabel->setStyleSheet("font-size: 14px; color: #1D1D1F;");
    layout->addWidget(bioLabel);

    bioEdit = new QTextEdit();
    bioEdit->setMaximumHeight(80);
    bioEdit->setPlaceholderText("介绍一下自己吧...");
    bioEdit->setStyleSheet(
        "border: 1px solid #E5E5E5; border-radius: 8px; padding: 8px; font-size: 14px; background: #F7F8FA;"
        );
    layout->addWidget(bioEdit);

    // 按钮
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText("保存");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QString EditProfileDialog::getNickname() const
{
    return nicknameEdit->text().trimmed();
}

QString EditProfileDialog::getBio() const
{
    return bioEdit->toPlainText().trimmed();
}