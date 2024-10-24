import os

semana = input("Digite o número da semana: ")
semana = f"./Semana {semana}/"

pratica = input("Digite o número da prática: ")
pratica = f'pratica{pratica}'

os.system(f'cd "{semana}" && msp430-gcc -mmcu=msp430g2553 -o {pratica}.elf {pratica}.c')


os.system(f'cd "{semana}" && sudo mspdebug rf2500 "prog {pratica}.elf"')

