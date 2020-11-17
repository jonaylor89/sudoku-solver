def color_nodes(graph): # Soon (graph, colors)

    color_map = {}

    # Consider nodes in descending degree
    for node in sorted(graph, key=lambda x: len(graph[x]), reverse=True):

        neighbor_colors = set(color_map.get(neigh) for neigh in graph[node])

        color_map[node] = next(
            color for color in range(len(graph)) if color not in neighbor_colors
        )

    return color_map


def sudoku(graph, colors):
    pass


def main():

    num_nodes, num_edges = list(map(int, input().strip().split(" ")))
    edges = [tuple(map(int, input().strip().split(" "))) for _ in range(num_edges)]
    colors = list(map(int, input().strip().split(" ")))

    # print(f"Number of Nodes {num_nodes} & Edges {num_edges}")
    # print(f"Edges {edges}")
    # print(f"Colors {colors}")

    # color_nodes(neighbor_graph)
    # sudoku(edges, colors)


if __name__ == "__main__":
    main()
