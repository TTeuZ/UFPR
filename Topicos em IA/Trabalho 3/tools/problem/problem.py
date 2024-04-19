# Class that represent a CSP Problem
# _variables: Array of tuples (domain_size, [domain])
# _constraints: Array of constraints (constraints.class)

class problem():
    def __init__(self, variables, constraints):
        self._variables = variables
        self._constraints = constraints