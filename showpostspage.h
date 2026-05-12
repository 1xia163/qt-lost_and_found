#ifndef SHOWPOSTSPAGE_H
#define SHOWPOSTSPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include "postdata.h"
#include <QSoundEffect>

class ShowPostsPage : public QWidget {
    Q_OBJECT
public:
    explicit ShowPostsPage(const QString &tag, QWidget *parent = nullptr);

private:
    void loadPosts();
    void onImageClicked(int index);

    QString tag;
    QList<PostData> posts;
    QGridLayout *gridLayout;
    QWidget *gridWidget;
    QSoundEffect *clickSound;
};

#endif // SHOWPOSTSPAGE_H
