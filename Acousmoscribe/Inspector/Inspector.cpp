#include "Inspector.hpp"

#include <score/document/DocumentContext.hpp>

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>

namespace Acousmoscribe
{
InspectorWidget::InspectorWidget(
    const Acousmoscribe::Model& object, const score::DocumentContext& context,
    QWidget* parent)
    : InspectorWidgetDelegate_T{object, parent}
    , m_dispatcher{context.commandStack}
{
  auto lay = new QFormLayout{this};

  /* Affichage texte */
  QLabel *melodique = new QLabel;
  lay->addWidget(melodique);
  melodique->setText("clé spectrale\n");

  lay->addWidget(new QLabel());

  /* bouton à cocher */
  /*QCheckBox *check1 = new QCheckBox("&tonique", parent);
  QCheckBox *check2 = new QCheckBox("&inharmonique", parent);
  QCheckBox *check3 = new QCheckBox("&bruit", parent);
  QCheckBox *check3 = new QCheckBox("&hybride", parent);*/

  QRadioButton *r_tonic = new QRadioButton("&tonique");
  QRadioButton *r_qinharm = new QRadioButton("&inharmonique");
  QRadioButton *r_qnoise = new QRadioButton("&bruit");

  lay->addWidget(r_tonic);
  lay->addWidget(r_qinharm);
  lay->addWidget(r_qnoise);

  lay->addWidget(new QLabel());

  QRadioButton *r_poor = new QRadioButton("&pauvre");
  QRadioButton *r_rich = new QRadioButton("&riche");
  QRadioButton *r_hybrid = new QRadioButton("&hybride");

  lay->addWidget(r_poor);
  lay->addWidget(r_rich);
  lay->addWidget(r_hybrid);

  QRadioButton *r_tonic2 = new QRadioButton("&tonique");
  QRadioButton *r_qinharm2 = new QRadioButton("&inharmonique");
  QRadioButton *r_qnoise2 = new QRadioButton("&bruit");

  lay->addWidget(new QLabel());
  lay->addWidget(r_tonic2);
  lay->addWidget(r_qinharm2);
  lay->addWidget(r_qnoise2);

  r_tonic2->setVisible(false);
  r_qinharm2->setVisible(false);
  r_qnoise2->setVisible(false);
  
  connect(r_hybrid, SIGNAL(toggled(bool)), r_tonic2, SLOT(setVisible(bool)));
  connect(r_hybrid, SIGNAL(toggled(bool)), r_qinharm2, SLOT(setVisible(bool)));
  connect(r_hybrid, SIGNAL(toggled(bool)), r_qnoise2, SLOT(setVisible(bool)));


  /* menu déroulant */
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
