from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    # generating matrix
    matrix = [[(0, None) for x in range(len(b) + 1)] for y in range(len(a) + 1)]

    # base case
    for i in range(1, len(a) + 1):
        matrix[i][0] = (i, Operation.DELETED)
    for j in range(1, len(b) + 1):
        matrix[0][j] = (j, Operation.INSERTED)

    # fill in matrix with tuples (cost, operation)
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            # edit distance algorithm
            # costs for deletion, insertion and substitution
            delete_cost = matrix[i - 1][j][0] + 1
            insert_cost = matrix[i][j - 1][0] + 1
            substitute_cost = matrix[i - 1][j - 1][0]
            if a[i - 1] != b[j - 1]:
                substitute_cost += 1

            # edit distance is min cost of deletion, insertion, substitution
            if delete_cost < insert_cost and delete_cost < substitute_cost:
                matrix[i][j] = (delete_cost, Operation.DELETED)
            elif insert_cost < substitute_cost:
                matrix[i][j] = (insert_cost, Operation.INSERTED)
            else:
                matrix[i][j] = (substitute_cost, Operation.SUBSTITUTED)

    return matrix
