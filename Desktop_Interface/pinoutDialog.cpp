#include "pinoutDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QDebug>
#include <QResizeEvent>

class ImageLabel : public QLabel
{
public:
    ImageLabel(const QString &path) : m_image(path)
    {
        setPixmap(m_image);
    }

    QSize sizeHint() const override {
        return m_image.size();
    }
protected:
    void resizeEvent(QResizeEvent *event) override
    {
        setPixmap(m_image.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QLabel::resizeEvent(event);
    }

private:
    QPixmap m_image;
};

static QString loadDescription()
{
    QFile file(":/resources/pinout.html");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to load" << file.fileName();
        return "";
    }
    return QString::fromUtf8(file.readAll());
}

pinoutDialog::pinoutDialog()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QHBoxLayout *contentLayout = new QHBoxLayout;
    mainLayout->addLayout(contentLayout);

    QLabel *imageLabel = new ImageLabel(":/resources/pinout.png");
    imageLabel->setMinimumSize(250, 250);
    imageLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    contentLayout->addWidget(imageLabel);

    QLabel *description = new QLabel;
    description->setWordWrap(true);
    description->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    description->setTextFormat(Qt::RichText);
    description->setText(loadDescription());
    description->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    contentLayout->addWidget(description);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    mainLayout->addLayout(buttonLayout);
    buttonLayout->addStretch();

    QPushButton *closeButton = new QPushButton(tr("Close"));
    closeButton->setDefault(true);
    buttonLayout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

}
