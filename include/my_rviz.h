#pragma once

#include <QObject>
#include <QtQuick/QQuickView>

#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include "rviz/display.h"

namespace rviz
{
class Display;
class RenderPanel;
class VisualizationManager;
}

// BEGIN_TUTORIAL
// Class "MyViz" implements the top level widget for this example.
class MyViz: public QQuickView
{
Q_OBJECT
public:
  MyViz( QWindow* parent = nullptr );
  ~MyViz();

signals:
  void ogreInitialized();

private slots:
  void setThickness( int thickness_percent );
  void setCellSize( int cell_size_percent );
  void initializeOgre();
  void addContent();

private:
  rviz::VisualizationManager* manager_;
  rviz::RenderPanel* render_panel_;
  rviz::Display* grid_;
  rviz::QtOgreRenderWindow* render_window_;

  int thickness_percent_;
  int cell_size_percent_;
};
// END_TUTORIAL
