#include "postpage.h"
#include <QScrollArea>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>

PostPage::PostPage(QWidget *parent) : QWidget(parent)
{
    clickSound = new QSoundEffect(this);

    clickSound->setSource(
        QUrl("qrc:/effects/click.wav")
        );

    clickSound->setVolume(0.5);

    // 外层滚动区域
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
   scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");


    QWidget *contentWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(16);

    // 顶部栏：取消 + 标题 + 发布
    QHBoxLayout *topBar = new QHBoxLayout();
    cancelBtn = new QPushButton("取消");
    cancelBtn->setStyleSheet("color: #8E8E93; font-size: 15px; border: none; background: transparent;");

    QLabel *pageTitle = new QLabel("发布信息");
    pageTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #1D1D1F;");
    pageTitle->setAlignment(Qt::AlignCenter);

    submitBtn = new QPushButton("发布");
    submitBtn->setStyleSheet(
        "QPushButton {"
        "  color: white;"
        "  background-color: #4A90E2;"
        "  border-radius: 15px;"
        "  padding: 6px 18px;"
        "  font-size: 14px;"
        "  border: none;"
        "}"
        );

    topBar->addWidget(cancelBtn);
    topBar->addStretch();
    topBar->addWidget(pageTitle);
    topBar->addStretch();
    topBar->addWidget(submitBtn);
    mainLayout->addLayout(topBar);

    //标签选择：发现 / 寻找
    QHBoxLayout *tagLayout = new QHBoxLayout();
    QLabel *tagLabel = new QLabel("标签：");
    tagLabel->setStyleSheet("font-size: 15px; color: #1D1D1F;");

    tagGroup = new QButtonGroup(this);
    radioFound = new QRadioButton("发现");
    radioLost = new QRadioButton("寻找");
    radioFound->setStyleSheet("font-size: 14px;");
    radioLost->setStyleSheet("font-size: 14px;");
    radioFound->setChecked(true);

    tagGroup->addButton(radioFound, 0);
    tagGroup->addButton(radioLost, 1);

    tagLayout->addWidget(tagLabel);
    tagLayout->addWidget(radioFound);
    tagLayout->addWidget(radioLost);
    tagLayout->addStretch();
    mainLayout->addLayout(tagLayout);

    //物品名称
    QLabel *titleLabel = new QLabel("物品名称");
    titleLabel->setStyleSheet("font-size: 15px; color: #1D1D1F;");
    mainLayout->addWidget(titleLabel);

    titleEdit = new QLineEdit();
    titleEdit->setPlaceholderText("例如：黑色钱包、钥匙串...");
    titleEdit->setStyleSheet(
        "QLineEdit {"
        "  border: 1px solid #E5E5E5;"
        "  border-radius: 8px;"
        "  padding: 10px;"
        "  font-size: 15px;"
        "  background-color: #F7F8FA;"
        "}"
        );
    mainLayout->addWidget(titleEdit);

    //详细描述
    QLabel *detailLabel = new QLabel("详细描述");
    detailLabel->setStyleSheet("font-size: 15px; color: #1D1D1F;");
    mainLayout->addWidget(detailLabel);

    detailEdit = new QTextEdit();
    detailEdit->setPlaceholderText("描述物品特征、丢失或捡到的地点、时间...");
    detailEdit->setMaximumHeight(120);
    detailEdit->setStyleSheet(
        "QTextEdit {"
        "  border: 1px solid #E5E5E5;"
        "  border-radius: 8px;"
        "  padding: 10px;"
        "  font-size: 15px;"
        "  background-color: #F7F8FA;"
        "}"
        );
    mainLayout->addWidget(detailEdit);

    //添加图片
    QLabel *imageTitle = new QLabel("添加图片（选填）");
    imageTitle->setStyleSheet("font-size: 15px; color: #1D1D1F;");
    mainLayout->addWidget(imageTitle);

    QHBoxLayout *imageRow = new QHBoxLayout();
    imageRow->setSpacing(8);
    imageLayout = new QHBoxLayout();
    imageLayout->setSpacing(8);

    QPushButton *addImageBtn = new QPushButton("+");
    addImageBtn->setFixedSize(64, 64);
    addImageBtn->setStyleSheet(
        "QPushButton {"
        "  border: 1px dashed #C7C7CC;"
        "  border-radius: 8px;"
        "  font-size: 24px;"
        "  color: #C7C7CC;"
        "  background: #F7F8FA;"
        "}"
        );

    imageRow->addWidget(addImageBtn);
    imageRow->addLayout(imageLayout);
    imageRow->addStretch();
    mainLayout->addLayout(imageRow);

    connect(addImageBtn, &QPushButton::clicked, this, &PostPage::onAddImage);

    //联系方式
    QLabel *contactTitle = new QLabel("联系方式（选填）");
    contactTitle->setStyleSheet("font-size: 15px; color: #1D1D1F;");
    mainLayout->addWidget(contactTitle);

    QHBoxLayout *qqLayout = new QHBoxLayout();
    QLabel *qqLabel = new QLabel("QQ：");
    qqLabel->setFixedWidth(50);
    qqEdit = new QLineEdit();
    qqEdit->setPlaceholderText("选填");
    qqEdit->setStyleSheet("border: 1px solid #E5E5E5; border-radius: 6px; padding: 8px; font-size: 14px; background-color: #F7F8FA;");
    qqLayout->addWidget(qqLabel);
    qqLayout->addWidget(qqEdit);
    mainLayout->addLayout(qqLayout);

    QHBoxLayout *wechatLayout = new QHBoxLayout();
    QLabel *wechatLabel = new QLabel("微信：");
    wechatLabel->setFixedWidth(50);
    wechatEdit = new QLineEdit();
    wechatEdit->setPlaceholderText("选填");
    wechatEdit->setStyleSheet("border: 1px solid #E5E5E5; border-radius: 6px; padding: 8px; font-size: 14px; background-color: #F7F8FA;");
    wechatLayout->addWidget(wechatLabel);
    wechatLayout->addWidget(wechatEdit);
    mainLayout->addLayout(wechatLayout);

    QHBoxLayout *phoneLayout = new QHBoxLayout();
    QLabel *phoneLabel = new QLabel("电话：");
    phoneLabel->setFixedWidth(50);
    phoneEdit = new QLineEdit();
    phoneEdit->setPlaceholderText("选填");
    phoneEdit->setStyleSheet("border: 1px solid #E5E5E5; border-radius: 6px; padding: 8px; font-size: 14px; background-color: #F7F8FA;");
    phoneLayout->addWidget(phoneLabel);
    phoneLayout->addWidget(phoneEdit);
    mainLayout->addLayout(phoneLayout);

    mainLayout->addStretch();

    scrollArea->setWidget(contentWidget);

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scrollArea);

    //信号连接
    connect(submitBtn, &QPushButton::clicked, this, &PostPage::onSubmit);
    connect(cancelBtn, &QPushButton::clicked, this, [this]() {
        clickSound->play();
        emit cancelPost();
    });
}

