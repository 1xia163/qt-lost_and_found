#ifndef POSTDETAILDIALOG_H
#define POSTDETAILDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include "postdata.h"
#include <QSoundEffect>

class PostDetailDialog : public QDialog {
    Q_OBJECT
    QSoundEffect *clickSound;
public:
    explicit PostDetailDialog(const PostData &post, QWidget *parent = nullptr);
};

#endif // POSTDETAILDIALOG_H
