
# tac list

0x5609e9ce5ca0	label main
0x5609e9ce5ce0	begin
0x5609e9ce4810	var i
0x5609e9ce4950	var k
0x5609e9ce4a60	k = 0
0x5609e9ce5ac0	label L5
0x5609e9ce4c00	var t0
0x5609e9ce4c40	t0 = (k < 10)
0x5609e9ce5c00	ifz t0 goto L6
0x5609e9ce4cf0	i = 0
0x5609e9ce5640	label L2
0x5609e9ce4e30	var t1
0x5609e9ce4e70	t1 = (i < 10)
0x5609e9ce5780	ifz t1 goto L3
0x5609e9ce5030	var t2
0x5609e9ce5070	t2 = i + i
0x5609e9ce51c0	var t3
0x5609e9ce5200	t3 = t2 + 9
0x5609e9ce52a0	output t3
0x5609e9ce5340	output L1
0x5609e9ce5500	var t4
0x5609e9ce5540	t4 = i + 1
0x5609e9ce5580	i = t4
0x5609e9ce5680	goto L2
0x5609e9ce5740	label L3
0x5609e9ce5820	output L4
0x5609e9ce5980	var t5
0x5609e9ce59c0	t5 = k + 1
0x5609e9ce5a00	k = t5
0x5609e9ce5b00	goto L5
0x5609e9ce5bc0	label L6
0x5609e9ce5d20	end
