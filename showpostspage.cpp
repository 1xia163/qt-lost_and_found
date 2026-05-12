#include "showpostspage.h"
#include "postmanager.h"
#include "postdetaildialog.h"
#include <QPixmap>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>

ShowPostsPage::ShowPostsPage(const QString &tag, QWidget *parent)
    : QWidget(parent), tag(tag)
{
    clickSound = new QSoundEffect(this);

    clickSound->setSource(
        QUrl("qrc:/effects/click.wav")
        );

    clickSound->setVolume(0.5);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 顶部返回栏
    QWidget *topBar = new QWidget(this);
    topBar->setFixedHeight(44);
    topBar->setStyleSheet("background-color: #FFFFFF; border-bottom: 1px solid #E5E5E5;");

    QHBoxLayout *topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(12, 0, 12, 0);

    QPushButton *backBtn = new QPushButton("← 返回", topBar);
    backBtn->setStyleSheet("color: #4A90E2; font-size: 15px; border: none; background: transparent;");
    backBtn->setCursor(Qt::PointingHandCursor);

    QLabel *titleLabel = new QLabel(tag, topBar);
    titleLabel->setStyleSheet("font-size: 17px; font-weight: bold; color: #1D1D1F;");
    titleLabel->setAlignment(Qt::AlignCenter);

    topLayout->addWidget(backBtn);
    topLayout->addStretch();
    topLayout->addWidget(titleLabel);
    topLayout->addStretch();
    topLayout->addWidget(new QWidget()); // 占位保持标题居中

    mainLayout->addWidget(topBar);

    // 返回按钮点击时回到首页
    connect(backBtn, &QPushButton::clicked, this, [this]()
    {
        clickSound->play();
        if (parentWidget()) {
            QStackedWidget *stack = qobject_cast<QStackedWidget*>(parentWidget());
            if (stack) {
                stack->setCurrentIndex(0);  // 回到首页
            }
        }
    });

    //图片墙滚动区
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; }");

    gridWidget = new QWidget();
    gridLayout = new QGridLayout(gridWidget);
    gridLayout->setContentsMargins(12, 4, 12, 4);
    gridLayout->setSpacing(8);

    scrollArea->setWidget(gridWidget);
    mainLayout->addWidget(scrollArea);

    loadPosts();
}
void ShowPostsPage::loadPosts()
{
    posts = PostManager::instance().getPostsByTag(tag);

    int row = 0, col = 0;
    for (int i = 0; i < posts.size(); ++i) {
        QPushButton *imageBtn = new QPushButton();
        imageBtn->setFixedSize(160, 160);
        imageBtn->setCursor(Qt::PointingHandCursor);
        imageBtn->setStyleSheet("border: 1px solid #E5E5E5; border-radius: 8px; background: #F7F8FA;");

        if (!posts[i].images.isEmpty()) {
            QPixmap pixmap(posts[i].images.first());
            QIcon icon(pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            imageBtn->setIcon(icon);
            imageBtn->setIconSize(QSize(150, 150));
        } else {
            imageBtn->setText(posts[i].title);
            imageBtn->setStyleSheet(
                "QPushButton {"
                "  border: 1px solid #E5E5E5; border-radius: 8px;"
                "  background: #F7F8FA; font-size: 14px; color: #8E8E93;"
                "}"
                );
        }

        int index = i;
        connect(imageBtn, &QPushButton::clicked, this, [this, index]() {
            onImageClicked(index);
        });

        gridLayout->addWidget(imageBtn, row, col);

        col++;
        if (col >= 2) {
            col = 0;
            row++;
        }
    }
}

void ShowPostsPage::onImageClicked(int index)
{
    if (index >= 0 && index < posts.size()) {
        PostDetailDialog dialog(posts[index], this);
        dialog.exec();
    }
}