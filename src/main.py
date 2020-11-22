
from collections import defaultdict

def color_nodes(graph, color_map):


    # Consider nodes in descending degree
    for node in sorted(graph, key=lambda x: len(graph[x]), reverse=True):
        if color_map[node-1] == 0:
            neighbor_colors = set(color_map.get(neigh-1) for neigh in graph[node])

            color_map[node-1] = next(
                color for color in range(1, len(graph)+1) if color not in neighbor_colors
            )

    return color_map

def main():

    num_nodes, num_edges = list(map(int, input().strip().split(" ")))
    edges = [tuple(map(int, input().strip().split(" "))) for _ in range(num_edges)]
    colors = list(map(int, input().strip().split(" ")))

    graph = defaultdict(list)
    for edge in edges:
        _to = edge[0]
        _from = edge[1]

        graph[_to].append(_from)
        graph[_from].append(_to)
    
    color_map = {}
    for i, color in enumerate(colors):
        color_map[i] = color

    # print(graph)
    # print(color_map)

    solution = color_nodes(graph, color_map)

    original_colors = len(set(colors)) if 0 not in set(colors) else len(set(colors))-1
    new_colors = len(set(solution.values()))
    color_diff = new_colors - original_colors

    # print(solution)
    print(color_diff)
    for v in solution.values():
        print(v, end=" ")

    print()

if __name__ == "__main__":
    main()
