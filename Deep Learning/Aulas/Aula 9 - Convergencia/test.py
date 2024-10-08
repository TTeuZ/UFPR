import torch
import torch.optim as optim
from mpl_toolkits.mplot3d import Axes3D


# Definindo a função a ser minimizada
def func(x, y):
    return 3 * (x - 1)**2 + (y - 3)**2

# Chute inicial para x e y
x = torch.tensor([5.0], requires_grad=True)
y = torch.tensor([5.0], requires_grad=True)

# Definindo o otimizador RMSProp
optimizer = optim.RMSprop([x, y], lr=0.05)
# Teste o SGD com e sem momentum para comparar
# optimizer = optim.SGD([x, y], lr=0.05, momentum=0)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.view_init(0, 150)

X = np.linspace(-1, 5, 400)
Y = np.linspace(0, 6, 400)
X, Y = np.meshgrid(X, Y)
Z = func(torch.tensor(X), torch.tensor(Y)).detach().numpy()

ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.6)

for step in range(50):
    optimizer.zero_grad()
    loss = func(x, y)
    loss.backward()

    # Capturando os gradientes antes de fazer a atualização
    grad_x = x.grad.item()
    grad_y = y.grad.item()

    optimizer.step()

    ax.scatter(x.item(), y.item(), loss.item(), color='red')
    #Descomente abaixo se estiver executando em sua máquina local
    #plt.pause(0.01)

    print(f'Step {step}: x = {x.item():.4f}, y = {y.item():.4f}, loss = {loss.item():.4f} Gradient x = {grad_x:.4f}, Gradient y = {grad_y:.4f}')

# Valores finais de x, y e o valor mínimo da função
print(f"Final: x = {x.item():.4f}, y = {y.item():.4f}, loss = {func(x, y).item():.4f}")

# Mostrando o gráfico final
plt.show()
