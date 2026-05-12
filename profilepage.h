#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "userdata.h"
#include <QSoundEffect>

class ProfilePage : public QWidget
{
    Q_OBJECT
public:
    explicit ProfilePage(QWidget *parent = nullptr);
    void refreshMyPosts();  // 刷新我的帖子列表

private:
    UserData currentUser;
    QVBoxLayout *postListLayout;
    QScrollArea *scrollArea;
    QLabel *nicknameLabel;
    QLabel *bioLabel;
    QLabel *avatarLabel;
    QSoundEffect *clickSound;

    void refreshUserInfo();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};



#endif // PROFILEPAGE_H