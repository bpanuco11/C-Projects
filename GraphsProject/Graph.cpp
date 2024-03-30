#include "Graph.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <limits>
#include <unordered_set>
#include <iostream>

using namespace std;

Graph::Graph(const char* const& edgelist_csv_fn) {
    ifstream file(edgelist_csv_fn);
    string line;
    //int new_line = 0;
    while (getline(file, line)) {  // read one line from the file
        istringstream ss(line);      // create istringstream of current line
        string node1, node2, weight; // helper vars
        getline(ss, node1, ',');     // store first column in "first"
        getline(ss, node2, ',');    // store second column in "second"
        getline(ss, weight, '\n');    // store third column in "third"
        csv_tuples.push_back(make_tuple(node1, node2, stod(weight)));
        //new_line++;
        node_set.insert(node1);
        node_set.insert(node2);
    }
    file.close();
}

unsigned int Graph::num_nodes() {
    return node_set.size();
}

vector<string> Graph::nodes() {
    vector<string> node_array(node_set.begin(), node_set.end());
    return node_array;
}

unsigned int Graph::num_edges() {
    return csv_tuples.size();
}


double Graph::edge_weight(string const& u_label, string const& v_label) {
    for (const auto& tuple : csv_tuples) {
        if (get<0>(tuple) == u_label && get<1>(tuple) == v_label || get<1>(tuple) == u_label && get<0>(tuple) == v_label)
            return get<2>(tuple);
    }
    return -1;
}

/**
 * Return the number of neighbors of a given node.
 * @param node_label The label of the query node.
 * @return The number of neighbors of the node labeled by `node_label`.
 */
unsigned int Graph::num_neighbors(string const& node_label) {
    unsigned int neighborCount = 0;
    for (const auto& tuple : csv_tuples) {
        if (get<0>(tuple) == node_label || get<1>(tuple) == node_label)
            neighborCount++;
    }
    return neighborCount;
}


/**
 * Return a `vector` containing the labels of the neighbors of a given node.
 * The neighbors can be in any order within the `vector`.
 * Example: If our graph has edges "A"<-(0.1)->"B" and "A"<-(0.2)->"C", if we call this function on "A", we would return the following `vector`: {"B", "C"}
 * @param node_label The label of the query node.
 * @return A `vector` containing the labels of the neighbors of the node labeled by `node_label`.
 */
vector<string> Graph::neighbors(string const& node_label) {
    vector<string> neighborhood;
    for (const auto& tuple : csv_tuples) {
        if (get<0>(tuple) == node_label || get<1>(tuple) == node_label) {
            if (get<0>(tuple) == node_label)
                neighborhood.push_back(get<1>(tuple));
            else
                neighborhood.push_back(get<0>(tuple));
        }
    }
    return neighborhood;
}

/**
 * Return the shortest unweighted path from a given start node to a given end node as a `vector` of `node_label` strings, including the start node.
 * If there does not exist a path from the start node to the end node, return an empty `vector`.
 * If there are multiple equally short unweighted paths from the start node to the end node, you can return any of them.
 * If the start and end are the same, the vector should just contain a single element: that node's label.
 * Example: If our graph has edges "A"<-(0.1)->"B", "A"<-(0.5)->"C", "B"<-(0.1)->"C", and "C"<-(0.1)->"D", if we start at "A" and end at "D", we would return the following `vector`: {"A", "C", "D"}
 * Example: If we start and end at "A", we would return the following `vector`: {"A"}
 * @param start_label The label of the start node.
 * @param end_label The label of the end node.
 * @return The shortest unweighted path from the node labeled by `start_label` to the node labeled by `end_label`, or an empty `vector` if no such path exists.
 */
vector<string> Graph::shortest_path_unweighted(string const& start_label, string const& end_label) {
    unordered_map<string, string> parent; 
    bool was_end_found = false;
    queue<string> label_queue;
    label_queue.push(start_label);
    parent[start_label] = ""; 

    while (!label_queue.empty()) {
        string current_label = label_queue.front();
        label_queue.pop();

        if (current_label == end_label) {
            was_end_found = true;
            break;
        }

        for (const auto& tuple : csv_tuples) {
            if (get<0>(tuple) == current_label || get<1>(tuple) == current_label) {
                string neighbor;
                if (get<0>(tuple) == current_label) {
                    neighbor = get<1>(tuple);
                    if (parent.find(neighbor) == parent.end()) {
                        parent[neighbor] = current_label;
                        label_queue.push(neighbor);
                    }
                } // end inner if
                else {
                    neighbor = get<0>(tuple);
                    if (parent.find(neighbor) == parent.end()) {
                        parent[neighbor] = current_label;
                        label_queue.push(neighbor);
                    }
                } // end inner else

            } // end outer if

        } // end inner loop
    } // end outer loop

    vector<string> path;
    if (was_end_found) {
        string node = end_label;
        while (node != "") {
            path.insert(path.begin(), node);
            node = parent[node];
        }
    }
    return path;
}

