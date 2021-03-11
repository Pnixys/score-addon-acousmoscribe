#include "Inspector.hpp"

#include <score/document/DocumentContext.hpp>

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QCheckBox>
#include <QComboBox>

namespace Skeleton
{
InspectorWidget::InspectorWidget(
    const Skeleton::Model& object, const score::DocumentContext& context,
    QWidget* parent)
    : InspectorWidgetDelegate_T{object, parent}
    , m_dispatcher{context.commandStack}
{
  auto lay = new QFormLayout{this};

  /* Affichage texte */
  QLabel *melodique = new QLabel;
  lay->addWidget(melodique);
  melodique->setText("clé mélodique");

  /* bouton à cocher */
  QCheckBox *check1 = new QCheckBox("&tonique", parent);
  QCheckBox *check2 = new QCheckBox("&inharmonique", parent);
  QCheckBox *check3 = new QCheckBox("&bruit", parent);
  lay->addWidget(check1);
  lay->addWidget(check2);
  lay->addWidget(check3);

  /* menu déroulant */
  QComboBox *list = new QComboBox;
  lay->addWidget(list);
  list->addItem("pauvre");
  list->addItem("riche");

  lay->addWidget(new QLabel());
  lay->addWidget(new QLabel());

  QLabel *spectrale = new QLabel;
  lay->addWidget(spectrale);
  spectrale->setText("clé spectrale");
  
  /*QPushButton *boutonQuitter = new QPushButton("Bouton");
  lay->addWidget(boutonQuitter);
  QWidget::connect(boutonQuitter,SIGNAL(clicked()),parent,SLOT(quit()));*/



}

InspectorWidget::~InspectorWidget()
{
}
}