void PostPage::onSubmit()
{
    QString tag = radioFound->isChecked() ? "发现" : "寻找";
    QString title = titleEdit->text().trimmed();
    QString detail = detailEdit->toPlainText().trimmed();
    QString qq = qqEdit->text().trimmed();
    QString wechat = wechatEdit->text().trimmed();
    QString phone = phoneEdit->text().trimmed();

    if (title.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入物品名称");
        return;
    }

    emit postSubmitted(tag, title, detail, qq, wechat, phone, selectedImages);

    // 清空表单
    titleEdit->clear();
    detailEdit->clear();
    qqEdit->clear();
    wechatEdit->clear();
    phoneEdit->clear();
    radioFound->setChecked(true);
    selectedImages.clear();

    // 清空图片预览
    for (QLabel *label : imageLabels) {
        imageLayout->removeWidget(label);
        delete label;
    }
    imageLabels.clear();
}

void PostPage::onAddImage()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择图片", "",
                                                    "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!filePath.isEmpty()) {
        selectedImages.append(filePath);

        QLabel *imageLabel = new QLabel();
        QPixmap pixmap(filePath);
        imageLabel->setPixmap(pixmap.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imageLabel->setFixedSize(60, 60);
        imageLabel->setStyleSheet("border: 1px solid #E5E5E5; border-radius: 6px;");
        imageLabels.append(imageLabel);
        imageLayout->addWidget(imageLabel);
    }
}

void PostPage::setDefaultTag(const QString &tag)
{
    if (tag == "寻找") {
        radioLost->setChecked(true);
    } else {
        radioFound->setChecked(true);
    }
}
#include <QPainter>

void PostPage::paintEvent(QPaintEvent *event)
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