/**
 * Return the shortest weighted path from a given start node to a given end node as a `vector` of (`from_label`, `to_label`, `edge_weight`) tuples.
 * If there does not exist a path from the start node to the end node, return an empty `vector`.
 * If there are multiple equally short weighted paths from the start node to the end node, you can return any of them.
 * If the start and end are the same, the vector should just contain a single element: (`node_label`, `node_label`, -1)
 * Example: If our graph has edges "A"<-(0.1)->"B", "A"<-(0.5)->"C", "B"<-(0.1)->"C", and "C"<-(0.1)->"D", if we start at "A" and end at "D", we would return the following `vector`: {("A","B",0.1), ("B","C",0.1), ("C","D",0.1)}
 * Example: If we start and end at "A", we would return the following `vector`: {("A","A",-1)}
 * @param start_label The label of the start node.
 * @param end_label The label of the end node.
 * @return The shortest weighted path from the node labeled by `start_label` to the node labeled by `end_label`, or an empty `vector` if no such path exists.
 */
vector<tuple<string, string, double>> Graph::shortest_path_weighted(string const& start_label, string const& end_label) {
    unordered_map<string, double> distance;
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> priorityqueue;
    vector<tuple<string, string, double>> path;
    unordered_map<string, string> parent;

    // immediately return distance -1 if start and end labels are equal
    if (start_label == end_label) {
        path.push_back(make_tuple(start_label, end_label, -1));
        return path;
    }

    for (const auto& node : node_set) {
        // by dijkstra's set to infinity by default
        distance[node] = numeric_limits<double>::infinity();
    }
    // from start set to 0 by dijkstra's
    distance[start_label] = 0;
    priorityqueue.push({ 0, start_label });
    // dijkstra's algorithm
    while (!priorityqueue.empty()) {
        string label1 = priorityqueue.top().second;
        priorityqueue.pop();

        for (const auto& tuple : csv_tuples) {
            string label2;
            double weight;

            if (get<0>(tuple) == label1 || get<1>(tuple) == label1) {
                weight = get<2>(tuple);
                (get<0>(tuple) == label1) ? label2 = get<1>(tuple) : label2 = get<0>(tuple);
            }
            else
                continue;
            
            if (distance[label1] + weight < distance[label2]) {
                distance[label2] = distance[label1] + weight;
                parent[label2] = label1;
                priorityqueue.push({ distance[label2], label2 });
            }
        }
    }

    if (parent.find(end_label) != parent.end()) {
        string node = end_label;
        while (node != start_label) {
            string previous = parent[node];
            path.insert(path.begin(), make_tuple(previous, node, edge_weight(previous, node)));
            node = previous;
        }
    }

    return path;
}


/**
 * Given a threshold, ignoring all edges with a weight greater than the threshold, return the connected components of the resulting graph as a `vector` of `vector` of `string` (i.e., each connected component is a `vector` of `string`, and you return a `vector` containing all of the connected components).
 * The components can be in any order, and the node labels within a component can be in any order.
 * Example: If our graph has edges "A"<-(0.1)->"B", "B"<-(0.2)->"C", "D"<-(0.3)->"E", and "E"<-(0.4)->"F", if our threshold is 0.3, we would output the following connected components: {{"A","B","C"}, {"D","E"}, {"F"}}
 * @param threshold The maximum edge weight to consider
 * @return The connected components of this graph, if we ignore edges with weight greater than `threshold`, as a `vector<vector<string>>`.
 */
