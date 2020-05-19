# Omni-wheel platform
Projekt zakladał zbudowanie robota z wykorzystaniem kół omnikierunkowych umożliwiających jazdę platformy w dowolnym kierunku bez wykonywania obrou w okół własnej osi.
Do zbudowania robota urzyto mikrokontroler STM F103RB oraz zaprojektowano dedykowanął płytkę PCB. Elementami wykonawczymi były 3 silniki DC
z wbudowanym enkoderm umożliwjającym obliczanie rzeczywistej prędkości obrotowej silników. Sterowanie platformą odbywało się za pomocą kontrolera do gier.
## Program
Napisany program zawiera algorytm regulatora PID służący do osiągania zadanej prędkości silników, komunikację SPI kontrolera z robotem oraz algorytm sterowania robta.
### Zdjęcie robota 
