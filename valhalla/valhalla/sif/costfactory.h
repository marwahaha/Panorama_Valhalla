#ifndef VALHALLA_SIF_COSTFACTORY_H_
#define VALHALLA_SIF_COSTFACTORY_H_

#include <map>
#include <memory>

#include <valhalla/sif/autocost.h>
#include <valhalla/sif/bicyclecost.h>
#include <valhalla/sif/motorscootercost.h>
#include <valhalla/sif/pedestriancost.h>
#include <valhalla/sif/truckcost.h>
#include <valhalla/sif/transitcost.h>
#include <valhalla/baldr/rapidjson_utils.h>
#include "baldr/graphreader.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace valhalla {
namespace sif {

/**
* Generic factory class for creating objects based on type name.
*/
template <class cost_t>
class CostFactory {
 public:
  typedef std::shared_ptr<cost_t> cost_ptr_t;
  //TODO: might want to have some configurable params to each cost type
  //Armin H. changed so all costs require a graph reader input, since variable arguments cannot be done with dynamic typing without significantly changing the code base.
  //OLD: typedef cost_ptr_t (*factory_function_t)(const boost::property_tree::ptree& config);
  typedef cost_ptr_t (*factory_function_t)(const boost::property_tree::ptree& config, baldr::GraphReader& graphreader);
  //Armin H.

  /**
   * Constructor
   */
  CostFactory() { }

  /**
   * Register the callback to create this type of cost
   *
   * @param name       the name of the cost that the function creates
   * @param function   the function pointer to call to actually create the cost object
   */
  void Register(const std::string& name, factory_function_t function) {
    factory_funcs_.emplace(name, function);
  }

  //Armin H. Removed because of reason above.
  /**
   * Make a cost from its name
   * @param name    the name of the cost to create
   * @param config  Property tree with configuration / cost options
   
  cost_ptr_t Create(const std::string& name,
                    const boost::property_tree::ptree& config) const {
    auto itr = factory_funcs_.find(name);
    if (itr == factory_funcs_.end()) {
      throw std::runtime_error("No costing method found for '" + name + "'");
    }
    //create the cost using the function pointer
    return itr->second(config);
  }
  */
  //Armin H.

  //Armin H. Made custom auto factory create to pass graph reader into the AutoCosting class
  cost_ptr_t Create(const std::string& name,
                    const boost::property_tree::ptree& config,
                    baldr::GraphReader& graphreader) const {
    auto itr = factory_funcs_.find(name);
    if (itr == factory_funcs_.end()) {
      throw std::runtime_error("No costing method found for '" + name + "'");
    }
    //create the cost using the function pointer
    return itr->second(config, graphreader);
  }
  //Armin H.

  //Armin H. Removed because of typedef reason.
  /*
  cost_ptr_t Create(const std::string& name,
                    const rapidjson::Value& config) const {
    if (config.IsNull())
      return Create(name, boost::property_tree::ptree{});
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    config.Accept(writer);
    boost::property_tree::ptree pt;
    std::istringstream is(buffer.GetString());;
    boost::property_tree::read_json(is, pt);
    return Create(name, pt);
  }
  */
  //Armin H.

  //Armin H. Made custom auto factory create to pass graph reader into the AutoCosting class
  cost_ptr_t Create(const std::string& name,
                    const rapidjson::Value& config,
                    baldr::GraphReader& graphreader) const {
    if (config.IsNull())
    {
      boost::property_tree::ptree pt;
      return Create(name, pt, graphreader);
    }
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    config.Accept(writer);
    boost::property_tree::ptree pt;
    std::istringstream is(buffer.GetString());;
    boost::property_tree::read_json(is, pt);
    return Create(name, pt, graphreader);
  }
  //Armin H.

 private:
  std::map<std::string, factory_function_t> factory_funcs_;
};

}
}

#endif // VALHALLA_SIF_COSTFACTORY_H_
