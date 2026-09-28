
# tac list

0x556ee28ea7a0	var i
0x556ee28eb430	label main
0x556ee28eb470	begin
0x556ee28ea900	var a
0x556ee28ea9d0	var b
0x556ee28eaaa0	var c
0x556ee28eab00	input a
0x556ee28eab60	input b
0x556ee28ead10	var t0
0x556ee28ead50	actual b
0x556ee28ead90	actual a
0x556ee28eadf0	t0 = call max
0x556ee28eae60	c = t0
0x556ee28eaec0	output c
0x556ee28eaf90	output L1
0x556ee28eb1b0	var t1
0x556ee28eb1f0	t1 = i + 1
0x556ee28eb230	i = t1
0x556ee28eb290	output i
0x556ee28eb360	output L2
0x556ee28eb4b0	end
0x556ee28ebdb0	label max
0x556ee28ebdf0	begin
0x556ee28eb610	formal x
0x556ee28eb6e0	formal y
0x556ee28eb850	var t2
0x556ee28eb890	t2 = (x > y)
0x556ee28ebc10	ifz t2 goto L3
0x556ee28eb940	i = x
0x556ee28ebc50	goto L4
0x556ee28ebae0	label L3
0x556ee28eb9f0	i = y
0x556ee28ebbd0	label L4
0x556ee28ebce0	return i
0x556ee28ebe30	end
