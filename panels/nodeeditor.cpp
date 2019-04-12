#include "nodeeditor.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QDebug>

NodeEditor::NodeEditor(QWidget *parent) :
  EffectsPanel(parent),
  view_(&scene_)
{
  setWindowTitle(tr("Node Editor"));
  resize(720, 480);

  QWidget* central_widget = new QWidget();
  setWidget(central_widget);

  QVBoxLayout* layout = new QVBoxLayout(central_widget);
  layout->setSpacing(0);
  layout->setMargin(0);

  layout->addWidget(&view_);

  view_.setInteractive(true);
  view_.setDragMode(QGraphicsView::RubberBandDrag);
}

void NodeEditor::Retranslate()
{
}

void NodeEditor::LoadEvent()
{
  nodes_.resize(open_effects_.size());

  if (!open_effects_.isEmpty()) {
    Clip* first_clip = open_effects_.first()->GetEffect()->parent_clip;

    for (int i=0;i<open_effects_.size();i++) {
      EffectUI* effect_ui = open_effects_.at(i);

      if (effect_ui->GetEffect()->parent_clip == first_clip) {
        NodeUI* node_ui = new NodeUI();

        effect_ui->SetNodeParent(node_ui);
        effect_ui->SetSelectable(false);

        node_ui->SetWidget(effect_ui);
        node_ui->AddToScene(&scene_);

        nodes_[i] = node_ui;
      }
    }
  }
}

void NodeEditor::ClearEvent()
{
  NodeUI* node;

  foreach (node, nodes_) {
    delete node;
  }

  nodes_.clear();
}