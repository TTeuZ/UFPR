DEFAULT_VALUE = -1

class variable():
    def __init__(self, index, domain_size, domain):
        self.index = index
        self.domain = domain
        self.domain_size = domain_size

        self.assigned_value = DEFAULT_VALUE
