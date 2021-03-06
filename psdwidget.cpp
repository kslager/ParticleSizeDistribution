#include "psdwidget.h"
#include "soilmodel.h"

#include <QListView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
//#include <QStringListModel>

#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>

PSDWidget::PSDWidget(QWidget *parent) : QWidget(parent)
{
    QWidget * toolBar = new QWidget();
    QHBoxLayout *toolLayout = new QHBoxLayout();
    toolLayout->setMargin(0);

    std::vector<std::string> actions = { "Add", "Edit", "Copy", "Delete" };

    for ( auto ac : actions )
    {
        toolLayout->addWidget(new QPushButton(QString::fromStdString(ac)));
    }

    toolBar->setLayout(toolLayout);

    QListView *sands = new QListView();

    SoilModel *sandModel = new SoilModel();
    //QStringList sand;
    //sand << "Fine sand" << "Medium fine sand" << "Coarse sand" << "Coarse sand and gravel" << "Gravel";
    //sandModel->setStringList(sand);
    sands->setModel(sandModel);

    QGroupBox *details = new QGroupBox("Properties");
    QFormLayout *propLayout = new QFormLayout();
    propLayout->addRow("Grain density", new QLabel("2650 kg/m\u00B3"));
    propLayout->addRow("In-situ density", new QLabel("1950 kg/m\u00B3"));
    propLayout->addRow("Grain size d<sub>50</sub>", new QLabel("110 μm"));
    propLayout->addRow("d<sub>mf</sub> = (d<sub>10</sub>+...+d<sub>90</sub>)/9", new QLabel("130 μm"));
    propLayout->addRow("c<sub>u</sub> = d<sub>60</sub> / d<sub>10</sub>", new QLabel("2.98"));
    propLayout->addRow("Density at 20% in-situ concentration", new QLabel("1210 kg/m\u00B3"));
    propLayout->addRow("Silt fraction", new QLabel("9.0 %"));


    details->setLayout(propLayout);

    QVBoxLayout *sideLayout = new QVBoxLayout();
    sideLayout->setMargin(0);
    sideLayout->addWidget(sands);
    sideLayout->addWidget(toolBar);
    sideLayout->addSpacing(30);
    sideLayout->addWidget(details);

    QWidget * sideBar = new QWidget();
    sideBar->setLayout(sideLayout);

    QHBoxLayout *layout = new QHBoxLayout();

    m_view = new PSDView();

    layout->addWidget(sideBar,1);
    layout->addWidget(m_view,5);


    setLayout(layout);
}
