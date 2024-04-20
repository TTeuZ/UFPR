# Class that represent a CSP Problem
# _variables: Array of tuples (domain_size, [domain])
# _constraints: Array of constraints (constraints.class)

class problem():
    def __init__(self, vars_qty, variables, constraints_qty, constraints):
        self.vars_qty = vars_qty
        self.constraints_qty = constraints_qty

        self.variables = variables
        self.constraints = constraints
        self.solved = False