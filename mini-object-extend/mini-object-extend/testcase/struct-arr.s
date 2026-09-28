	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4
	JMP main

	# label main
main:

	# begin

	# var i

	# var j

	# var a

	# var b

	# var c1

	# var t0

	# t0 = &c1
	LOD R5,R2
	LOD R6,18
	ADD R5,R6

	# var t1

	# t1 = t0 + 0
	LOD R6,0
	ADD R5,R6
	STO (R2+5572),R5

	# *t1 = 1
	LOD R7,1
	STO (R5+0),R7
	STO (R2+5576),R5

	# var t2

	# t2 = &c1
	LOD R5,R2
	LOD R6,18
	ADD R5,R6

	# var t3

	# t3 = t2 + 14
	LOD R6,14
	ADD R5,R6
	STO (R2+5580),R5

	# var t5

	# var t4

	# t4 = 2 * 554
	LOD R7,2
	LOD R8,554
	MUL R7,R8

	# t5 = t3 + t4
	ADD R5,R7
	STO (R2+5584),R5

	# var t6

	# t6 = t5 + 0
	LOD R9,0
	ADD R5,R9
	STO (R2+5588),R5

	# *t6 = 2
	LOD R10,2
	STO (R5+0),R10
	STO (R2+5596),R5
	STO (R2+5592),R7

	# var t7

	# t7 = &c1
	LOD R5,R2
	LOD R6,18
	ADD R5,R6

	# var t8

	# t8 = t7 + 14
	LOD R6,14
	ADD R5,R6
	STO (R2+5600),R5

	# var t10

	# var t9

	# t9 = 2 * 554
	LOD R7,2
	LOD R8,554
	MUL R7,R8

	# t10 = t8 + t9
	ADD R5,R7
	STO (R2+5604),R5

	# var t11

	# t11 = t10 + 14
	ADD R5,R6
	STO (R2+5608),R5

	# var t13

	# var t12

	# t12 = 3 * 54
	LOD R9,3
	LOD R10,54
	MUL R9,R10

	# t13 = t11 + t12
	ADD R5,R9
	STO (R2+5616),R5

	# var t14

	# t14 = t13 + 4
	LOD R11,4
	ADD R5,R11
	STO (R2+5620),R5

	# var t16

	# var t15

	# t15 = 1 * 1
	LOD R12,1
	LOD R13,R12
	MUL R13,R12

	# t16 = t14 + t15
	ADD R5,R13
	STO (R2+5628),R5

	# *t16 = 98
	LOD R12,98
	STC (R5+0),R12
	STO (R2+5632),R5
	STO (R2+5612),R7
	STO (R2+5624),R9
	STO (R2+5636),R13

	# var t17

	# t17 = &c1
	LOD R5,R2
	LOD R6,18
	ADD R5,R6

	# var t18

	# t18 = t17 + 14
	LOD R6,14
	ADD R5,R6
	STO (R2+5640),R5

	# var t20

	# var t19

	# t19 = 2 * 554
	LOD R7,2
	LOD R8,554
	MUL R7,R8

	# t20 = t18 + t19
	ADD R5,R7
	STO (R2+5644),R5

	# var t21

	# t21 = t20 + 14
	ADD R5,R6
	STO (R2+5648),R5

	# var t23

	# var t22

	# t22 = 3 * 54
	LOD R9,3
	LOD R10,54
	MUL R9,R10

	# t23 = t21 + t22
	ADD R5,R9
	STO (R2+5656),R5

	# var t24

	# t24 = t23 + 4
	LOD R11,4
	ADD R5,R11
	STO (R2+5660),R5

	# var t26

	# var t25

	# t25 = 0 * 1
	LOD R12,0
	LOD R13,1
	MUL R12,R13

	# t26 = t24 + t25
	ADD R5,R12
	STO (R2+5668),R5

	# *t26 = 97
	LOD R14,97
	STC (R5+0),R14
	STO (R2+5672),R5
	STO (R2+5652),R7
	STO (R2+5664),R9
	STO (R2+5676),R12

	# ifz 0 goto L2
	LOD R5,0
	TST R5
	JEZ L2

	# output L1
	LOD R6,L1
	LOD R15,R6
	OTS

	# label L2
