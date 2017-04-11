////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Michael Hackstein
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGOD_GRAPH_SHORTEST_PATH_OPTIONS_H
#define ARANGOD_GRAPH_SHORTEST_PATH_OPTIONS_H 1

#include "Graph/BaseOptions.h"

namespace arangodb {

namespace transaction {
class Methods;
}

namespace velocypack {
class Builder;
class Slice;
}
namespace graph {

struct ShortestPathOptions : public BaseOptions {

 public:
  std::string start;
  std::string direction;
  bool useWeight;
  std::string weightAttribute;
  double defaultWeight;
  bool bidirectional;
  bool multiThreaded;
  std::string end;
  arangodb::velocypack::Builder startBuilder;
  arangodb::velocypack::Builder endBuilder;

  explicit ShortestPathOptions(transaction::Methods* trx);

  ShortestPathOptions(transaction::Methods* trx,
                      arangodb::velocypack::Slice const& info);

  ~ShortestPathOptions();

  // Creates a complete Object containing all EngineInfo
  // in the given builder.
  void buildEngineInfo(arangodb::velocypack::Builder&) const override;

  void setStart(std::string const&);
  void setEnd(std::string const&);

  arangodb::velocypack::Slice getStart() const;
  arangodb::velocypack::Slice getEnd() const;

  /// @brief Build a velocypack for cloning in the plan.
  void toVelocyPack(arangodb::velocypack::Builder&) const override;

  // Creates a complete Object containing all index information
  // in the given builder.
  void toVelocyPackIndexes(arangodb::velocypack::Builder&) const override;

  /// @brief Estimate the total cost for this operation
  double estimateCost(size_t& nrItems) const override;

};

} // namespace graph
} // namespace arangodb

#endif