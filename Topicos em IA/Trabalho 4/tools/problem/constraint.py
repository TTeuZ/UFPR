import numpy as np

DEFAULT_VALUE = -1

class constraint():
    def __init__(self, constraint_type, scope, tuples):
        self.type = constraint_type.upper() == "V"
        
        self.scope_size, self.scope = scope
        self.tuples_size, self.tuples = tuples


    def _check_v_type(self, var, values):
        if var.assigned_value != DEFAULT_VALUE:
            return var.assigned_value in values
        return bool(values.intersection(var.domain))
    

    def _check_i_type(self, var, values):
        if var.assigned_value != DEFAULT_VALUE:
            return var.assigned_value not in values
        return len(values.intersection(var.domain)) < len(var.domain)


    def is_satisfied(self, var_and_values):
        if self.type:
            return all(self._check_v_type(var, values) for var, values in var_and_values)
        else:
            constraint_result = [self._check_i_type(var, values) for var, values in var_and_values]            
            return len(constraint_result) == 0 or any(constraint_result)
