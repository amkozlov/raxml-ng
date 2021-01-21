#include "EnergyMonitor.hpp"

#include "../common.h"

using namespace std;

EnergyMonitor global_energy_monitor;

static inline string  pkg_energy_path(int pkg_id)
{
  return  "/sys/class/powercap/intel-rapl/intel-rapl:" + to_string(pkg_id);
}

static inline string  pkg_subdomain_path(int pkg_id, int sub_id)
{
  return  pkg_energy_path(pkg_id) + "/intel-rapl:" + to_string(pkg_id) + ":" + to_string(sub_id);
}

static inline string  pkg_name_fname(string pkg_path)
{
  return  pkg_path + "/name";
}

static inline string  pkg_energy_fname(string pkg_path)
{
  return  pkg_path + "/energy_uj";
}

static inline string  pkg_energy_range_fname(string pkg_path)
{
  return  pkg_path + "/max_energy_range_uj";
}

template<typename T>
static inline T read_value(string fname)
{
  T val;
  ifstream fs(fname);
  fs >> val;
  return val;
}

EnergyMonitor::EnergyMonitor ()
{
  // so far, power monitoring only works on Linux
#if defined(__linux__)
  init_packages();
//  for(auto& pkg: _pkg_list)
//    printf("RAPL pkg %d:%d -> %s\n", pkg.pkg_id, pkg.sub_id, pkg.name.c_str());
  _active = !_pkg_list.empty();
#else
  _active = false;
#endif
  _consumed_joules = 0;
  _last_update_ts = time(NULL);
}

void EnergyMonitor::reset()
{
  _consumed_joules = 0;
  update();
}

void EnergyMonitor::update(double interval)
{
  if (!_active || (interval > 0. && time(NULL) - _last_update_ts  < interval))
    return;

  for(auto& pkg: _pkg_list)
  {
    size_t energy_uj = read_value<size_t>(pkg.energy_fname);

    // account for overflow
    auto diff_uj = (energy_uj > pkg.last_energy_uj) ? energy_uj - pkg.last_energy_uj :
        energy_uj + (pkg.max_energy_range_uj - pkg.last_energy_uj);

    pkg.last_energy_uj = energy_uj;
    _consumed_joules += diff_uj / 1e6f; // convert to Joules
  }
  _last_update_ts = time(NULL);
}

double EnergyMonitor::consumed_joules(bool do_update)
{
  if (do_update)
    update();
  return _consumed_joules;
}

double EnergyMonitor::consumed_wh(bool do_update)
{
  return consumed_joules(do_update) / 3600.;
}

void EnergyMonitor::enable()
{
  _active = true;
  update();
}

void EnergyMonitor::disable()
{
  _active = false;
}

bool EnergyMonitor::active() const
{
  return _active;
}

bool EnergyMonitor::add_package(RAPLPackage& pkg)
{
  auto pkg_path = pkg.sub_id < 0 ? pkg_energy_path(pkg.pkg_id) :
                                   pkg_subdomain_path(pkg.pkg_id, pkg.sub_id);
  pkg.energy_fname = pkg_energy_fname(pkg_path);

  /* Check if we have permissions to read energy_uj file.
   * Starting from kernel 5.10 (and earlier with patch) it requires root privileges!
   */
  if (!sysutil_file_exists(pkg.energy_fname, R_OK))
    return sysutil_file_exists(pkg.energy_fname, F_OK);

  pkg.name = read_value<string>(pkg_name_fname(pkg_path));

  /* It seems that DRAM subzone energy is NOT included in the parent package value,
   * whereas other subzones (cores, uncore) are. This design choice is extremely confusing,
   * and not clearly documented. So for now, we just ignore all subzones except DRAM.
   * There is no guarantee this workaround will work as intended on all systems,
   * especially the future ones. */
  if (pkg.sub_id >= 0 && pkg.name != "dram")
    return true;

  bool proceed = true;
  if (pkg.name == "psys")
  {
    /* BINGO! we got system-wide energy counter, ignore all the rest */
    _pkg_list.clear();
    proceed = false;
  }

  pkg.max_energy_range_uj = read_value<size_t>(pkg_energy_range_fname(pkg_path));
  pkg.last_energy_uj = read_value<size_t>(pkg.energy_fname);
  _pkg_list.push_back(pkg);

  return proceed;
}

void EnergyMonitor::init_packages()
{
  static const int max_packages = 1024;
  /* iterate over packages -> CPU sockets */
  for(int i = 0; i < max_packages; i++)
  {
    RAPLPackage pkg;
    pkg.pkg_id = i;
    pkg.sub_id = -1;
    if (!add_package(pkg))
      break;

    /* iterate over subdomains -> DRAM and other weird stuff */
    for(int j = 0; j < max_packages; j++)
    {
      pkg.sub_id = j;
      if (!add_package(pkg))
        break;
    }
  }
}
