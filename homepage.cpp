#include "homepage.h"
#include "postmanager.h"
#include "postdetaildialog.h"
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QSoundEffect>

HomePage::HomePage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    clickSound = new QSoundEffect(this);
    clickSound->setSource(QUrl("qrc:/effects/click.wav"));
    clickSound->setVolume(0.5);

    // ---- 两个矩形按钮 ----
    QHBoxLayout *topBtnLayout = new QHBoxLayout();
    topBtnLayout->setContentsMargins(12, 8, 12, 8);
    topBtnLayout->setSpacing(12);

    btnDiscover = new QPushButton(this);
    btnDiscover->setFixedSize(175, 80);
    btnDiscover->setIcon(QIcon(":/images/found3.png"));
    btnDiscover->setIconSize(QSize(175, 80));
    btnDiscover->setFlat(true);
    btnDiscover->setCursor(Qt::PointingHandCursor);
    btnDiscover->setStyleSheet("border: none; background: transparent;");
    topBtnLayout->addWidget(btnDiscover);

    btnSearch = new QPushButton(this);
    btnSearch->setFixedSize(175, 80);
    btnSearch->setIcon(QIcon(":/images/to_find3.png"));
    btnSearch->setIconSize(QSize(175, 80));
    btnSearch->setFlat(true);
    btnSearch->setCursor(Qt::PointingHandCursor);
    btnSearch->setStyleSheet("border: none; background: transparent;");
    topBtnLayout->addWidget(btnSearch);

    mainLayout->addLayout(topBtnLayout);

    // 点击信号
    connect(btnDiscover, &QPushButton::clicked, this, [this]() {
        clickSound->play();
        emit goToPost(QStringLiteral("发现"));
    });
    connect(btnSearch, &QPushButton::clicked, this, [this]() {
        clickSound->play();
        emit goToPost(QStringLiteral("寻找"));
    });

    // 滚动区域（帖子列表）
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    scrollArea->setAutoFillBackground(false);
    scrollArea->viewport()->setStyleSheet("background: transparent;");
    scrollArea->viewport()->setAutoFillBackground(false);

    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("background: transparent;");
    contentWidget->setAutoFillBackground(false);

    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(12, 8, 12, 12);
    contentLayout->setSpacing(10);
    contentLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    scrollArea->setWidget(contentWidget);
    mainLayout->addWidget(scrollArea, 1);
}

void HomePage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap bg(":/images/background3.png");
    if (!bg.isNull()) {
        painter.drawPixmap(this->rect(), bg.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}

void HomePage::refreshPosts()
{
    QLayoutItem *item;
    while ((item = contentLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    QList<PostData> posts = PostManager::instance().getAllPosts();

    for (const PostData &post : posts) {
        QWidget *card = new QWidget();
        card->setFixedWidth(351);
        card->setStyleSheet(
            "QWidget {"
            "  background: #FFFFFF;"
            "  border-radius: 12px;"
            "  border: 1px solid #EEEEEE;"
            "}"
            );

        QHBoxLayout *cardLayout = new QHBoxLayout(card);
        cardLayout->setContentsMargins(12, 12, 12, 12);
        cardLayout->setSpacing(12);

        QLabel *imageLabel = new QLabel();
        imageLabel->setFixedSize(80, 80);
        imageLabel->setStyleSheet("border-radius: 8px; background: #F2F2F7;");

        if (!post.images.isEmpty()) {
            QPixmap pixmap(post.images.first());
            imageLabel->setPixmap(pixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            imageLabel->setText("📷");
            imageLabel->setAlignment(Qt::AlignCenter);
            imageLabel->setStyleSheet("border-radius: 8px; background: #F2F2F7; font-size: 28px;");
        }
        cardLayout->addWidget(imageLabel);

        QVBoxLayout *textLayout = new QVBoxLayout();
        textLayout->setSpacing(6);

        QLabel *titleLabel = new QLabel(post.title);
        titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #1D1D1F; border: none; background: transparent;");
        textLayout->addWidget(titleLabel);

        QLabel *tagLabel = new QLabel(post.tag == "发现" ? " #发现 " : " #寻找 ");
        if (post.tag == "发现") {
            tagLabel->setStyleSheet(
                "font-size: 11px; color: #2E7D32; background: #E8F5E9; "
                "border-radius: 4px; padding: 2px 6px;"
                );
        } else {
            tagLabel->setStyleSheet(
                "font-size: 11px; color: #E65100; background: #FFF3E0; "
                "border-radius: 4px; padding: 2px 6px;"
                );
        }
        textLayout->addWidget(tagLabel);

        QLabel *detailLabel = new QLabel(post.detail);
        detailLabel->setStyleSheet("font-size: 13px; color: #8E8E93; border: none; background: transparent;");
        detailLabel->setWordWrap(true);
        detailLabel->setMaximumHeight(32);
        textLayout->addWidget(detailLabel);

        QLabel *timeLabel = new QLabel(post.time.toString("MM-dd hh:mm"));
        timeLabel->setStyleSheet("font-size: 11px; color: #C7C7CC; border: none; background: transparent;");
        textLayout->addWidget(timeLabel);

        cardLayout->addLayout(textLayout, 1);

        QPushButton *clickBtn = new QPushButton(card);
        clickBtn->setStyleSheet("border: none; background: transparent;");
        clickBtn->setCursor(Qt::PointingHandCursor);
        clickBtn->setGeometry(0, 0, card->width(), card->height());
        clickBtn->raise();

        PostData postData = post;
        connect(clickBtn, &QPushButton::clicked, this, [this, postData]() {
            PostDetailDialog dialog(postData, this);
            dialog.exec();
        });

        contentLayout->insertWidget(0, card);
    }
}