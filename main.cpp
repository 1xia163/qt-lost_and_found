#include <QApplication>
#include "mainwindow.h"
#include "postmanager.h"
#include "postdata.h"
#include "soundmanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SoundManager::instance().startBGM();  // 启动背景音乐

    PostManager &manager = PostManager::instance();

    PostData post1;
    post1.tag = "发现";
    post1.title = "钥匙";
    post1.detail = "图书馆多媒体专区发现一串钥匙，有一个hello kitty拼豆和两把钥匙，已交给值班阿姨";
    post1.qq = "";
    post1.wechat = "";
    post1.phone = "";
    post1.time = QDateTime(QDate(2026, 5, 8), QTime(9, 15));
    post1.author = "system";
    manager.addPost(post1);

    PostData post11;
    post11.tag = "寻找";
    post11.title = "U盘";
    post11.detail = "在实验楼A304机房丢失，是联想的如图，里面有重要课件资料，有没有同学捡到了呢";
    post11.qq = "3578915368";
    post11.wechat = "";
    post11.phone = "";
    post11.images.append(":/images/upan.jpg");
    post11.time = QDateTime(QDate(2026, 5, 8), QTime(10, 30));
    post11.author = "system";
    manager.addPost(post11);

    PostData post2;
    post2.tag = "发现";
    post2.title = "小狗挂件回家";
    post2.detail = "今天晚上在操文科场跑道边捡到";
    post2.qq = "";
    post2.wechat = "";
    post2.phone = "13900002222";
    post2.images.append(":/images/dog.jpg");
    post2.time = QDateTime(QDate(2026, 5, 8), QTime(20, 45));
    post2.author = "system";
    manager.addPost(post2);

    PostData post7;
    post7.tag = "寻找";
    post7.title = "紫色笔记本";
    post7.detail = "今天早上在公教楼C区201上课落下了，回去找发现不见了，有没有uu看见";
    post7.qq = "555666777";
    post7.wechat = "";
    post7.phone = "";
    post7.images.append(":/images/book.jpg");
    post7.time = QDateTime(QDate(2026, 5, 9), QTime(11, 58));
    post7.author = "system";
    manager.addPost(post7);

    PostData post3;
    post3.tag = "发现";
    post3.title = "手机支架";
    post3.detail = "在理科食堂二楼发现";
    post3.qq = "987654321";
    post3.wechat = "";
    post3.phone = "";
    post3.images.append(":/images/phone_support.jpg");
    post3.time = QDateTime(QDate(2026, 5, 9), QTime(12, 23));
    post3.author = "system";
    manager.addPost(post3);

    PostData post8;
    post8.tag = "寻找";
    post8.title = "学生证";
    post8.detail = "可能在教学楼或食堂丢失，有没有uu看见过，姓名李明，学号2024001。";
    post8.qq = "0975831567";
    post8.wechat = "";
    post8.phone = "13400006666";
    post8.time = QDateTime(QDate(2026, 5, 9), QTime(17, 53));
    post8.author = "system";
    manager.addPost(post8);

    PostData post4;
    post4.tag = "发现";
    post4.title = "白色蓝牙耳机";
    post4.detail = "如图，谁的蓝牙耳机落在公教A座201教室了，放在原位了。";
    post4.qq = "";
    post4.wechat = "";
    post4.phone = "";
    post4.images.append(":/images/earphone.jpg");
    post4.time = QDateTime(QDate(2026, 5, 9), QTime(19, 17));
    post4.author = "system";
    manager.addPost(post4);


    PostData post5;
    post5.tag = "发现";
    post5.title = "雨伞";
    post5.detail = "在食堂门口捡到，蓝色折叠伞，已放在1楼失物招领处。";
    post5.qq = "";
    post5.wechat = "";
    post5.phone = "13600004444";
    post5.time = QDateTime(QDate(2026, 5, 10), QTime(7, 01));
    post5.author = "system";
    manager.addPost(post5);

    PostData post6;
    post6.tag = "发现";
    post6.title = "水杯回家";
    post6.detail = "在西南门滴滴车筐里发现，绿色保温杯，失主可以联系我。";
    post6.qq = "111222333";
    post6.wechat = "J989243";
    post6.phone = "";
    post6.images.append(":/images/cup.jpg");
    post6.time = QDateTime(QDate(2026, 5, 10), QTime(8, 22));
    post6.author = "system";
    manager.addPost(post6);

    PostData post9;
    post9.tag = "寻找";
    post9.title = "手表";
    post9.detail = "在操场丢失，黑色表带，表面有轻微划痕。";
    post9.qq = "999888777";
    post9.wechat = "";
    post9.phone = "13300007777";
    post9.images.append(":/images/watch.jpg");
    post9.time = QDateTime(QDate(2026, 5, 10), QTime(9, 45));
    post9.author = "system";
    manager.addPost(post9);

    PostData post10;
    post10.tag = "寻找";
    post10.title = "眼镜";
    post10.detail = "在图书馆丢失，黑框近视眼镜。";
    post10.qq = "";
    post10.wechat = "glasses_finder";
    post10.phone = "13200008888";
    post10.images.append(":/images/glasses.jpg");
    post10.time = QDateTime(QDate(2026, 5, 10), QTime(10, 14));
    post10.author = "system";
    manager.addPost(post10);

    // 创建主窗口
    MainWindow w;
    w.show();

    return a.exec();
}