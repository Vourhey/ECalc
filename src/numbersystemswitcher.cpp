#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include "numbersystemswitcher.h"

NumberSystemSwitcher::NumberSystemSwitcher(QWidget *parent) :
    QWidget(parent)
{
    m_number = 0;

    label = new QLabel;
    label->setTextFormat(Qt::RichText);

    comboBox = new QComboBox;

    comboBox->addItem(tr("Binary"), QVariant(2));
    comboBox->addItem(tr("Octal"), QVariant(8));
    comboBox->addItem(tr("Decimal"), QVariant(10));
    comboBox->addItem(tr("Hexadecimal"), QVariant(16));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), SLOT(updateFromAndTo(int)));
    comboBox->setCurrentIndex(2);   // Dec

    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->addWidget(comboBox);
    mainlayout->addWidget(label);
    setLayout(mainlayout);
}

void NumberSystemSwitcher::setNumber(quint64 n)
{
    m_number = n;
    updateLabel();
}

void NumberSystemSwitcher::updateLabel()
{
    QString text = QString("%1%2 = %3%4")
            .arg(QString::number(m_number, from))
            .arg(QString("<sub>%1</sub>").arg(from))
            .arg(QString::number(m_number, to))
            .arg(QString("<sub>%1</sub>").arg(to));

    label->setText(text);
}

void NumberSystemSwitcher::updateFromAndTo(int i)
{
    qint8 n = (qint8)comboBox->itemData(i).toInt();

    if(n == 2) { from = 8; to = 10; }
    else if(n == 8) { from = 10; to = 16; }
    else if(n == 10) { from = 8; to = 16; }
    else { from = 8; to = 10; }

    updateLabel();
}
