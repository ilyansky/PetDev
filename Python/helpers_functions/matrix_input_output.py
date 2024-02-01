def input_matrix(row):
    return [[int(i) for i in input().split()] for _ in range(row)]


def print_matrix(matrix, row):
    [print(*matrix[i]) for i in range(row)]


# def print_matrix_with_space(matrix, row_col):
#     for r in range(row_col[0]):
#         for c in range(row_col[1]):
#             print(str(matrix[r][c]).ljust(2), end=' ')
#         print()


row, col = [int(i) for i in input().split()]
matrix = input_matrix(row)
print()
print_matrix(matrix, row)
print(matrix)
