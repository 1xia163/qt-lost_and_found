#ifndef POSTDATA_H
#define POSTDATA_H

#include <QString>
#include <QStringList>
#include <QDateTime>

struct PostData {
    QString tag;        // "发现" 或 "寻找"
    QString title;      // 物品名称
    QString detail;     // 详细描述
    QString qq;         // QQ
    QString wechat;     // 微信
    QString phone;      // 电话
    QStringList images; // 图片路径列表
    QDateTime time;     //发布时间
};

#endif // POSTDATA_H