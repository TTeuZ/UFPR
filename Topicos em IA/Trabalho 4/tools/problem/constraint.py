import numpy as np

# Class that represent a CSP Constraint
# type: Constrint type (I or V)
# scope: Constraint scope -> (scope_size, [scope])
# tuples: Constraint tuples -> (tuples_size, [tuples])

DEFAULT_VALUE = -1

class constraint():
    def __init__(self, constraint_type, scope, tuples):
        self.type = constraint_type.upper() == "V"
        
        self.scope_size, self.scope = scope
        self.tuples_size, self.tuples = tuples

    
    def check_feasibility_with_values(self, values):
        restricted_values = np.full(self.scope_size, DEFAULT_VALUE)
        for restricted_index, values_index in enumerate(self.scope):
            restricted_values[restricted_index] = values[values_index]

        value_tuple = tuple(restricted_values)
        if self.type:
            return value_tuple in self.tuples  
        else:
            return value_tuple not in self.tuples