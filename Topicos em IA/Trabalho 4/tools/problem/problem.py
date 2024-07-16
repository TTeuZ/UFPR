import numpy as np

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
        self.precomputed_constraints = self._precompute_constraints()
        
        self.solved = False

    
    def _precompute_constraints(self):
        precomputed_constraints = [[] for _ in range(self.vars_qty)]

        for index in range(1, self.vars_qty):
            for constraint in self.constraints:
                if np.all(constraint.scope <= index):
                    precomputed_constraints[index].append(constraint)

        return precomputed_constraints