#include <stdio.h>

#include <QPainter>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

#include <std_srvs/Trigger.h>
#include <std_srvs/Empty.h>
#include "state_trigger_panel.h"

namespace orne_rviz_plugins
{

StateTriggerPanel::StateTriggerPanel( QWidget* parent )
  : rviz::Panel( parent )
{
  start_client_ = nh_.serviceClient<std_srvs::Trigger>("start_wp_nav", false);
  resume_client_ = nh_.serviceClient<std_srvs::Trigger>("resume_nav", false);
  loop_start_client_ = nh.serviceClient<std_srvs::Empty>("loop_start_wp_nav", false);
  loop_stop_client_ = nh.serviceClient<std_srvs::Empty>("loop_stop_wp_nav", false);
  
  start_nav_button_ = new QPushButton("StartWaypointsNavigation");
  resume_nav_button_ = new QPushButton("ResumeWaypointsNavigation");
  loop_start_button_ =  new QPushButton("LoopStartNavigation");
  loop_stop_button_ =  new QPushButton("LoopStopNavigation");

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(start_nav_button_);
  layout->addWidget(resume_nav_button_);
  layout->addWidget(loop_start_button_);
  layout->addWidget(loop_stop_button_);
  setLayout( layout );
  
  connect(start_nav_button_, SIGNAL(clicked()), this, SLOT(pushStartNavigation()));
  connect(resume_nav_button_, SIGNAL(clicked()), this, SLOT(pushResumeNavigation()));
  connect(loop_start_button_, SIGNAL(clicked()), this, SLOT(pushLoopStart()));
  connect(loop_stop_button_, SIGNAL(clicked()), this, SLOT(pushLoopStop()));
}

void StateTriggerPanel::save( rviz::Config config ) const
{
  rviz::Panel::save( config );
}

void StateTriggerPanel::load( const rviz::Config& config )
{
  rviz::Panel::load( config );
}

void StateTriggerPanel::pushStartNavigation() {
    ROS_INFO("Service call: start waypoints navigation");
    
    std_srvs::Trigger trigger;
    start_client_.call(trigger);
}

void StateTriggerPanel::pushResumeNavigation() {
    ROS_INFO("Service call: resume waypoints navigation");
    
    std_srvs::Trigger trigger;
    resume_client_.call(trigger);
}
void StateTriggerPanel::pushLoopStart() {
    ROS_INFO("Service call: loop start navigation");
    
    std_srvs::Empty empty;
    loop_start_client_.call(empty);
}

void StateTriggerPanel::pushLoopStop() {
    ROS_INFO("Service call: loop stop navigation");
    
    std_srvs::Empty empty;
    loop_stop_client_.call(empty);
}



} // end namespace orne_rviz_plugins

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(orne_rviz_plugins::StateTriggerPanel,rviz::Panel )
