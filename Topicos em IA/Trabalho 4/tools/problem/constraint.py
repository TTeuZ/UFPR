DEFAULT_VALUE = -1

class constraint():
    def __init__(self, constraint_type, scope, tuples):
        self.type = constraint_type.upper() == "V"
        
        self.scope_size, self.scope = scope
        self.tuples_size, self.tuples = tuples


    def _check_v_tuple(self, variables, r_tuple):    
        return all(
            var.assigned_value == value if var.assigned_value != DEFAULT_VALUE else value in var.domain
            for var, value in zip(variables, r_tuple)
        )
    

    def _check_i_tuple(self, variables, r_tuple):
        return any(
            var.assigned_value != value if var.assigned_value != DEFAULT_VALUE else any(x != value for x in var.domain)
            for var, value in zip(variables, r_tuple)
        )


    def is_satisfied(self, problem, variable):
        restricted_variables = [problem.variables[index] for index in self.scope]
        index_in_constraint = restricted_variables.index(variable)
        related_tuples = [r_tuple for r_tuple in self.tuples if r_tuple[index_in_constraint] == variable.assigned_value]

        if self.type:
            return any(self._check_v_tuple(restricted_variables, r_tuple) for r_tuple in related_tuples)
        else:
            if not related_tuples: return True
            return all(self._check_i_tuple(restricted_variables, r_tuple) for r_tuple in related_tuples)