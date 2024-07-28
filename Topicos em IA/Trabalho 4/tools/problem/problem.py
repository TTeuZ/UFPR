from tools.problem.constraint import constraint
import copy

class shared_state:
    def __init__(self):
        self.solved = False


class problem():
    def __init__(self, vars_qty, variables, constraints_qty, constraints, precomputed_constraints = None, state = None):
        self.vars_qty = vars_qty
        self.constraints_qty = constraints_qty

        self.variables = variables
        self.constraints = constraints

        self.precomputed_constraints = self._precompute_constraints() if precomputed_constraints == None else precomputed_constraints
        self.shared_state = shared_state() if state == None else state


    @property
    def solved(self):
        return self.shared_state.solved


    @solved.setter
    def solved(self, value):
        self.shared_state.solved = value

    
    def _precompute_constraints(self):
        precomputed_constraints = [[] for _ in range(self.vars_qty)]

        for index in range(self.vars_qty):
            for constraint in self.constraints:
                if index in constraint.scope:
                    precomputed_constraints[index].append(constraint)

        return precomputed_constraints
    

    def conditional_copy(self):
        new_variables = copy.deepcopy(self.variables)        
        return problem(self.vars_qty, new_variables, self.constraints_qty, self.constraints, self.precomputed_constraints, self.shared_state)