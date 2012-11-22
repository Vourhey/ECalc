#include <QtGui>
#include "bineditor.h"

BinEditor::BinEditor(QWidget *parent) :
    QWidget(parent), m_number(0)
{
    LabelForBinEditor *lbl;
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSpacing(1);

    int degree = 63;
    for(int j=0; j<8; ++j)
    {
        int i;
        for(i=0; i<4; ++i)
        {
            lbl = new LabelForBinEditor(degree--, tr("0"));
            connect(lbl, SIGNAL(clicked(int,QString)), SLOT(labelClickSlot(int,QString)));
            gridLayout->addWidget(lbl, 0, i + 5*j);
        }
        QLabel *l = new QLabel(tr(" "));
        gridLayout->addWidget(l, 0, i + 5*j);
    }


    QLabel *lbl63 = new QLabel(tr("63"));
    QLabel *lbl47 = new QLabel(tr("47"));
    QLabel *lbl32 = new QLabel(tr("32"));

    gridLayout->addWidget(lbl63, 1, 0, 1, 2);
    gridLayout->addWidget(lbl47, 1, 20, 1, 2);
    gridLayout->addWidget(lbl32, 1, 38, 1, 2);

    for(int j=0; j<8; ++j)
    {
        int i;
        for(i=0; i<4; ++i)
        {
            lbl = new LabelForBinEditor(degree--, tr("0"));
            connect(lbl, SIGNAL(clicked(int,QString)), SLOT(labelClickSlot(int,QString)));
            gridLayout->addWidget(lbl, 2, i + 5*j);
        }
        QLabel *l = new QLabel(tr(" "));
        gridLayout->addWidget(l, 2, i + 5*j);
    }

    QLabel *lbl31 = new QLabel(tr("31"));
    QLabel *lbl15 = new QLabel(tr("15"));
    QLabel *lbl0 = new QLabel(tr("0"));

    gridLayout->addWidget(lbl31, 3, 0, 1, 2);
    gridLayout->addWidget(lbl15, 3, 20, 1, 2);
    gridLayout->addWidget(lbl0, 3, 38, 1, 2);

    setLayout(gridLayout);
}

void BinEditor::labelClickSlot(int d, const QString &text)
{
    quint64 temp = 1;
    temp = temp << d; // смещаем на d бит влево

    if(text == tr("0"))
    {
        m_number = m_number | temp; // устанавливаем бит
    }
    else
    {
        temp = ~temp; // инвентируем
        m_number = m_number & temp;
    }

    emit numberChanged(m_number);
}
