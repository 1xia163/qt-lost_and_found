#ifndef USERDATA_H
#define USERDATA_H

#include <QString>

struct UserData {
    QString nickname = "用户小王";
    QString studentId = "20260001";
    QString bio = "乐于助人，经常捡到东西";
    QString avatarPath = ":/images/default_avatar.png";
};

#endif // USERDATA_H