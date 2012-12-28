#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include "numbersystemswitcher.h"
#include "lineedit.h"

NumberSystemSwitcher::NumberSystemSwitcher(LineEdit *le, QWidget *parent) :
    QWidget(parent), lineEdit(le), m_number(0)
{
    label = new QLabel;
    label->setTextFormat(Qt::RichText);
    label->setAlignment(Qt::AlignRight);

    comboBox = new QComboBox;

    comboBox->addItem(tr("Binary"), QVariant(2));
    comboBox->addItem(tr("Octal"), QVariant(8));
    comboBox->addItem(tr("Decimal"), QVariant(10));
    comboBox->addItem(tr("Hexadecimal"), QVariant(16));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), SLOT(updateFromAndTo(int)));
    comboBox->setCurrentIndex(2);   // Dec

    connect(lineEdit, SIGNAL(numberChanged(Number)), SLOT(setNumber(Number)));
    connect(lineEdit, SIGNAL(numberModeChanged(int)), SLOT(changeIndex(int)));

    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->addWidget(comboBox);
    mainlayout->addWidget(label);
    setLayout(mainlayout);

    setNumber(lineEdit->getNumber());
}

void NumberSystemSwitcher::setNumber(Number n)
{
    if(!n.isUInteger())
        n = 0;
    m_number = n;
    updateLabel();
}

void NumberSystemSwitcher::updateLabel()
{
    QString text = QString("%1%2 = %3%4")
            .arg(QString::number(m_number.toUInt64(), from))
            .arg(QString("<sub>%1</sub>").arg(from))
            .arg(QString::number(m_number.toUInt64(), to).toUpper())
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

    lineEdit->setNumberMode(n);

    updateLabel();
}

void NumberSystemSwitcher::changeIndex(int n)
{
    if(n == 2) comboBox->setCurrentIndex(0);
    else if(n == 8) comboBox->setCurrentIndex(1);
    else if(n == 10) comboBox->setCurrentIndex(2);
    else comboBox->setCurrentIndex(3);
}
