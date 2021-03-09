#include "robot_model.h"
#include <QColor>

#include <ros/ros.h>


RobotModelType::RobotModelType(QObject *parent)
  : QObject(parent)
  , robotModel_(nullptr)
  , frame_(nullptr)
{
//  connect(this, &RobotModelType::lineWidthChanged, this, &RobotModelType::updateProperties);
//  connect(this, &RobotModelType::colorChanged, this, &RobotModelType::updateProperties);
}

RobotModelType::~RobotModelType()
{

}

rviz::QuickVisualizationFrame *RobotModelType::getFrame() const
{
  return frame_;
}

//int RobotModelType::getLineWidth() const
//{
//  return line_width_;
//}

//QColor RobotModelType::getColor() const
//{
//  return color_;
//}

void RobotModelType::setFrame(rviz::QuickVisualizationFrame *frame)
{
  if (frame_ == frame) {
    return;
  }

  frame_ = frame;
  Q_EMIT frameChanged(frame_);

  if (frame_->isInitialized()) {
      initialize();
  }
  else {
    connect(frame_, &rviz::QuickVisualizationFrame::initializedChanged,
            this, &RobotModelType::initialize);
  }
}

//void RobotModelType::setLineWidth(int line_width)
//{
//  if (line_width_ == line_width) {
//    return;
//  }

//  line_width_ = line_width;
//  Q_EMIT lineWidthChanged(line_width_);
//}

//void RobotModelType::setColor(QColor color)
//{
//  if (color_ == color) {
//    return;
//  }

//  color_ = color;
//  Q_EMIT colorChanged(color_);
//}

void RobotModelType::initialize()
{
  robotModel_ = frame_->getManager()->createDisplay( "rviz/RobotModel", "RobotModel", true );
  ROS_ASSERT( robotModel_ != NULL );

//  updateProperties();
}

//void RobotModelType::updateProperties()
//{
//  if (!grid_) {
//    return;
//  }

//  grid_->subProp("Line Style")->subProp("Line Width")->setValue(line_width_);
//  grid_->subProp( "Color" )->setValue( color_ );
//}
