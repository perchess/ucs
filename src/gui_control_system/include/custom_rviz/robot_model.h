#pragma once

#include <QObject>

#include <rviz/visualization_manager.h>
#include <rviz/quick_visualization_frame.h>
#include <rviz/display.h>


class RobotModelType : public QObject
{
  Q_OBJECT
  Q_PROPERTY(rviz::QuickVisualizationFrame* frame READ getFrame WRITE setFrame NOTIFY frameChanged)
//  Q_PROPERTY(int lineWidth READ getLineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
//  Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)

public:
  explicit RobotModelType(QObject *parent = nullptr);

    ~RobotModelType();

  rviz::QuickVisualizationFrame* getFrame() const;
//  int getLineWidth() const;
//  QColor getColor() const;

Q_SIGNALS:
  void frameChanged(rviz::QuickVisualizationFrame* frame);
//  void lineWidthChanged(int lineWidth);

//  void colorChanged(QColor color);

public Q_SLOTS:
  void setFrame(rviz::QuickVisualizationFrame* frame);
//  void setLineWidth(int lineWidth);
//  void setColor(QColor color);

private:
  rviz::Display* robotModel_;

  rviz::QuickVisualizationFrame* frame_;
  ///Params here
//  int line_width_;
//  QColor color_;

private Q_SLOTS:
  void initialize();
//  void updateProperties();
};
