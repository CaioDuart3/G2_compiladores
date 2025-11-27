def testar_condicionais(a, b, c):
    if a == b:
        print("a é igual a b (==)")
    else:
        if a != b and b < c:
            print("a é diferente de b (!=) E b é menor que c (<)")
        else:
            if a > b or c <= b:
                print("a é maior que b (>) OU c é menor ou igual a b (<=)")
            else:
                print("Nenhuma condição anterior satisfeita")



testar_condicionais(5, 3, 10)
