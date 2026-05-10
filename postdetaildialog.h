#ifndef POSTDETAILDIALOG_H
#define POSTDETAILDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include "postdata.h"

class PostDetailDialog : public QDialog {
    Q_OBJECT
public:
    explicit PostDetailDialog(const PostData &post, QWidget *parent = nullptr);
};

#endif // POSTDETAILDIALOG_H
