#include "Inspector.hpp"
//#include "../View/View.hpp" 

#include <score/document/DocumentContext.hpp>

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>


namespace Acousmoscribe
{
InspectorWidget::InspectorWidget(
    const Acousmoscribe::Model& object, const score::DocumentContext& context,
    QWidget* parent)
    : InspectorWidgetDelegate_T{object, parent}
    , m_dispatcher{context.commandStack}
{
  auto lay = new QFormLayout{this};

  /* text display */
  QLabel *melodique = new QLabel;
  lay->addWidget(melodique);
  melodique->setText("clé spectrale\n");

  lay->addWidget(new QLabel());

  /* check button */
  /*QCheckBox *check1 = new QCheckBox("&tonique", parent);
  QCheckBox *check2 = new QCheckBox("&inharmonique", parent);
  QCheckBox *check3 = new QCheckBox("&bruit", parent);
  QCheckBox *check3 = new QCheckBox("&hybride", parent);*/

  QButtonGroup *group = new QButtonGroup;
  QPushButton *r_tonic = new QPushButton("&tonique");
  r_tonic->setCheckable(true);
  r_tonic->setChecked(true);
  QPushButton *r_qinharm = new QPushButton("&inharmonique");
  r_qinharm->setCheckable(true);
  QPushButton *r_noise = new QPushButton("&bruit");
  r_noise->setCheckable(true);

  group->addButton(r_tonic, 1);
  group->addButton(r_qinharm, 2);
  group->addButton(r_noise, 3);

  lay->addWidget(r_tonic);
  lay->addWidget(r_qinharm);
  lay->addWidget(r_noise);

  QButtonGroup *group2 = new QButtonGroup;
  QPushButton *r_poor = new QPushButton("&pauvre");
  r_poor->setCheckable(true);
  r_poor->setChecked(true);
  QPushButton *r_rich = new QPushButton("&riche");
  r_rich->setCheckable(true);
  QPushButton *r_hybrid = new QPushButton("&hybride");
  r_hybrid->setCheckable(true);
  
  group2->addButton(r_poor, 1);
  group2->addButton(r_rich, 2);
  group2->addButton(r_hybrid, 3);

  lay->addWidget(r_poor);
  lay->addWidget(r_rich);
  lay->addWidget(r_hybrid);

  QButtonGroup *group3 = new QButtonGroup;
  QPushButton *r_tonic2 = new QPushButton("&tonique");
  r_tonic2->setCheckable(true);
  r_tonic2->setChecked(true);
  QPushButton *r_qinharm2 = new QPushButton("&inharmonique");
  r_qinharm2->setCheckable(true);
  QPushButton *r_noise2 = new QPushButton("&bruit");
  r_noise2->setCheckable(true);

  group3->addButton(r_tonic2, 1);
  group3->addButton(r_qinharm2, 2);
  group3->addButton(r_noise2, 3);

  lay->addWidget(r_tonic2);
  lay->addWidget(r_qinharm2);
  lay->addWidget(r_noise2);

  r_tonic2->setVisible(false);
  r_qinharm2->setVisible(false);
  r_noise2->setVisible(false);
  
  connect(r_hybrid, SIGNAL(toggled(bool)), r_tonic2, SLOT(setVisible(bool)));
  connect(r_hybrid, SIGNAL(toggled(bool)), r_qinharm2, SLOT(setVisible(bool)));
  connect(r_hybrid, SIGNAL(toggled(bool)), r_noise2, SLOT(setVisible(bool)));


  /* scrolling menu */
  QComboBox *list = new QComboBox;
  lay->addWidget(list);
  list->addItem("pauvre");
  list->addItem("riche");
  list->addItem("hybride");


  lay->addWidget(new QLabel());
  lay->addWidget(new QLabel());

  QLabel *spectrale = new QLabel;
  lay->addWidget(spectrale);
  spectrale->setText("clé mélodique");
  
  /*QPushButton *boutonQuitter = new QPushButton("Bouton");
  lay->addWidget(boutonQuitter);
  QWidget::connect(boutonQuitter,SIGNAL(clicked()),parent,SLOT(quit()));*/

}


InspectorWidget::~InspectorWidget()
{
}
}
