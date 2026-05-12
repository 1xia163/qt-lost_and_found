#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QList>
#include <QSoundEffect>

class PostManager;

class HomePage : public QWidget
{
    Q_OBJECT

signals:
    void goToPost(const QString &tag);

public:
    explicit HomePage(QWidget *parent = nullptr);
    void refreshPosts();

private:
    QListWidget *postList;
    QPushButton *btnDiscover;
    QPushButton *btnSearch;
    QScrollArea *scrollArea;
    QWidget *contentWidget;
    QVBoxLayout *contentLayout;
    QSoundEffect *clickSound;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // HOMEPAGE_H