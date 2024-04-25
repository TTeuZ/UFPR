# Class that represent a CSP Problem
# vars_qty: Quantity of problem variables
# variables: Array of tuples (domain_size, [domain])
# constraints_qty: Quantity of problem constraints
# constraints: Array of constraints (constraints.class)

class problem():
    def __init__(self, vars_qty, variables, constraints_qty, constraints):
        self.vars_qty = vars_qty
        self.constraints_qty = constraints_qty

        self.variables = variables
        self.constraints = constraints
        
        self.solved = False