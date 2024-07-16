import numpy as np

# CSP Solver class
# Use a simple backtracking to find one solution (not optmal)

DEFAULT_VALUE = -1
INITIAL_DEPTH = 0

class csp_solver():
    def _check_constraints(self, index, result, constraints):
        if index < 1: return True

        for constraint in constraints[index]:
            if not constraint.check_feasibility_with_values(result):
                return False
        return True
        

    def _backtracking(self, problem, result, depth):
        if depth == problem.vars_qty:
            problem.solved = True
            return

        _, domain = problem.variables[depth]
        for value in domain:
            if problem.solved:
                return

            result[depth] = value
            if self._check_constraints(depth, result, problem.precomputed_constraints):
                self._backtracking(problem, result, depth + 1)

        if not problem.solved:
            result[depth] = DEFAULT_VALUE


    def solve(self, problem):
        result = np.full(len(problem.variables), DEFAULT_VALUE)

        self._backtracking(problem, result, INITIAL_DEPTH)
        return result