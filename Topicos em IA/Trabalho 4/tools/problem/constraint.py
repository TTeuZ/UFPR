import numpy as np

DEFAULT_VALUE = -1

class constraint():
    def __init__(self, constraint_type, scope, tuples):
        self.type = constraint_type.upper() == "V"
        
        self.scope_size, self.scope = scope
        self.tuples_size, self.tuples = tuples