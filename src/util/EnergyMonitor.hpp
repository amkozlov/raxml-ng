#ifndef RAXML_ENERGYMONITOR_HPP_
#define RAXML_ENERGYMONITOR_HPP_

#include <string>
#include <vector>

struct RAPLPackage
{
  int pkg_id;
  int sub_id;
  std::string energy_fname;
  size_t last_energy_uj;
  size_t max_energy_range_uj;
};

class EnergyMonitor
{
public:
  EnergyMonitor ();

  double consumed_wh();
  double consumed_joules();

  void reset();
  void update(double interval = 0.);

  void enable();
  void disable();
  bool active() const;

private:
  bool _active;
  std::vector<RAPLPackage> _pkg_list;
  double _consumed_joules;
  double last_update_ts;

  bool add_package(RAPLPackage& pkg);
  void init_packages();
};

extern EnergyMonitor global_energy_monitor;

#endif /* RAXML_ENERGYMONITOR_HPP_ */
