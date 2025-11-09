a =1
b =1

def soma(x, y):
    return x + y

if a: #verdade
    b = b +1 #2
    if b: #verdade
        a = a +1 #2
    b = 1
    x = soma(a, b) #4
    
    if soma(a, b) > 10: #falso
        a = a + 2 #4
    else:
        print("acabou")