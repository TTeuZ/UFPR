# Class that represent a CSP Constraint
# _type: Constrint type (I or V)
# _scope: Constraint scope -> (scope_size, [scope])
# _tuples: Constraint tuples -> (tuples_size, [tuples])

class constraint():
    def __init__(self, constraint_type, scope, tuples):
        self._type = constraint_type
        self._scope = scope
        self._tuples = tuples