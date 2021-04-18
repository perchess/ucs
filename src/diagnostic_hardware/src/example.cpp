#include <diagnostic_updater/diagnostic_updater.h>
#include <std_msgs/Bool.h>
#include <diagnostic_updater/publisher.h>

// ERROR defined in windows.h causes name collision, undefine the macro to fix the issue
#ifdef ERROR
#undef ERROR
#endif

double time_to_launch;


void dummy_diagnostic(diagnostic_updater::DiagnosticStatusWrapper &stat)
{
  if (time_to_launch < 10)
    // summaryf for formatted text.
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::ERROR, "Buckle your seat belt. Launch in %f seconds!", time_to_launch);
  else
    // summary for unformatted text.
    stat.summary(diagnostic_msgs::DiagnosticStatus::OK, "Launch is in a long time. Have a soda.");

  // add and addf are used to append key-value pairs.
  stat.add("Diagnostic Name", "dummy");
  // add transparently handles conversion to string (using a string_stream).
  stat.add("Time to Launch", time_to_launch);
  // addf allows arbitrary printf style formatting.
  stat.addf("Geeky thing to say", "The square of the time to launch %f is %f",
            time_to_launch, time_to_launch * time_to_launch);
}

class DummyClass
{
public:
  void produce_diagnostics(diagnostic_updater::DiagnosticStatusWrapper &stat)
  {
    stat.summary(diagnostic_msgs::DiagnosticStatus::WARN, "This is a silly updater.");

    stat.add("Stupidicity of this updater", 1000.);
  }
};

class DummyTask : public diagnostic_updater::DiagnosticTask
{
public:
  DummyTask() : DiagnosticTask("Updater Derived from DiagnosticTask")
  {}

  void run(diagnostic_updater::DiagnosticStatusWrapper &stat)
  {
    stat.summary(diagnostic_msgs::DiagnosticStatus::WARN, "AAAAAAAAAA I ADDDED IT");
    stat.add("Stupidicity of this updater", 2000.);
  }
};

void check_lower_bound(diagnostic_updater::DiagnosticStatusWrapper &stat)
{
  if (time_to_launch > 5)
    stat.summary(diagnostic_msgs::DiagnosticStatus::OK, "Lower-bound OK");
  else
    stat.summary(diagnostic_msgs::DiagnosticStatus::ERROR, "Too low");

  stat.add("Low-Side Margin", time_to_launch - 5);
}

void check_upper_bound(diagnostic_updater::DiagnosticStatusWrapper &stat)
{
  if (time_to_launch < 10)
    stat.summary(diagnostic_msgs::DiagnosticStatus::OK, "Upper-bound OK");
  else
    stat.summary(diagnostic_msgs::DiagnosticStatus::WARN, "Too high");

  stat.add("Top-Side Margin", 10 - time_to_launch);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "diagnostic_updater_example");

  ros::NodeHandle nh;

  diagnostic_updater::Updater updater;

  updater.setHardwareID("none");
  // Or...
  updater.setHardwareIDf("Device-%i-%i", 27, 46);

  updater.add("Function updater", dummy_diagnostic);
  DummyClass dc;
  updater.add("Method updater", &dc, &DummyClass::produce_diagnostics);

  diagnostic_updater::FunctionDiagnosticTask lower("Lower-bound check",
                                                   boost::bind(&check_lower_bound, _1));
  diagnostic_updater::FunctionDiagnosticTask upper("Upper-bound check",
                                                   boost::bind(&check_upper_bound, _1));

  diagnostic_updater::CompositeDiagnosticTask bounds("Bound check");
  bounds.addTask(&lower);
  bounds.addTask(&upper);

  updater.add(bounds);

  DummyTask prikol;
  updater.add(prikol);

  updater.broadcast(0, "Doing important initialization stuff.");

  ros::Publisher pub1 = nh.advertise<std_msgs::Bool>("topic1", 1);
  ros::Publisher pub2_temp = nh.advertise<std_msgs::Bool>("topic2", 1);
  ros::Duration(2).sleep(); // It isn't important if it doesn't take time.

  double min_freq = 0.5; // If you update these values, the
  double max_freq = 2; // HeaderlessTopicDiagnostic will use the new values.
  diagnostic_updater::HeaderlessTopicDiagnostic pub1_freq("topic1", updater,
                                                          diagnostic_updater::FrequencyStatusParam(&min_freq, &max_freq, 0.1, 10));

  pub1_freq.addTask(&lower); // (This wouldn't work if lower was stateful).

  updater.force_update();

  if (!updater.removeByName("Bound check"))
    ROS_ERROR("The Bound check task was not found when trying to remove it.");

  while (nh.ok())
  {
    std_msgs::Bool msg;
    ros::Duration(0.1).sleep();

    msg.data = false;
    pub1.publish(msg);
    pub1_freq.tick();

    updater.update();
  }

  return 0;
}