L2:

	# var t27

	# t27 = &c1
	LOD R5,R2
	LOD R6,18
	ADD R5,R6

	# var t28

	# t28 = t27 + 0
	LOD R6,0
	ADD R5,R6
	STO (R2+5680),R5

	# var t29

	# t29 = *t28
	LOD R7,(R5+0)

	# i = t29
	STO (R2+5688),R7
	STO (R2+8),R7

	# var t30

	# t30 = &c1
	LOD R8,R2
	LOD R9,18
	ADD R8,R9

	# var t31

	# t31 = t30 + 14
	LOD R9,14
	ADD R8,R9
	STO (R2+5692),R8

	# var t33

	# var t32

	# t32 = 2 * 554
	LOD R10,2
	LOD R11,554
	MUL R10,R11

	# t33 = t31 + t32
	ADD R8,R10
	STO (R2+5696),R8

	# var t34

	# t34 = t33 + 0
	ADD R8,R6
	STO (R2+5700),R8

	# var t35

	# t35 = *t34
	LOD R12,(R8+0)

	# j = t35
	STO (R2+5712),R12
	STO (R2+12),R12

	# var t36

	# t36 = &c1
	LOD R13,R2
	LOD R14,18
	ADD R13,R14

	# var t37

	# t37 = t36 + 14
	ADD R13,R9
	STO (R2+5716),R13

	# var t39

	# var t38

	# t38 = 2 * 554
	LOD R14,2
	MUL R14,R11

	# t39 = t37 + t38
	ADD R13,R14
	STO (R2+5720),R13

	# var t40

	# t40 = t39 + 14
	ADD R13,R9
	STO (R2+5724),R13

	# var t42

	# var t41

	# t41 = 3 * 54
	LOD R6,3
	LOD R6,54
	LOD R7,3
	MUL R7,R6

	# t42 = t40 + t41
	ADD R13,R7
	STO (R2+5732),R13

	# var t43

	# t43 = t42 + 4
	LOD R6,4
	ADD R13,R6
	STO (R2+5736),R13

	# var t45

	# var t44

	# t44 = 0 * 1
	LOD R6,0
	LOD R6,1
	STO (R2+5740),R7
	LOD R7,0
	MUL R7,R6

	# t45 = t43 + t44
	ADD R13,R7
	STO (R2+5744),R13

	# var t46

	# t46 = *t45
	LDC R6,(R13+0)

	# a = t46
	STC (R2+5756),R6
	STC (R2+16),R6

	# var t47

	# t47 = &c1
	LOD R6,R2
	LOD R9,18
	ADD R6,R9

	# var t48

	# t48 = t47 + 14
	LOD R9,14
	ADD R6,R9
	STO (R2+5757),R6

	# var t50

	# var t49

	# t49 = 2 * 554
	LOD R9,2
	MUL R9,R11

	# t50 = t48 + t49
	ADD R6,R9
	STO (R2+5761),R6

	# var t51

	# t51 = t50 + 14
	LOD R11,14
	ADD R6,R11
	STO (R2+5765),R6

	# var t53

	# var t52

	# t52 = 3 * 54
	LOD R11,3
	LOD R11,54
	LOD R12,3
	MUL R12,R11

	# t53 = t51 + t52
	ADD R6,R12
	STO (R2+5773),R6

	# var t54

	# t54 = t53 + 4
	LOD R11,4
	ADD R6,R11
	STO (R2+5777),R6

	# var t56

	# var t55

	# t55 = 1 * 1
	LOD R11,1
	STO (R2+5781),R12
	LOD R12,R11
	MUL R12,R11

	# t56 = t54 + t55
	ADD R6,R12
	STO (R2+5785),R6

	# var t57

	# t57 = *t56
	LDC R11,(R6+0)

	# b = t57
	STC (R2+5797),R11
	STC (R2+17),R11

	# ifz 0 goto L3
	STO (R2+5684),R5
	STO (R2+5789),R6
	STO (R2+5752),R7
	STO (R2+5708),R8
	STO (R2+5769),R9
	STO (R2+5704),R10
	STO (R2+5793),R12
	STO (R2+5748),R13
	STO (R2+5728),R14
	LOD R5,0
	TST R5
	JEZ L3

	# output L1
	LOD R5,L1
	LOD R15,R5
	OTS

	# label L3
L3:

	# output i
	LOD R5,(R2+8)
	LOD R15,R5
	OTI

	# output j
	LOD R6,(R2+12)
	LOD R15,R6
	OTI

	# output a
	LDC R7,(R2+16)
	LOD R15,R7
	OTC

	# output b
	LDC R8,(R2+17)
	LOD R15,R8
	OTC

	# output L1
	LOD R9,L1
	LOD R15,R9
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L1:
	DBS 10,0
STATIC:
	DBN 0,0
STACK:
