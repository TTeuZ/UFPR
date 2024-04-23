from tools.problem.constraint import constraint
from tools.problem.problem import problem
import numpy as np

def read_problem(path):
    with open(path, "r") as file:
        vars_qty, variables = int(file.readline()), []
        for _ in range(vars_qty):
            domain = [int(elem) for elem in file.readline().split(" ")]
            domain_size = domain.pop(0)
            variables.append((domain_size, np.array(domain)))

        constraints_qty, constraints = int(file.readline()), []
        for _ in range(constraints_qty):
            constraint_type = file.readline()[0]

            scope = [int(elem) for elem in file.readline().split(" ")]
            scope_size = scope.pop(0)
            scope = np.array([elem - 1 for elem in scope])

            tuples = [int(elem) for elem in file.readline().split(" ")]
            tuples_size = tuples.pop(0)
            tuples = [tuple(tuples[i:i+scope_size]) for i in range(0, len(tuples), scope_size)]

            new_constraint = constraint(constraint_type, (scope_size, scope), (tuples_size, tuples))
            constraints.append(new_constraint)

    return problem(vars_qty, variables, constraints_qty, constraints)


def write_result(result):
    if -1 in result:
        print("INVIAVEL")
    else:
        for index, value in enumerate(result):
            print(f"x{index + 1} = {value}")