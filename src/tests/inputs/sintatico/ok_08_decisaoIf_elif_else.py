# Caso de teste: estruturas de decisão com if, elif e else
# Contém if, elif e else aninhados e atribuições dentro de cada bloco

x = 5
y = 0
z = 10

if x > 10:  # falso neste caso
    y = y + 1  # não executado
    if z > 0:
        x = x + z
    elif y == 0:
        z = z - 1
    else:
        y = 2

elif x == 5:  # verdadeiro
    y = 100
    if y > 50:  # verdadeiro
        z = z + 5  # z vira 15
        if z > 20:
            x = x + 10
        elif z == 15:
            x = x + 1  # este ramo será executado (x passa a 6)
        else:
            x = x - 1
    else:
        x = x - 1

else:
    # bloco else (não executado aqui)
    x = 0
    y = y + x
    if x:
        z = z * 2
    else:
        z = -1

# saída esperada (para observação durante testes): x=6, y=100, z=15
print(x, y, z)
