import copy

class shared_state:
    def __init__(self):
        self.solved = False


class problem():
    def __init__(self, vars_qty, variables, constraints_qty, constraints, precomputed_constraints = None, state = None):
        self.vars_qty, self.constraints_qty = vars_qty, constraints_qty
        self.variables, self.constraints = variables, constraints

        self.precomputed_constraints = self._precompute_constraints() if precomputed_constraints == None else precomputed_constraints
        self.shared_state = shared_state() if state == None else state


    @property
    def solved(self):
        return self.shared_state.solved


    @solved.setter
    def solved(self, value):
        self.shared_state.solved = value

    
    def _precompute_constraints(self):
        return [
            [constraint for constraint in self.constraints if var_index in constraint.scope]
            for var_index in range(self.vars_qty)
        ]
    

    def conditional_copy(self):
        new_variables = copy.deepcopy(self.variables)        
        return problem(self.vars_qty, new_variables, self.constraints_qty, self.constraints, self.precomputed_constraints, self.shared_state)