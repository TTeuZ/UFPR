import numpy as np
from collections import defaultdict

# CSP Solver class
# Use a simple backtracking to find one solution (not optmal)

DEFAULT_VALUE = -1
INITIAL_DEPTH = 0

class csp_solver():
    def _minimum_remaining_values(self, problem):
        return min(
            (var for var in problem.variables if var.assigned_value == DEFAULT_VALUE), 
            key=lambda var: var.domain_size,
        )


    def _consistency(self, problem, variable):
        constraints = problem.precomputed_constraints[variable.index]

        for constraint in constraints:
            restricted_variables = [problem.variables[index] for index in constraint.scope]
            index_in_constraint = restricted_variables.index(variable)
            related_tuples = [r_tuple for r_tuple in constraint.tuples if r_tuple[index_in_constraint] == variable.assigned_value]

            if constraint.type and len(related_tuples) == 0:
                return False
            
            var_and_values = defaultdict(list)
            for r_tuple in related_tuples:
                filtered_tuple = [r_tuple[index] for index in range(len(r_tuple)) if index != index_in_constraint]
                remaining_vars = [problem.variables[constraint.scope[i]] for i in range(constraint.scope_size) if i != index_in_constraint]

                for var, value in zip(remaining_vars, filtered_tuple):
                    var_and_values[var].append(value)
            var_and_values = [(var, set(values)) for var, values in var_and_values.items()]

            if constraint.type:
                for var, values in var_and_values:
                    if var.assigned_value != DEFAULT_VALUE and var.assigned_value not in values:
                        return False
                    if len(values.intersection(set(var.domain))) == 0:
                        return False
            else:
                constraint_result = np.full(len(var_and_values), True)
                for index, (var, values) in enumerate(var_and_values):
                    if var.assigned_value != DEFAULT_VALUE and var.assigned_value in values:
                        constraint_result[index] = False
                    if len(values.intersection(set(var.domain))) >= len(var.domain):
                        constraint_result[index] = False

                if len(constraint_result) > 0 and True not in constraint_result:
                    return False
                
        return True
    

    def _arc_consistency(self, problem):
        queue = {var for var in problem.variables if var.assigned_value == DEFAULT_VALUE}

        while queue:
            variable = queue.pop()
            initial_domain_size = variable.domain_size

            for value in reversed(variable.domain):
                variable.assigned_value = value
                consistent = self._consistency(problem, variable)
                variable.assigned_value = DEFAULT_VALUE

                if not consistent:
                    variable.domain.remove(value)
                    variable.domain_size -= 1
                    
                    if variable.domain_size == 0:
                        return False

            if variable.domain_size != initial_domain_size:
                queue.update(
                    problem.variables[index]
                    for constraint in problem.precomputed_constraints[variable.index]
                    for index in constraint.scope
                    if variable.index != index and problem.variables[index].assigned_value == DEFAULT_VALUE
                )
        
        return True



    def _backtracking(self, problem, result, depth):
        if depth == problem.vars_qty:
            problem.solved = True
            return
        
        if not self._arc_consistency(problem):
            return
        
        selected_variable = self._minimum_remaining_values(problem)
        for value in selected_variable.domain:
            if problem.solved:
                return

            result[selected_variable.index], selected_variable.assigned_value = value, value
            self._backtracking(problem.conditional_copy(), result, depth + 1)

        if not problem.solved:
            result[selected_variable.index], selected_variable.assigned_value = DEFAULT_VALUE, DEFAULT_VALUE


    def solve(self, problem):
        result = np.full(problem.vars_qty, DEFAULT_VALUE)

        self._backtracking(problem, result, INITIAL_DEPTH)
        return result