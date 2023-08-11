nums = [1, 2, 3, 4, 5, 6]
oddNums = [x for x in nums if x % 2 == 1]
print(oddNums)
oddNumsPlusOne = [x + 1 for x in nums if x % 2 == 1]
print(oddNumsPlusOne)

letters = ['BATATA', 'Pao de Queijo', 'TRES', 'Car']
lettersWithMoreThan5Chars = [x.lower() for x in letters if len(x) > 5]
print(lettersWithMoreThan5Chars)