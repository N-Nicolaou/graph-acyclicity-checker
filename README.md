# Directed Graph Acyclicity Checker

**Module:** 5SENG003W Algorithms and Data Structures — University of Westminster  
**Grade: 100%**

A C++ program that determines whether a directed graph is **acyclic** (a DAG) or **cyclic**, and if cyclic, identifies and reports the exact cycle.

---

## What It Does

Given a directed graph G = (V, E) from an input file, the program either:
- ✅ Confirms the graph is a **DAG** and outputs the full sink-elimination sequence
- 🔄 Identifies the graph as **cyclic** and reports the exact cycle path

---

## How It Works

### Acyclicity Test — Sink Elimination
The algorithm is based on the theorem: *a finite directed graph is acyclic if and only if it contains a sink (a vertex with out-degree zero).*

1. If the graph is empty → **Acyclic**
2. If no sink exists → **Cyclic**
3. Remove any sink and all its incident edges → repeat from step 1

Every vertex on a cycle always has at least one outgoing edge, so it can never become a sink. The algorithm removes only non-cycle vertices until either the graph empties (acyclic) or no more sinks can be found (cyclic).

### Cycle Detection — DFS
When sink elimination terminates with vertices remaining, a DFS is performed on the residual graph. A `inStack[]` boolean array tracks the current recursion path. When a back edge is discovered, the cycle is reconstructed by tracing the `parent[]` array.

---

## Data Structure

The graph uses an **adjacency list with a reverse adjacency list**, built from three parallel arrays:

| Array | Purpose |
|-------|---------|
| `adj[v]` | Outgoing neighbours of v |
| `radj[v]` | Incoming neighbours of v (reverse edges) |
| `outdeg[v]` | Current out-degree; `-1` marks eliminated vertices |

The reverse adjacency list `radj` is the key optimisation — when a sink `v` is removed, only its true predecessors need their out-degree decremented, reducing each removal to O(deg⁻¹(v)) rather than O(E).

### Complexity

| Operation | Complexity |
|-----------|-----------|
| `addEdge(u, v)` | O(1) |
| `hasSink()` | O(V) |
| `removeVertex(v)` | O(deg⁻¹(v)) |
| `isAcyclic()` | O(V² + E) |
| `findCycle()` | O(V + E) |

---

## File Structure

```
├── Graph.h          # Class interface
├── Graph.cpp        # Algorithm implementation
├── Main.cpp         # Entry point & file parsing
└── Report.pdf       # Full technical report with complexity analysis & benchmarks
```

## Input Format

```
<vertex_count>
<from> <to>
<from> <to>
...
```

**Example (cyclic):**
```
8
10 9
9 37
37 7
7 39
39 25
25 3
3 24
24 10
```

**Example output:** `Cyclic: 10 – 9 – 37 – 7 – 39 – 25 – 3 – 24 – 10`

---

## Performance

Benchmarked across 90 test graphs (9 sizes × 5 acyclic + 5 cyclic instances):

| V | Avg Time (ms) |
|---|--------------|
| 40 | ~13ms |
| 640 | ~13ms |
| 2,560 | ~17ms |
| 5,120 | ~29ms |
| 10,240 | ~84ms |

The 2.9× increase from V=5,120 to V=10,240 is consistent with the predicted O(V²) growth from the `hasSink` linear scan. A queue-based variant could achieve O(V+E) for larger graphs.

---

## Built With
- C++
- Standard Library (`std::map`, `std::vector`)
- MPLABX / g++ compiler

