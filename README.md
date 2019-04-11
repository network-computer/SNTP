# SNTP

### Dependencies 
GCC

### Compile
```bash
gcc socket.c -o socket
```

### Run
```bash
./socket
```


## A Estrutura do NTP.br

Os servidores públicos estrato 2 do NTP.br são:
```
a.ntp.br
b.ntp.br
c.ntp.br
```

Cada um desses endereços representa um servidor duplo: duas lâminas numa blade, cada uma delas com duas placas de rede conectadas a estruturas de rede distintas (routers e switches diferentes). Ou seja, há redundância de hardware e de conectividade, com balanceamento automático. Cada um deles está em um datacenter diferente, com ótima conexão à Internet.

Eles são alimentados por servidores primários (estrato 1), também acessíveis publicamente:
```
a.st1.ntp.br
b.st1.ntp.br
c.st1.ntp.br
d.st1.ntp.br
```
Esses, por sua vez, são sincronizados com relógios atômicos, que são de responsabilidade do Observatório Nacional.

Existe também um servidor que utilizamos para monitoração do sistema. É um servidor ntp estrato 1, sincronizado com o Sistema de Posicionamento Global (GPS). Ele também pode ser usado:
```
gps.ntp.br
```
O servidor de monitoração consulta todos os servidores estrato 1 e estrato 2 do NTP.br e através de seus logs são gerados gráficos que podem ser visualizados nesta página.

A figura a seguir representa a estrutura do NTP.br:

![](images/ntp-structure.png)


