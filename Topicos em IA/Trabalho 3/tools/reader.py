from tools.problem.constraint import constraint
from tools.problem.problem import problem

def read_problem(path):
    with open(path, "r") as file:
        vars_qty, variables = int(file.readline()), []
        for _ in range(vars_qty):
            domain = [int(elem) for elem in file.readline().split(" ")]
            domain_size = domain.pop(0)
            variables.append((domain_size, domain))

        constraints_qty, constraints = int(file.readline()), []
        for _ in range(constraints_qty):
            constraint_type = file.readline()[0]

            scope = [int(elem) for elem in file.readline().split(" ")]
            scope_size = scope.pop(0)

            tuples = [int(elem) for elem in file.readline().split(" ")]
            tuples_size = tuples.pop(0)
            tuples = [tuple(tuples[i:i+scope_size]) for i in range(0, len(tuples), scope_size)]

            new_constraint = constraint(constraint_type, (scope_size, scope), (tuples_size, tuples))
            constraints.append(new_constraint)

    return problem(variables, constraints)