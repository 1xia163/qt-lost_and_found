#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "userdata.h"

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

    void refreshUserInfo();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};



#endif // PROFILEPAGE_H