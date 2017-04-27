; ====================
sr = 44100
kr = 441
ksmps = 100
nchnls = 2
; ====================

; =======================================
instr 1 ; (short atack, long release)
; =======================================
iamp = p5 * 25000
ifreq = cpspch(p4)
itable = 1

kamp linen 1.0, 0.05, p3, (0.9 * p3)
asig oscil iamp, ifreq, itable
aout = kamp * asig
outs aout, aout
; =======================================
endin
; =======================================
; =======================================
instr 2 ; (medium atack, short release)
; =======================================
iamp = p5 * 25000
ifreq = cpspch(p4)
itable = 2

kamp linen 1.0, 0.1, p3, (0.1 * p3)
asig oscil iamp, ifreq, itable
aout = kamp * asig
outs aout, aout
; =======================================
endin
; =======================================
; =======================================
instr 3 ; (long atack, long release)
; =======================================
iamp = p5 * 25000
ifreq = cpspch(p4)
itable = 3

kamp linen 1.0, (0.4 * p3), p3, (0.3 * p3)
asig oscil iamp, ifreq, itable
aout = kamp * asig
outs aout, aout
; =======================================
endin
; =======================================
; =======================================
instr 4 ; (short atack, medium release)
; =======================================
iamp = p5 * 25000
ifreq = cpspch(p4)
itable = 4

kamp linen 1.0, 0.03, p3, (0.4 * p3)
asig oscil iamp, ifreq, itable
aout = kamp * asig
outs aout, aout
; =======================================
endin
; =======================================
