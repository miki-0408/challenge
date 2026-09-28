
# tac list

0x560ce192f2a0	label main
0x560ce192f2e0	begin
0x560ce192d830	var i
0x560ce192d900	var j
0x560ce192da40	i = 0
0x560ce192daa0	input j
0x560ce192e570	label L3
0x560ce192dc10	var t0
0x560ce192dc50	t0 = (i < j)
0x560ce192e5b0	ifz t0 goto L4
0x560ce192dcb0	output i
0x560ce192ded0	var t1
0x560ce192df10	t1 = i + 1
0x560ce192df50	i = t1
0x560ce192e150	var t2
0x560ce192e190	t2 = (i > 10)
0x560ce192e3d0	ifz t2 goto L2
0x560ce192e260	output L1
0x560ce192e2a0	goto L4
0x560ce192e390	label L2
0x560ce192e5f0	goto L3
0x560ce192e630	label L4
0x560ce192e700	output L5
0x560ce192f0b0	label L8
0x560ce192e870	var t3
0x560ce192e8b0	t3 = (i < j)
0x560ce192f0f0	ifz t3 goto L9
0x560ce192e910	output i
0x560ce192eaa0	var t4
0x560ce192eae0	t4 = i + 1
0x560ce192eb20	i = t4
0x560ce192ec90	var t5
0x560ce192ecd0	t5 = (i == 10)
0x560ce192ef10	ifz t5 goto L7
0x560ce192eda0	output L6
0x560ce192ede0	goto L8
0x560ce192eed0	label L7
0x560ce192f130	goto L8
0x560ce192f170	label L9
0x560ce192f1d0	output L5
0x560ce192f320	end
