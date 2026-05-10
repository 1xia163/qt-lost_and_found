#include "postdetaildialog.h"
#include <QPixmap>
#include <QDateTime>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QPushButton>

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
            QHBoxLayout *row = new QHBoxLayout();
            QLabel *qqLabel = new QLabel("QQ：" + post.qq);
            qqLabel->setStyleSheet("font-size: 14px; color: #4A90E2;");
            row->addWidget(qqLabel);

            QPushButton *copyBtn = new QPushButton("复制");
            copyBtn->setFixedSize(48, 26);
            copyBtn->setCursor(Qt::PointingHandCursor);
            copyBtn->setStyleSheet(
                "QPushButton {"
                "  color: #4A90E2; font-size: 11px; border: 1px solid #4A90E2;"
                "  border-radius: 10px; background: transparent;"
                "}"
                "QPushButton:hover { background: #E8F0FE; }"
                );
            QString qqStr = post.qq;
            connect(copyBtn, &QPushButton::clicked, this, [this, qqStr]() {
                QApplication::clipboard()->setText(qqStr);
                QMessageBox::information(this, "已复制", "QQ号已复制到剪贴板");
            });
            row->addWidget(copyBtn);
            row->addStretch();
            layout->addLayout(row);
        }

        if (!post.wechat.isEmpty()) {
            QHBoxLayout *row = new QHBoxLayout();
            QLabel *wechatLabel = new QLabel("微信：" + post.wechat);
            wechatLabel->setStyleSheet("font-size: 14px; color: #4A90E2;");
            row->addWidget(wechatLabel);

            QPushButton *copyBtn = new QPushButton("复制");
            copyBtn->setFixedSize(48, 26);
            copyBtn->setCursor(Qt::PointingHandCursor);
            copyBtn->setStyleSheet(
                "QPushButton {"
                "  color: #4A90E2; font-size: 11px; border: 1px solid #4A90E2;"
                "  border-radius: 10px; background: transparent;"
                "}"
                "QPushButton:hover { background: #E8F0FE; }"
                );
            QString wechatStr = post.wechat;
            connect(copyBtn, &QPushButton::clicked, this, [this, wechatStr]() {
                QApplication::clipboard()->setText(wechatStr);
                QMessageBox::information(this, "已复制", "微信号已复制到剪贴板");
            });
            row->addWidget(copyBtn);
            row->addStretch();
            layout->addLayout(row);
        }

        if (!post.phone.isEmpty()) {
            QHBoxLayout *row = new QHBoxLayout();
            QLabel *phoneLabel = new QLabel("电话：" + post.phone);
            phoneLabel->setStyleSheet("font-size: 14px; color: #4A90E2;");
            row->addWidget(phoneLabel);

            QPushButton *copyBtn = new QPushButton("复制");
            copyBtn->setFixedSize(48, 26);
            copyBtn->setCursor(Qt::PointingHandCursor);
            copyBtn->setStyleSheet(
                "QPushButton {"
                "  color: #4A90E2; font-size: 11px; border: 1px solid #4A90E2;"
                "  border-radius: 10px; background: transparent;"
                "}"
                "QPushButton:hover { background: #E8F0FE; }"
                );
            QString phoneStr = post.phone;
            connect(copyBtn, &QPushButton::clicked, this, [this, phoneStr]() {
                QApplication::clipboard()->setText(phoneStr);
                QMessageBox::information(this, "已复制", "电话号码已复制到剪贴板");
            });
            row->addWidget(copyBtn);
            row->addStretch();
            layout->addLayout(row);
        }
    }

    layout->addStretch();

    scrollArea->setWidget(content);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(scrollArea);
}