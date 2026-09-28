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

	# var k

	# var l

	# var a

	# var b

	# var c

	# var d

	# input d
	LDC R5,(R2+27)
	ITC
	LOD R5,R15
	STC (R2+27),R5

	# c = 99
	LOD R6,99
	STC (R2+26),R6

	# b = 98
	LOD R7,98
	STC (R2+25),R7

	# input a
	LDC R8,(R2+24)
	ITC
	LOD R8,R15
	STC (R2+24),R8

	# ifz 0 goto L2
	LOD R9,0
	TST R9
	JEZ L2

	# output L1
	LOD R10,L1
	LOD R15,R10
	OTS

	# label L2
L2:

	# output a
	LDC R5,(R2+24)
	LOD R15,R5
	OTC

	# output b
	LDC R6,(R2+25)
	LOD R15,R6
	OTC

	# output c
	LDC R7,(R2+26)
	LOD R15,R7
	OTC

	# output d
	LDC R8,(R2+27)
	LOD R15,R8
	OTC

	# output L1
	LOD R9,L1
	LOD R15,R9
	OTS

	# i = a
	STO (R2+8),R5

	# j = b
	STO (R2+12),R6

	# k = c
	STO (R2+16),R7

	# l = d
	STO (R2+20),R8

	# ifz 0 goto L3
	LOD R10,0
	TST R10
	JEZ L3

	# output L1
	LOD R15,R9
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

	# output k
	LOD R7,(R2+16)
	LOD R15,R7
	OTI

	# output l
	LOD R8,(R2+20)
	LOD R15,R8
	OTI

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
