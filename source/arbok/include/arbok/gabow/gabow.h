
#include <tuple>
#include <vector>
#include <set>
#include <list>
#include <functional>
#include <memory>
#include <optional>

#include <arbok/data_structures/dsu.h>
#include <arbok/data_structures/activeset.h>

namespace arbok {

/*struct OffsetDSU {
    std::vector<int> p; // ?
    //explicit OffsetDSU(int n);
    int find(int i);
    int find_value(int i);
    bool join(int i, int j);
};*/

struct Edge {
    Edge(int _from, int _to, int _weight, int _orig_weight) : from(_from), to(_to), weight(_weight), orig_weight(_orig_weight) {};
    int from, to, weight, orig_weight;
    inline bool operator<(const Edge& rhs) const { return std::tie(weight,from) < std::tie(rhs.weight, rhs.from); }
    inline bool operator==(const Edge& rhs) const { return std::tie(weight,from) == std::tie(rhs.weight,rhs.from); }
    inline bool operator>(const Edge& rhs) const { return rhs < *this; }
};
static const Edge NO_EDGE = {(int)1e9, (int)1e9, (int)1e9, (int)1e9};

class Gabow {
public:
    Gabow(int n);
    ~Gabow() = default;

    void create_edge(int from, int to, int weight);

    long long run(int root);

    void debug();
    // std::vector<Edge> reconstruct();

protected:
    const int num_vertices;
    DSU co; // for actual merges; TODO this needs to also manage offsets and needs to work with path compression // 2021 update: kp was wir hier meinten mit dem todo, das sollte ja eig so sein
    std::vector<int> offsets;

    struct EdgeLink {
        EdgeLink(int from, int to, int weight, int _id, std::optional<std::list<int>::iterator> _exit_list_iter, std::optional<std::list<int>::iterator> _passive_set_iter) : e(from, to, weight, weight), id(_id), exit_list_iter(_exit_list_iter), passive_set_iter(_passive_set_iter) {};
        Edge e;
        int id; // pos in edges
        std::optional<std::list<int>::iterator> exit_list_iter;
        std::optional<std::list<int>::iterator> passive_set_iter;
    };

    std::vector<EdgeLink> edges; // all edges
    std::vector<std::vector<int>> incoming_edges; // adjacency list pointing into edges

    std::vector<int> growth_path;
    std::vector<int> growth_path_edges;
    std::vector<bool> in_path;

    std::vector<std::list<int>> exit_list; // stores the index into edges
    std::vector<std::list<int>> passive_set; // stores the index into edges
    std::vector<std::shared_ptr<AbstractActiveSet>> active_set; // shared_ptr to avoid object-cutoff that would happen if we insert polymorphic objects here
    std::vector<int> active_set_pointer; // maps vertices to keys into the activeset

    std::vector<int> chosen;

    void add_edge_to_exit_list(int v, int edge_id);
    void insert_vertex_into_activeset(int v, int u, int key); // insert v into u's AS
    void insert_edge_into_passiveset(int edge_id, int u); // insert edge_id into u's PS
    void init_root(int root);
    void ensure_strongly_connected(int root);
    void extendPath(int u);
    int contractPathPrefix(int u);

};

}  // end namespace arbok

