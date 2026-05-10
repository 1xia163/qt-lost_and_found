#ifndef POSTDIALOG_H
#define POSTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialogButtonBox>

class PostDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PostDialog(QWidget *parent = nullptr);

    QString getTitle() const;
    QString getDetail() const;

private:
    QLineEdit *titleEdit;
    QTextEdit *detailEdit;
    QDialogButtonBox *buttonBox;
};

#endif // POSTDIALOG_H
