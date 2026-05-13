#include "profilepage.h"
#include "postmanager.h"
#include "postdetaildialog.h"
#include "postdata.h"
#include "editprofiledialog.h"
#include <QScrollArea>
#include <QPixmap>
#include <QMessageBox>
#include "editprofiledialog.h"
#include <QMouseEvent>
#include <QFileDialog>
#include <QPainter>


ProfilePage::ProfilePage(QWidget *parent) : QWidget(parent)
{
    clickSound = new QSoundEffect(this);

    clickSound->setSource(
        QUrl("qrc:/effects/click.wav")
        );

    clickSound->setVolume(0.5);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background: transparent;");
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(20, 30, 20, 20);
    contentLayout->setSpacing(20);

    // ===== 头像 + 昵称 =====
    avatarLabel = new QLabel();
    avatarLabel->setCursor(Qt::PointingHandCursor);
    avatarLabel->installEventFilter(this);  // 需要事件过滤器
    avatarLabel->setFixedSize(80, 80);
    avatarLabel->setStyleSheet("border-radius: 40px; background: #E5E5E5;");
    QPixmap avatar(currentUser.avatarPath);
    if (!avatar.isNull()) {
        avatarLabel->setPixmap(avatar.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        avatarLabel->setText("👤");
        avatarLabel->setAlignment(Qt::AlignCenter);
        avatarLabel->setStyleSheet("border-radius: 40px; background: #E5E5E5; font-size: 36px;");
    }
    contentLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);

    QLabel *hintLabel = new QLabel("点击修改头像");
    hintLabel->setStyleSheet("font-size: 11px; color: #C7C7CC;");
    hintLabel->setAlignment(Qt::AlignCenter);
    contentLayout->addWidget(hintLabel);


    nicknameLabel = new QLabel(currentUser.nickname);
    nicknameLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #1D1D1F;");
    nicknameLabel->setAlignment(Qt::AlignCenter);
    contentLayout->addWidget(nicknameLabel);

    QLabel *idLabel = new QLabel("学号：" + currentUser.studentId);
    idLabel->setStyleSheet("font-size: 13px; color: #6D4C41;");
    idLabel->setAlignment(Qt::AlignCenter);
    contentLayout->addWidget(idLabel);

    bioLabel = new QLabel(currentUser.bio);
    bioLabel->setStyleSheet("font-size: 13px; color: #6D4C41;");
    bioLabel->setAlignment(Qt::AlignCenter);
    contentLayout->addWidget(bioLabel);

    // 编辑资料按钮
    QPushButton *editBtn = new QPushButton("编辑资料");
    editBtn->setStyleSheet(
        "QPushButton {"
        "  color: #4A90E2; font-size: 14px; border: 1px solid #4A90E2;"
        "  border-radius: 15px; padding: 6px 20px; background: transparent;"
        "}"
        );
    contentLayout->addWidget(editBtn, 0, Qt::AlignCenter);
    connect(editBtn, &QPushButton::clicked, this, [this]() {
       clickSound->play();
        EditProfileDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            QString newNickname = dialog.getNickname();
            QString newBio = dialog.getBio();
            if (!newNickname.isEmpty()) {
                currentUser.nickname = newNickname;
            }
            if (!newBio.isEmpty()) {
                currentUser.bio = newBio;
            }
            QMessageBox::information(this, "成功", "资料已更新，下次进入个人页生效");
        }
    });

    // 分割线
    QWidget *divider = new QWidget();
    divider->setFixedHeight(1);
    divider->setStyleSheet("background:#F0D5BE;");
    contentLayout->addWidget(divider);

    // ===== 我的帖子标题 =====
    QLabel *myPostTitle = new QLabel("我的帖子");
    myPostTitle->setStyleSheet("font-size: 17px; font-weight: bold; color: #1D1D1F;");
    contentLayout->addWidget(myPostTitle);

    // ===== 我的帖子列表 =====
    postListLayout = new QVBoxLayout();
    postListLayout->setSpacing(10);
    contentLayout->addLayout(postListLayout);

    contentLayout->addStretch();

    // 关于
    QLabel *aboutLabel = new QLabel("失物招领 v3.0");
    aboutLabel->setStyleSheet("font-size: 12px; color: #C7C7CC;");
    aboutLabel->setAlignment(Qt::AlignCenter);
    contentLayout->addWidget(aboutLabel);

    scrollArea->setWidget(contentWidget);
    mainLayout->addWidget(scrollArea);

    refreshMyPosts();
}

