from gpiozero import TonalBuzzer
from gpiozero.tones import Tone
from time import sleep

b = TonalBuzzer(2)

b.play(Tone("C4"))
sleep(1)
b.play(Tone("D4"))
sleep(1)
b.play(Tone("E4"))
sleep(1)
b.play(Tone("F4"))
sleep(1)
b.play(Tone("G4"))
sleep(1)
b.play(Tone("A4"))
sleep(1)
b.play(Tone("B4"))
sleep(1)
b.stop()
