import shop

shopName = 'the Berkeley Bowl'
fruitPrices = {'apples': 1.00, 'oranges': 1.50, 'pears': 1.75}
berkeleyShop = shop.FruitShop(shopName, fruitPrices)

print(berkeleyShop.name)
berkeleyShop.name = 'Batata'
print(berkeleyShop.name)