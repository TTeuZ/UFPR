import numpy as np

# CSP Solver class
# Use a simple backtracking to find one solution (not optmal)

DEFAULT_VALUE = -1
INITIAL_DEPTH = 0

class csp_solver():
    # def _get_index_related_constraints(self, index, constraints):
    #     temp = []
    #     for constraint in constraints:
    #         validation = constraint.scope - index
    #         if np.all(validation <= 0):
    #             temp.append(constraint)
        
    #     return temp
    def _get_step_constraints(self, index, constraints):
        temp = []
        for constraint in constraints:
            if np.all(constraint.scope <= index):
                temp.append(constraint)
        
        return temp

    
    def _check_constraints(self, index, result, constraints):
        if index < 1: return True

        related_constraints = self._get_step_constraints(index, constraints)
        for constraint in related_constraints:
            if not constraint.check_feasibility_with_values(result):
                return False
        return True


    def _backtracking(self, problem, result, depth):
        if depth == problem.vars_qty:
            problem.solved = True
        
        if not problem.solved:
            _, domain = problem.variables[depth]

            for value in domain:
                if not problem.solved:
                    result[depth] = value
                    if self._check_constraints(depth, result, problem.constraints):
                        self._backtracking(problem, result, depth + 1)
            
            if not problem.solved:
                result[depth] = DEFAULT_VALUE


    def solve(self, problem):
        result = np.full(len(problem.variables), DEFAULT_VALUE)

        self._backtracking(problem, result, INITIAL_DEPTH)
        return result