void ProfilePage::refreshMyPosts()
{
    refreshUserInfo();
    // 清空旧列表
    QLayoutItem *item;
    while ((item = postListLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    QList<PostData> allPosts = PostManager::instance().getPostsByAuthor("user");

    if (allPosts.isEmpty()) {
        QLabel *emptyLabel = new QLabel("还没有发布过帖子");
        emptyLabel->setStyleSheet("font-size: 14px; color: #C7C7CC;");
        emptyLabel->setAlignment(Qt::AlignCenter);
        postListLayout->addWidget(emptyLabel);
        return;
    }

    // 倒序显示，最新的在上面
    for (int i = allPosts.size() - 1; i >= 0; --i) {
        const PostData &post = allPosts[i];

        QWidget *card = new QWidget();
        card->setFixedWidth(335);
        card->setStyleSheet("background: #FFFFFF; border-radius: 8px; border: 1px solid #EEEEEE;");

        QHBoxLayout *cardLayout = new QHBoxLayout(card);
        cardLayout->setContentsMargins(12, 10, 12, 10);
        cardLayout->setSpacing(10);

        // 图片
        QLabel *imgLabel = new QLabel();
        imgLabel->setFixedSize(50, 50);
        imgLabel->setStyleSheet("border-radius: 6px; background: #F2F2F7;");
        if (!post.images.isEmpty()) {
            QPixmap pixmap(post.images.first());
            imgLabel->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            imgLabel->setText("📷");
            imgLabel->setAlignment(Qt::AlignCenter);
        }
        cardLayout->addWidget(imgLabel);

        // 文字
        QVBoxLayout *textLayout = new QVBoxLayout();
        textLayout->setSpacing(4);

        QLabel *titleLabel = new QLabel(post.title);
        titleLabel->setStyleSheet("font-size: 15px; font-weight: bold; color: #1D1D1F; border: none; background: transparent;");
        textLayout->addWidget(titleLabel);

        QLabel *tagLabel = new QLabel(post.tag == "发现" ? " #发现 " : " #寻找 ");
        if (post.tag == "发现") {
            tagLabel->setStyleSheet("font-size: 10px; color: #2E7D32; background: #E8F5E9; border-radius: 3px; padding: 1px 5px;");
        } else {
            tagLabel->setStyleSheet("font-size: 10px; color: #E65100; background: #FFF3E0; border-radius: 3px; padding: 1px 5px;");
        }
        textLayout->addWidget(tagLabel);

        QLabel *timeLabel = new QLabel(post.time.toString("MM-dd hh:mm"));
        timeLabel->setStyleSheet("font-size: 11px; color: #C7C7CC; border: none; background: transparent;");
        textLayout->addWidget(timeLabel);

        cardLayout->addLayout(textLayout, 1);

        // 点击查看详情
        QPushButton *clickBtn = new QPushButton(card);
        clickBtn->setStyleSheet("border: none; background: transparent;");
        clickBtn->setCursor(Qt::PointingHandCursor);
        clickBtn->setGeometry(0, 0, card->width(), card->height());
        clickBtn->raise();

        PostData postData = post;
        connect(clickBtn, &QPushButton::clicked, this, [this, postData]() {
            clickSound->play();
            PostDetailDialog dialog(postData, this);
            dialog.exec();
        });

        postListLayout->addWidget(card);
    }
}
void ProfilePage::refreshUserInfo()
{
    nicknameLabel->setText(currentUser.nickname);
    bioLabel->setText(currentUser.bio);
    // 刷新头像
    QPixmap avatar(currentUser.avatarPath);
    if (!avatar.isNull()) {
        avatarLabel->setPixmap(avatar.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

bool ProfilePage::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == avatarLabel && event->type() == QEvent::MouseButtonPress) {
        QString filePath = QFileDialog::getOpenFileName(this, "选择头像", "",
                                                        "Images (*.png *.jpg *.jpeg *.bmp)");
        if (!filePath.isEmpty()) {
            currentUser.avatarPath = filePath;
            QPixmap avatar(filePath);
            avatarLabel->setPixmap(avatar.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        return true;
    }
    return QWidget::eventFilter(obj, event);
}
void ProfilePage::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    QPixmap bg(":/images/background3.png");
    if (!bg.isNull()) {
        painter.drawPixmap(this->rect(), bg.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        painter.fillRect(this->rect(), QColor("#F7F8FA"));
    }
}