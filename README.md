# Omni-wheel platform
Projekt zakladał zbudowanie robota z wykorzystaniem kół omnikierunkowych umożliwiających jazdę platformy w dowolnym kierunku bez wykonywania obrou w okół własnej osi.
Do zbudowania robota urzyto mikrokontroler STM F103RB oraz zaprojektowano dedykowanął płytkę PCB. Elementami wykonawczymi były 3 silniki DC
z wbudowanym enkoderm umożliwjającym obliczanie rzeczywistej prędkości obrotowej silników. Sterowanie platformą odbywało się za pomocą kontrolera do gier.
## Program
Napisany program zawiera algorytm regulatora PID służący do osiągania zadanej prędkości silników, komunikację SPI kontrolera z robotem oraz algorytm sterowania robta.
### Zdjęcie robota 

<img width="509" alt="ROBOT" src="https://user-images.githubusercontent.com/62465226/82304467-acc95b00-99bc-11ea-86e4-deb19443f3e7.png">

<img width="693" alt="Robot2" src="https://user-images.githubusercontent.com/62465226/82304277-670c9280-99bc-11ea-84b9-daf13b3d3420.png">
