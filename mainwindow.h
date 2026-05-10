#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class PostPage;
class ShowPostsPage;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();

    QStackedWidget *stackedWidget;
    QPushButton *btnHome;
    QPushButton *btnProfile;
    QPushButton *fabBtn;
    PostPage *postPage;
    QWidget *showPostsPage = nullptr;
};

#endif // MAINWINDOW_H