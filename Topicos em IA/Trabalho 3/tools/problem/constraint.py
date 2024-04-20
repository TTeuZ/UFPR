import numpy as np

# Class that represent a CSP Constraint
# _type: Constrint type (I or V)
# _scope: Constraint scope -> (scope_size, [scope])
# _tuples: Constraint tuples -> (tuples_size, [tuples])

DEFAULT_VALUE = -1

class constraint():
    def __init__(self, constraint_type, scope, tuples):
        self.type = constraint_type
        self.scope_size, self.scope = scope
        self.tuples_size, self.tuples = tuples

    
    def check_feasibility_with_values(self, values):
        temp = np.full(self.scope_size, DEFAULT_VALUE)
        for temp_index, values_index in enumerate(self.scope):
            temp[temp_index] = values[values_index]

        if self.type == "V":
            for value_tuple in self.tuples:
                if np.array_equal(temp, np.array(value_tuple)):
                    return True
            return False
        else:
            for value_tuple in self.tuples:
                if np.array_equal(temp, np.array(value_tuple)):
                    return False
            return True