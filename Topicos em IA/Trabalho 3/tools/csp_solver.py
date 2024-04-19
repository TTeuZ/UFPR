import numpy as np

# CSP Solver class
# Use a simple backtracking to find one solution (not optmal)

DEFAULT_VALUE = -1

class csp_solver():
    def _backtracking(self, problem, result):
        print("batata")


    def solve(self, problem):
        result = np.full(len(problem._variables), DEFAULT_VALUE)

        self._backtracking(problem, result)
        return result

