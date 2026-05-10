#include "mainwindow.h"
#include "homepage.h"
#include "profilepage.h"
#include "postpage.h"
#include "postmanager.h"
#include "postdata.h"
#include "showpostspage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet("QWidget { border: none; }");
    setupUI();
    this->setFixedSize(375, 667);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    //顶部装饰导航栏
    QLabel *topBar = new QLabel(this);
    QPixmap topPixmap(":/images/up.png");
    topBar->setPixmap(topPixmap.scaledToWidth(375, Qt::SmoothTransformation));
    topBar->setFixedHeight(44);
    topBar->setScaledContents(false);
    mainLayout->addWidget(topBar);

    // 1. 堆栈页面区
    stackedWidget = new QStackedWidget(this);

    HomePage *homePage = new HomePage();
    ProfilePage *profilePage = new ProfilePage();
    postPage = new PostPage();

    stackedWidget->addWidget(homePage);           // 索引 0
    stackedWidget->addWidget(profilePage);        // 索引 1
    stackedWidget->addWidget(postPage);           // 索引 2

    mainLayout->addWidget(stackedWidget, 1);

    // 接收首页"发现"/"寻找"信号
    connect(homePage, &HomePage::goToPost, this, [this](const QString &tag) {
        qDebug() << "goToPost 触发，tag =" << tag;
        if (showPostsPage) {
            stackedWidget->removeWidget(showPostsPage);
            delete showPostsPage;
            showPostsPage = nullptr;
        }
        ShowPostsPage *page = new ShowPostsPage(tag);
        showPostsPage = page;
        stackedWidget->addWidget(showPostsPage);
        stackedWidget->setCurrentWidget(showPostsPage);
    });

    // 2. 底部导航容器
    QWidget *navBar = new QWidget(this);
    navBar->setFixedHeight(50);
    navBar->setStyleSheet("background-color: #FFFFFF; border-top: 1px solid #E5E5E5;");

    QHBoxLayout *navLayout = new QHBoxLayout(navBar);
    navLayout->setContentsMargins(40, 0, 40, 0);
    navLayout->setSpacing(0);

    btnHome = new QPushButton(this);
    btnHome->setIcon(QIcon(":/images/blue_main.png"));
    btnHome->setIconSize(QSize(48, 48));
    btnHome->setFlat(true);
    btnHome->setCursor(Qt::PointingHandCursor);
    btnHome->setStyleSheet("border: none; background: transparent;");
    navLayout->addWidget(btnHome);

    btnProfile = new QPushButton(this);
    btnProfile->setIcon(QIcon(":/images/gray_me.png"));
    btnProfile->setIconSize(QSize(48, 48));
    btnProfile->setFlat(true);
    btnProfile->setCursor(Qt::PointingHandCursor);
    btnProfile->setStyleSheet("border: none; background: transparent;");
    navLayout->addWidget(btnProfile);

    mainLayout->addWidget(navBar);

    // 3. FAB 按钮
    fabBtn = new QPushButton(this);
    fabBtn->setFixedSize(90, 90);
    fabBtn->setIcon(QIcon(":/images/jiahao.png"));
    fabBtn->setIconSize(QSize(90, 90));
    fabBtn->setFlat(true);
    fabBtn->setCursor(Qt::PointingHandCursor);
    fabBtn->setStyleSheet("QPushButton { border: none; background: transparent; }");
    fabBtn->move(255, 470);
    fabBtn->raise();

    // 4. 信号连接
    connect(btnHome, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(0);
        btnHome->setIcon(QIcon(":/images/blue_main.png"));
        btnProfile->setIcon(QIcon(":/images/gray_me.png"));
        // 刷新首页帖子
        HomePage *hp = qobject_cast<HomePage*>(stackedWidget->widget(0));
        if (hp) {
            hp->refreshPosts();
        }
    });
    connect(btnProfile, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(1);
        btnHome->setIcon(QIcon(":/images/gray_main.png"));
        btnProfile->setIcon(QIcon(":/images/blue_me.png"));
    });

    connect(fabBtn, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(2);
    });

    // 发帖取消
    connect(postPage, &PostPage::cancelPost, this, [this]() {
        stackedWidget->setCurrentIndex(0);
    });

    // 发帖提交
    connect(postPage, &PostPage::postSubmitted, this,
            [this](const QString &tag, const QString &title, const QString &detail,
                   const QString &qq, const QString &wechat, const QString &phone,
                   const QStringList &images)
            {
                PostData data;
                data.tag = tag;
                data.title = title;
                data.detail = detail;
                data.qq = qq;
                data.wechat = wechat;
                data.phone = phone;
                data.images = images;
                data.time = QDateTime::currentDateTime();
                PostManager::instance().addPost(data);
                // 刷新首页帖子列表
                HomePage *hp = qobject_cast<HomePage*>(stackedWidget->widget(0));
                if (hp) {
                    hp->refreshPosts();
                }
                stackedWidget->setCurrentIndex(0);
            });
    // 初始加载帖子
    HomePage *hp = qobject_cast<HomePage*>(stackedWidget->widget(0));
    if (hp) {
        hp->refreshPosts();
    }
}