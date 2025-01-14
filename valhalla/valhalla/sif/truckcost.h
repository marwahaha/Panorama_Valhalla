#ifndef VALHALLA_SIF_TRUCKCOST_H_
#define VALHALLA_SIF_TRUCKCOST_H_

#include <cstdint>
#include <valhalla/sif/dynamiccost.h>

/*
Armin H.
*/
#include <baldr/graphreader.h>
/*
Armin H.
*/


namespace valhalla {
namespace sif {

/**
 * Create a truckcost
 * @param  config  Property tree with configuration / options.
 */
cost_ptr_t CreateTruckCost(const boost::property_tree::ptree& config, baldr::GraphReader& graphreader);

}
}

#endif  // VALHALLA_SIF_TRUCKCOST_H_
