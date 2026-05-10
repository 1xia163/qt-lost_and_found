#include "postdetaildialog.h"
#include <QPixmap>
#include <QDateTime>

PostDetailDialog::PostDetailDialog(const PostData &post, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("帖子详情");
    setFixedSize(340, 500);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("border: none;");

    QWidget *content = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(content);
    layout->setSpacing(12);

    // 标签
    QLabel *tagLabel = new QLabel(post.tag);
    tagLabel->setStyleSheet(
        post.tag == "发现"
            ? "color: #4A90E2; font-size: 13px; background: #E8F0FE; padding: 4px 12px; border-radius: 10px;"
            : "color: #F5A623; font-size: 13px; background: #FFF3E0; padding: 4px 12px; border-radius: 10px;"
        );
    layout->addWidget(tagLabel);

    // 标题
    QLabel *titleLabel = new QLabel(post.title);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #1D1D1F;");
    titleLabel->setWordWrap(true);
    layout->addWidget(titleLabel);
    // 时间
    QLabel *timeLabel = new QLabel(post.time.toString("yyyy年MM月dd日 hh:mm"));
    timeLabel->setStyleSheet("font-size: 12px; color: #C7C7CC;");
    layout->addWidget(timeLabel);

    // 描述
    if (!post.detail.isEmpty()) {
        QLabel *detailLabel = new QLabel(post.detail);
        detailLabel->setStyleSheet("font-size: 14px; color: #8E8E93;");
        detailLabel->setWordWrap(true);
        layout->addWidget(detailLabel);
    }

    // 图片展示
    if (!post.images.isEmpty()) {
        for (const QString &imgPath : post.images) {
            QLabel *imgLabel = new QLabel();
            QPixmap pixmap(imgPath);
            imgLabel->setPixmap(pixmap.scaledToWidth(300, Qt::SmoothTransformation));
            imgLabel->setAlignment(Qt::AlignCenter);
            layout->addWidget(imgLabel);
        }
    }

    // 联系方式
    bool hasContact = !post.qq.isEmpty() || !post.wechat.isEmpty() || !post.phone.isEmpty();
    if (hasContact) {
        QLabel *contactTitle = new QLabel("联系方式");
        contactTitle->setStyleSheet("font-size: 15px; font-weight: bold; color: #1D1D1F; margin-top: 8px;");
        layout->addWidget(contactTitle);

        if (!post.qq.isEmpty()) {
            QLabel *qqLabel = new QLabel("QQ：" + post.qq);
            qqLabel->setStyleSheet("font-size: 14px; color: #4A90E2;");
            layout->addWidget(qqLabel);
        }
        if (!post.wechat.isEmpty()) {
            QLabel *wechatLabel = new QLabel("微信：" + post.wechat);
            wechatLabel->setStyleSheet("font-size: 14px; color: #4A90E2;");
            layout->addWidget(wechatLabel);
        }
        if (!post.phone.isEmpty()) {
            QLabel *phoneLabel = new QLabel("电话：" + post.phone);
            phoneLabel->setStyleSheet("font-size: 14px; color: #4A90E2;");
            layout->addWidget(phoneLabel);
        }
    }

    layout->addStretch();

    scrollArea->setWidget(content);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(scrollArea);
}