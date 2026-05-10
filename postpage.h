#ifndef POSTPAGE_H
#define POSTPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

class PostPage : public QWidget {
    Q_OBJECT

public:
    explicit PostPage(QWidget *parent = nullptr);
    void setDefaultTag(const QString &tag);

signals:
    void postSubmitted(const QString &tag, const QString &title, const QString &detail,
                       const QString &qq, const QString &wechat, const QString &phone,
                       const QStringList &images);
    void cancelPost();

private slots:
    void onSubmit();
    void onAddImage();

private:
    QRadioButton *radioFound;   // "发现"
    QRadioButton *radioLost;    // "寻找"
    QButtonGroup *tagGroup;

    QLineEdit *titleEdit;
    QTextEdit *detailEdit;

    // 图片预览区域
    QHBoxLayout *imageLayout;
    QList<QLabel*> imageLabels;
    QStringList selectedImages;

    // 联系方式
    QLineEdit *qqEdit;
    QLineEdit *wechatEdit;
    QLineEdit *phoneEdit;

    QPushButton *submitBtn;
    QPushButton *cancelBtn;
};

#endif // POSTPAGE_H