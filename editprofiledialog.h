#ifndef EDITPROFILEDIALOG_H
#define EDITPROFILEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

class EditProfileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EditProfileDialog(QWidget *parent = nullptr);

    QString getNickname() const;
    QString getBio() const;

private:
    QLineEdit *nicknameEdit;
    QTextEdit *bioEdit;
};

#endif // EDITPROFILEDIALOG_H