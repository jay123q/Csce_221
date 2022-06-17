#pragma once

#include <unordered_map>

#include "weighted-graph.hpp"
#include "graph-types.h"

template <typename T>
void computeIndegrees(const WeightedGraph<T>& graph, std::unordered_map<value_type<T>,int>& indegrees) {
    // TODO store the indegree for each vertex in the graph in the indegrees map
for (auto it = graph.begin(); it != graph.end(); ++it) 
{
    const auto & v = it->first;
    indegrees[v] =0;
}
    // for (value_type<T> i = 0; i < graph.size() ; i ++) {
    //         indegrees[i] = 0;

    //     }



    for (auto it = graph.begin(); it != graph.end(); ++it) 
    {
        for (auto iit : it->second) {
            // pair reference instead of iterators becasue no begin or end
            indegrees.at((iit.first)) += 1;
        }
    }
}