/*vector<vector<string>> Graph::connected_components(double const& threshold) {
    vector<vector<string>> connected_label_list;
    set<string> connected_set, visited;
    vector<string> neighbor_nodes;
    double weight;
    for (string node : node_set) {
        
        neighbor_nodes = neighbors(node);
        for (string neighbor : neighbor_nodes) {
            if (visited.find(neighbor) != visited.end())
                continue;
            weight = edge_weight(node, neighbor);
            if (weight <= threshold) {
                connected_set.insert(node);
                connected_set.insert(neighbor);
                visited.insert(node);
            }
        }
        connected_label_list.push_back(vector<string>(connected_set.begin(), connected_set.end()));
        connected_set.clear();
    }
    return connected_label_list;
}*/
vector<vector<string>> Graph::connected_components(double const& threshold) {
    vector<vector<string>> connected_label_list;
    set<string> visited;
    vector<string> neighbor_nodes;
    double weight;

    for (string node : node_set) {
        if (visited.find(node) != visited.end())
            continue;
        
        set<string> connected_set;
        queue<string> queue;
        queue.push(node);

        while (!queue.empty()) {
            string current_node = queue.front();
            queue.pop();

            if (visited.find(current_node) != visited.end())
                continue;
            

            visited.insert(current_node);
            connected_set.insert(current_node);
            neighbor_nodes = neighbors(current_node);
            for (string neighbor : neighbor_nodes) {
                weight = edge_weight(current_node, neighbor);
                if (weight <= threshold) {
                    queue.push(neighbor);
                }
            }
        }
        connected_label_list.push_back(vector<string>(connected_set.begin(), connected_set.end()));
    }

    return connected_label_list;
}


/**
 * Return the smallest `threshold` such that, given a start node and an end node, if we only considered all edges with weights <= `threshold`, there would exist a path from the start node to the end node.
 * If there does not exist such a threshold (i.e., it's impossible to go from the start node to the end node even if we consider all edges), return -1.
 * Example: If our graph has edges "A"<-(0.2)->"B", "B"<-(0.4)->"C", and "A"<-(0.5)->"C", if we start at "A" and end at "C", we would return 0.4.
 * Example: If we start and end at "A", we would return 0
 * Note: The smallest connecting threshold isn't necessarily part of the shortest weighted path (such as in the first example above)
 * @param start_label The label of the start node.
 * @param end_label The label of the end node.
 * @return The smallest `threshold` such that, if we only considered all edges with weights <= `threshold, there would exist a path connecting the nodes labeled by `start_label` and `end_label`, or -1 if no such threshold exists.
 */
double Graph::smallest_connecting_threshold(string const& start_label, string const& end_label) {
    // label1 , label2, weight
    unordered_map<string, pair<string, double>> mst_edges;
    unordered_set<string> visited;
    // keep track of mst weights using pair of pairs array: pair(weight, pair(label1,label2))
    priority_queue<pair<double, pair<string, string>>, vector<pair<double, pair<string, string>>>, greater<pair<double, pair<string, string>>>> priorityqueue;
    
   // Immediately return 0 if start and end label are the same node
    if(start_label == end_label)
        return 0;

    // Use Prim's in order to generate MST based on weight comparison
    visited.insert(start_label);
    for (const auto& neighbor : neighbors(start_label)) {
        double weight = edge_weight(start_label, neighbor);
        priorityqueue.push({weight, {start_label, neighbor}});
    }

    // Generate the MST from our priorityqueue
    while (!priorityqueue.empty()) {

        auto edge = priorityqueue.top();
        priorityqueue.pop();
        double weight = edge.first;
        string label1 = edge.second.first;
        string label2 = edge.second.second;


        if (visited.find(label2) == visited.end()) {
            mst_edges[label2] = {label1, weight};
            visited.insert(label2);
            for (const auto& neighbor : neighbors(label2)) {

                if (visited.find(neighbor) == visited.end()) {
                    double weight = edge_weight(label2, neighbor);
                    priorityqueue.push({weight, {label2, neighbor}});
                }
            }
        }

    }
    // if end_label is nowhere in the MST, then start_label cannot reach end_label, so return -1
    if(mst_edges.find(end_label) == mst_edges.end())
        return -1;
    // generate a path from start_label to end_label 
    vector<string> path;
    string current = end_label;
    while (current != start_label) {
        path.push_back(current);
        current = mst_edges[current].first;
    }
    path.push_back(start_label);
    // Last step is to find the maximum edge from our path
    double max_edge = -1;
    for (size_t i = 0; i < path.size() - 1; i++) {
        double weight = edge_weight(path[i], path[i+1]);
        max_edge = max(max_edge, weight);
    }
    return max_edge; 
}